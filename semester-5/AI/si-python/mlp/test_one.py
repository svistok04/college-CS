import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm
from template_mlp import MLPApproximator
import os
import sys

def fake_data(m, domain=np.pi, noise_std=0.1):
    np.random.seed(0)
    X = np.random.rand(m, 2) * domain
    y = np.cos(X[:, 0] * X[:, 1]) * np.cos(2 * X[:, 0]) + np.random.randn(m) * noise_std  # target: cos(x_1 * x_2) * cos(2 * X_0) + noise
    return X, y


def loss_during_fit(approx, X_train, y_train, X_test, y_test):
    keys = list(approx.history_weights.keys())
    epochs = []
    losses_train = []
    losses_test = []
    weights = approx.weights_
    weights0 = approx.weights0_
    for k in keys:
        epochs.append(k + 1)
        approx.weights_ = approx.history_weights[k]
        approx.weights0_ = approx.history_weights0[k]
        losses_train.append(np.mean((approx.predict(X_train) - y_train)**2))
        losses_test.append(np.mean((approx.predict(X_test) - y_test)**2))
    approx.weights_ = weights
    approx.weights0_ = weights0
    return epochs, losses_train, losses_test

def r2_during_fit(approx, X_train, y_train, X_test, y_test):
    keys = list(approx.history_weights.keys())
    epochs = []
    r2s_train = []
    r2s_test = []
    weights = approx.weights_
    weights0 = approx.weights0_
    for k in keys:
        epochs.append(k + 1)
        approx.weights_ = approx.history_weights[k]
        approx.weights0_ = approx.history_weights0[k]
        r2s_train.append(approx.score(X_train, y_train))
        r2s_test.append(approx.score(X_test, y_test))
    approx.weights_ = weights
    approx.weights0_ = weights0
    return epochs, r2s_train, r2s_test

def plot_sgd_comparison(domain, noise_std, m_train, m_test, learning_rate, activation_func, structure, algos):
    import matplotlib.pyplot as plt
    import numpy as np

    X_train, y_train = fake_data(m_train, domain, noise_std)
    X_test, y_test = fake_data(m_test, domain, noise_std)

    results = {}

    for algo in algos:
        try:
            # Initialize the neural network
            approx = MLPApproximator(
                structure=structure,
                activation_name=activation_func,
                targets_activation_name="linear",
                initialization_name="uniform",
                algo_name=algo,
                learning_rate=learning_rate,
                n_epochs=1000,
                batch_size=10,
                seed=53855,
                verbosity_e=100,
                verbosity_b=10,
            )

            # Train the model
            approx.fit(X_train, y_train)

            # Capture losses and R^2 values during fit
            epochs_loss, losses_train, losses_test = loss_during_fit(approx, X_train, y_train, X_test, y_test)
            epochs_r2, r2s_train, r2s_test = r2_during_fit(approx, X_train, y_train, X_test, y_test)
            results[algo] = {
                "epochs_loss": epochs_loss,
                "loss_train": losses_train,
                "loss_test": losses_test,
                "epochs_r2": epochs_r2,
                "r2_train": r2s_train,
                "r2_test": r2s_test,
            }

        except Exception as e:
            print(f"Algorithm {algo} failed due to: {e}")

    # Create a figure for visualization
    fig, axes = plt.subplots(2, 1, figsize=(12, 10))

    # Row 1: Loss curves
    axes[0].set_title("Train/Test Loss (MSE) Across Algorithms", fontsize=14)
    for algo, data in results.items():
        axes[0].plot(data["epochs_loss"], data["loss_train"], label=f"{algo} (Train)", linestyle="--", marker=".")
        axes[0].plot(data["epochs_loss"], data["loss_test"], label=f"{algo} (Test)", linestyle="-", marker="o")
    axes[0].set_xlabel("Epochs")
    axes[0].set_ylabel("Loss (MSE)")
    axes[0].grid(True)
    axes[0].legend()

    # Row 2: R^2 curves
    axes[1].set_title("Train/Test R^2 Across Algorithms", fontsize=14)
    for algo, data in results.items():
        axes[1].plot(data["epochs_r2"], data["r2_train"], label=f"{algo} (Train)", linestyle="--", marker=".")
        axes[1].plot(data["epochs_r2"], data["r2_test"], label=f"{algo} (Test)", linestyle="-", marker="o")
    axes[1].set_xlabel("Epochs")
    axes[1].set_ylabel("$R^2$")
    axes[1].grid(True)
    axes[1].legend()

    plt.tight_layout()
    plt.savefig(f"sgd_comparison_{activation_func}_{learning_rate}.png")
    plt.show()


if __name__ == '__main__':
    # Fixed parameters for the comparative plot test
    domain = 1.5 * np.pi
    noise_std = 0.1
    m_train = 1000
    m_test = 10000
    learning_rate = 1e-3
    activation_func = "relu"
    structure = [128, 128, 64, 64, 32, 32]
    algos = ["sgd_simple", "sgd_momentum", "rmsprop", "adam"]

    # Run the comparative test
    plot_sgd_comparison(domain, noise_std, m_train, m_test, learning_rate, activation_func, structure, algos)
