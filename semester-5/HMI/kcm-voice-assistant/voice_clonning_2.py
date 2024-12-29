import torch
import torchaudio
import numpy as np
import soundfile as sf
from data.tokenizer import AudioTokenizer
from torchaudio.transforms import Resample

def generate_npz(prompt_wav_path, output_npz_path, language_code=0):
    print("Processing audio for VALL-E-X...")

    wav, sr = torchaudio.load(prompt_wav_path)

    # Initialize tokenizer
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    tokenizer = AudioTokenizer(device=device)

    if sr != tokenizer.sample_rate:
        print(f"Resampling audio from {sr}Hz to {tokenizer.sample_rate}Hz...")
        resampler = Resample(orig_freq=sr, new_freq=tokenizer.sample_rate)
        wav = resampler(wav)

    if wav.shape[0] > 1:
        print("Converting to mono audio...")
        wav = torch.mean(wav, dim=0, keepdim=True)

    # Add batch dimension
    wav = wav.to(device).unsqueeze(0)

    # Encode audio to discrete tokens
    with torch.no_grad():
        audio_tokens = tokenizer.encode(wav)

    # Extract the first set of tokens
    audio_tokens = audio_tokens[0][0].cpu().numpy()

    # Save tokens as NPZ
    np.savez(output_npz_path,
             audio_tokens=audio_tokens,
             text_tokens=np.array([], dtype=np.int32),
             lang_code=language_code)  # lang_code=0 for English

    print(f"Custom voice prompt saved as: {output_npz_path}")

if __name__ == "__main__":
    ogg_path = "audio_2024-12-15_21-36-28.ogg"
    wav_path = "converted_audio.wav"

    print(f"Converting OGG file '{ogg_path}' to WAV...")
    wav, sr = torchaudio.load(ogg_path)
    sf.write(wav_path, wav.numpy().T, sr)
    print(f"Converted audio saved to: {wav_path}")

    speaker_name = input("Enter a name for the speaker (used in the npz filename): ")
    npz_filename = f"{speaker_name}_prompt.npz"
    generate_npz(wav_path, npz_filename, language_code=0)

    print("Voice cloning prompt generation complete!")
