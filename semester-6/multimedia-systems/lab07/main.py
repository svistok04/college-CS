import numpy as np
import sys
from docx import Document
from docx.shared import Inches
from io import BytesIO
import cv2
import matplotlib.pyplot as plt
from glob import glob
import os

# === A-law ===
def a_law_compress(x, A=87.6):
    x = np.clip(x, -1, 1)
    abs_x = np.abs(x)
    sign_x = np.sign(x)

    # Condition masks
    mask_linear = abs_x < (1 / A)
    mask_log = ~mask_linear

    # Output array
    Fx = np.zeros_like(x)

    # Apply linear part
    Fx[mask_linear] = (A * abs_x[mask_linear]) / (1 + np.log(A))

    # Apply logarithmic part
    Fx[mask_log] = (1 + np.log(A * abs_x[mask_log])) / (1 + np.log(A))

    return sign_x * Fx

def a_law_decompress(y, A=87.6):
    y = np.clip(y, -1, 1)
    abs_y = np.abs(y)
    sign_y = np.sign(y)

    threshold = 1 / (1 + np.log(A))
    mask_linear = abs_y < threshold
    mask_exp = ~mask_linear

    # Output array
    Fx_inv = np.zeros_like(y)

    # Apply inverse linear
    Fx_inv[mask_linear] = (abs_y[mask_linear] * (1 + np.log(A))) / A

    # Apply inverse exponential
    Fx_inv[mask_exp] = (np.exp(abs_y[mask_exp] * (1 + np.log(A)) - 1)) / A

    return sign_y * Fx_inv

def mu_law_compress(x, mu=255):
    x = np.clip(x, -1, 1)
    abs_x = np.abs(x)
    sign_x = np.sign(x)

    Fx = np.log1p(mu * abs_x) / np.log1p(mu)
    return sign_x * Fx

def mu_law_decompress(y, mu=255):
    y = np.clip(y, -1, 1)
    abs_y = np.abs(y)
    sign_y = np.sign(y)

    Fx_inv = (np.expm1(abs_y * np.log1p(mu))) / mu
    return sign_y * Fx_inv


def dpcm_compress(x, bit_depth):
    y = np.zeros_like(x)
    e = 0  # initial estimate
    for i in range(len(x)):
        diff = x[i] - e
        y[i] = quantize(diff, bit_depth)
        e = e + y[i]  # update estimate
    return y

def dpcm_decompress(y):
    x_rec = np.zeros_like(y)
    x_rec[0] = y[0]  # assume starting from 0
    for i in range(1, len(y)):
        x_rec[i] = x_rec[i - 1] + y[i]
    return x_rec

def dpcm_compress_predict(x, bit_depth, predictor, n):
    y = np.zeros_like(x)
    xp = np.zeros_like(x)

    for i in range(len(x)):
        # Get predictor values (last n reconstructed)
        if i < n:
            context = xp[:i] if i > 0 else [0]  # edge case
        else:
            context = xp[i-n:i]

        e = predictor(context)
        diff = x[i] - e
        y[i] = quantize(diff, bit_depth)
        xp[i] = y[i] + e  # update reconstructed signal
    return y

def dpcm_decompress_predict(y, predictor, n):
    x_rec = np.zeros_like(y)

    for i in range(len(y)):
        if i < n:
            context = x_rec[:i] if i > 0 else [0]
        else:
            context = x_rec[i-n:i]

        e = predictor(context)
        x_rec[i] = y[i] + e
    return x_rec


def no_predict(x):
    """Use the last value (like basic DPCM)"""
    return x[-1] if len(x) > 0 else 0.0

def mean_predict(x):
    """Average of the last n values"""
    return np.mean(x) if len(x) > 0 else 0.0

def median_predict(x):
    """Median of the last n values"""
    return np.median(x) if len(x) > 0 else 0.0


# === Kwantyzacja helper ===
def quantize(data, bit_depth, data_min=-1.0, data_max=1.0):
    data = np.clip(data, data_min, data_max)
    levels = 2 ** bit_depth

    # Normalize to [0, 1]
    data_norm = (data - data_min) / (data_max - data_min)

    # Quantize to levels
    data_q = np.round(data_norm * (levels - 1)) / (levels - 1)

    # Rescale to original range
    data_rescaled = data_q * (data_max - data_min) + data_min

    return data_rescaled.astype(np.float32)


def dequantize(val, bit_depth):
    pass

# === Test utility functions (e.g., plotting, audio I/O) ===
def load_audio(file_path):
    pass

def save_audio(file_path, data, sample_rate):
    pass

# def get_all_files():
#     return glob(f"../SING/*1.wav")

def main():
    pass


def plot_sine_compression(y_original, y_a, y_mu, y_dpcm, y_dpcm_pred, title):
    fig, axes = plt.subplots(5, 1, figsize=(8, 10), sharex=True, sharey=True)

    axes[0].plot(y_original)
    axes[0].set_title("Original")

    axes[1].plot(y_a)
    axes[1].set_title("A-law")

    axes[2].plot(y_mu)
    axes[2].set_title("μ-law")

    axes[3].plot(y_dpcm)
    axes[3].set_title("DPCM w/o prediction")

    axes[4].plot(y_dpcm_pred)
    axes[4].set_title("DPCM w/ prediction")

    fig.suptitle(title)
    plt.tight_layout()
    plt.show()

def test():
    bit_depth = 6
    pred_n = 3

    x = np.linspace(-1, 1, 1000)
    original = np.sin(np.pi * x)

    a_compressed = a_law_compress(original)
    a_quantized = quantize(a_compressed, bit_depth)
    a_decompressed = a_law_decompress(a_quantized)

    mu_compressed = mu_law_compress(original)
    mu_quantized = quantize(mu_compressed, bit_depth)
    mu_decompressed = mu_law_decompress(mu_quantized)

    dpcm_encoded = dpcm_compress(original, bit_depth)
    dpcm_decoded = dpcm_decompress(dpcm_encoded)

    dpcm_encoded_pred = dpcm_compress_predict(original, bit_depth, mean_predict, pred_n)
    dpcm_decoded_pred = dpcm_decompress_predict(dpcm_encoded_pred, mean_predict, pred_n)

    plot_sine_compression(
        original,
        a_decompressed,
        mu_decompressed,
        dpcm_decoded,
        dpcm_decoded_pred,
        title=f"Sine wave quantization to {bit_depth} bits"
    )




test()
