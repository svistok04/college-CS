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

def save_plot(fig, plot_filename):
    fig.savefig(plot_filename)
    plt.close(fig)

def generate_plots(approx, X_train, y_train, X_test, y_test, domain, data_settings_str, plot_filename):
    # Generate plots for training and test data
    mesh_size = 50
    X1, X2 = np.meshgrid(np.linspace(0.0, domain, mesh_size), np.linspace(0.0, domain, mesh_size))
    X12 = np.array([X1.ravel(), X2.ravel()]).T
    y_ref = np.cos(X12[:, 0] * X12[:, 1]) * np.cos(2 * X12[:, 0])
    Y_ref = np.reshape(y_ref, (mesh_size, mesh_size))
    y_pred = approx.predict(X12)
    Y_pred = np.reshape(y_pred, (mesh_size, mesh_size))

    fig = plt.figure(figsize=(16, 9))
    fig.suptitle(f"APPROXIMATOR (NEURAL NETWORK): {approx}", fontsize=14)

    # Loss during fit
    epochs, losses_train, losses_test = loss_during_fit(approx, X_train, y_train, X_test, y_test)
    ax_loss = fig.add_subplot(2, 2, 1)
    ax_loss.set_title("TRAIN / TEST LOSS DURING FIT (MSE)")
    ax_loss.plot(epochs, losses_train, color="blue", label="LOSS ON TRAIN DATA")
    ax_loss.plot(epochs, losses_test, color="red", label="LOSS ON TEST DATA")
    ax_loss.legend()
    ax_loss.grid()

    # R^2 during fit
    epochs, r2s_train, r2s_test = r2_during_fit(approx, X_train, y_train, X_test, y_test)
    ax_r2 = fig.add_subplot(2, 2, 2)
    ax_r2.set_title("TRAIN / TEST $R^2$")
    ax_r2.plot(epochs, r2s_train, color="blue", label="$R^2$ ON TRAIN DATA")
    ax_r2.plot(epochs, r2s_test, color="red", label="$R^2$ ON TEST DATA")
    ax_r2.legend()
    ax_r2.grid()

    # Training and prediction surfaces
    ax_train_data = fig.add_subplot(2, 3, 4, projection='3d')
    ax_target = fig.add_subplot(2, 3, 5, projection='3d')
    ax_approximator = fig.add_subplot(2, 3, 6, projection='3d')
    ax_train_data.scatter(X_train[:, 0], X_train[:, 1], y_train, marker=".")
    ax_target.plot_surface(X1, X2, Y_ref, cmap=cm.get_cmap("Spectral"))
    ax_approximator.plot_surface(X1, X2, Y_pred, cmap=cm.get_cmap("Spectral"))

    save_plot(fig, plot_filename)

def run_experiment(domain, noise_std, m_train, m_test, learning_rates, activation_funcs, algos, structures):
    os.makedirs("results", exist_ok=True)

    for lr_idx, lr in enumerate(learning_rates):
        for act_idx, act_name in enumerate(activation_funcs):
            for algo_idx, algo in enumerate(algos):
                for struct_idx, structure in enumerate(structures):
                    exp_id = f"{lr_idx+1}{act_idx+1}{algo_idx+1}{struct_idx+1}"
                    log_filename = f"results/{exp_id}_log.txt"
                    plot_filename = f"results/{exp_id}_plot.png"

                    X_train, y_train = fake_data(m_train, domain, noise_std)
                    X_test, y_test = fake_data(m_test, domain, noise_std)

                    approx = MLPApproximator(
                        structure=structure,
                        activation_name=act_name,
                        targets_activation_name="linear",
                        initialization_name="uniform",
                        algo_name=algo,
                        learning_rate=lr,
                        n_epochs=1000,
                        batch_size=10,
                        seed=53855,
                        verbosity_e=100,
                        verbosity_b=10,
                    )

                    data_settings_str = f"domain={domain}, noise_std={noise_std}, m_train={m_train}, m_test={m_test}"

                    # Redirect console output to a file
                    with open(log_filename, "w") as log_file:
                        original_stdout = sys.stdout  # Backup current stdout
                        sys.stdout = log_file  # Redirect stdout to file

                        try:
                            print(f"EXPERIMENT {exp_id} START")
                            print(f"DATA SETTINGS: {data_settings_str}")
                            print(f"APPROXIMATOR: {approx}")

                            approx.fit(X_train, y_train)

                            y_pred_train = approx.predict(X_train)
                            mse_train = np.mean((y_pred_train - y_train) ** 2)
                            y_pred_test = approx.predict(X_test)
                            mse_test = np.mean((y_pred_test - y_test) ** 2)
                            r2_train = approx.score(X_train, y_train)
                            r2_test = approx.score(X_test, y_test)

                            print(f"LOSS TRAIN (MSE): {mse_train}")
                            print(f"LOSS TEST (MSE): {mse_test}")
                            print(f"R^2 TRAIN: {r2_train}")
                            print(f"R^2 TEST: {r2_test}")
                            print("EXPERIMENT DONE")

                            generate_plots(approx, X_train, y_train, X_test, y_test, domain, data_settings_str, plot_filename)
                        except Exception as e:
                            print(f"EXPERIMENT FAILED: {e}")
                        finally:
                            sys.stdout = original_stdout  # Restore original stdout

if __name__ == '__main__':
    learning_rates = [1e-2, 1e-3, 1e-4]
    activation_funcs = ["sigmoid", "relu"]
    algos = ["sgd_simple", "sgd_momentum", "rmsprop", "adam"]
    structures = [
        [128, 64, 32],
        [128, 128, 64, 64, 32, 32],
        [64] * 5 + [32] * 5 + [16] * 5 + [8] * 5,
        ]

    run_experiment(
        domain=1.5 * np.pi,
        noise_std=0.1,
        m_train=1000,
        m_test=10000,
        learning_rates=learning_rates,
        activation_funcs=activation_funcs,
        algos=algos,
        structures=structures,
    )
