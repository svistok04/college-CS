import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm
from template_mlp import MLPApproximator

def fake_data(m, domain=np.pi, noise_std=0.1):
    np.random.seed(0)    
    X = np.random.rand(m, 2) * domain    
    y = np.cos(X[:, 0] * X[:, 1]) * np.cos(2 * X[:, 0]) + np.random.randn(m) * noise_std # target: cos(x_1 * x_2) * cos(2 * x_1) + normal noise  
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

if __name__ == '__main__':
    print("MLP DEMO...")
        
    # DATA
    domain = 1.0 * np.pi
    noise_std = 0.1
    m_train = 1000
    m_test = 10000
    data_settings_str = f"{domain=}, {noise_std=}, {m_train=}, {m_test=}"
    print(f"DATA SETTINGS: {data_settings_str}")
    X_train, y_train = fake_data(m_train, domain, noise_std)
    X_test, y_test= fake_data(m_test, domain, noise_std)
        
    # APPROXIMATOR (NEURAL NETWORK)            
    approx = MLPApproximator(structure=[32, 16, 8], activation_name="sigmoid", targets_activation_name="linear", initialization_name="uniform", 
                             algo_name="sgd_simple", learning_rate=1e-2,
                             n_epochs=0, batch_size=10, seed=0,
                             verbosity_e=100, verbosity_b=10)    
    print(f"APPROXIMATOR (NEURAL NETWORK): {approx}")
    
    # FIT
    approx.fit(X_train, y_train)
    
    # METRICS - LOSS, R^2    
    y_pred = approx.predict(X_train)
    mse = np.mean((y_pred - y_train)**2)
    print(f"LOSS TRAIN (MSE): {mse}")
    y_pred_test = approx.predict(X_test)
    mse_test = np.mean((y_pred_test - y_test)**2)
    print(f"LOSS TEST (MSE): {mse_test}")
    print(f"R^2 TRAIN: {approx.score(X_train, y_train)}")
    print(f"R^2 TEST: {approx.score(X_test, y_test)}")
    print("MLP DEMO DONE.")
        
    # PLOTS    
    mesh_size = 50  
    X1, X2 = np.meshgrid(np.linspace(0.0, domain, mesh_size), np.linspace(0.0, domain, mesh_size))
    X12 = np.array([X1.ravel(), X2.ravel()]).T
    y_ref = np.cos(X12[:, 0] * X12[:, 1]) * np.cos(2 * X12[:, 0])    
    Y_ref = np.reshape(y_ref, (mesh_size, mesh_size))
    y_pred = approx.predict(X12)
    Y_pred = np.reshape(y_pred, (mesh_size, mesh_size))
    epochs, losses_train, losses_test = loss_during_fit(approx, X_train, y_train, X_test, y_test)
    epochs, r2s_train, r2s_test = r2_during_fit(approx, X_train, y_train, X_test, y_test)        
    fig = plt.figure(figsize=(16, 9))
    fig.suptitle(f"DATA SETTINGS: {data_settings_str}\nAPPROXIMATOR (NEURAL NETWORK): {approx}", fontsize=8)        
    ax_loss = fig.add_subplot(2, 2, 1)
    ax_loss.set_title("TRAIN / TEST LOSS DURING FIT (MSE - MEAN SQUARED ERROR)")
    ax_loss.plot(epochs, losses_train, color="blue", marker=".", label="LOSS ON TRAIN DATA")
    ax_loss.plot(epochs, losses_test, color="red", marker=".", label="LOSS ON TEST DATA")
    ax_loss.legend()
    ax_loss.grid(color="gray", zorder=0, dashes=(4.0, 4.0))
    ax_loss.set_xlabel("EPOCH")
    ax_loss.set_ylabel("SQUARED LOSS")    
    ax_r2 = fig.add_subplot(2, 2, 2)
    ax_r2.set_title("TRAIN / TEST $R^2$ DURING FIT (COEF. OF DETERMINATION)")
    ax_r2.plot(epochs, r2s_train, color="blue", marker=".", label="$R^2$ ON TRAIN DATA")
    ax_r2.plot(epochs, r2s_test, color="red", marker=".", label="$R^2$ ON TEST DATA")
    ax_r2.set_ylim(-0.25, 1.05)
    ax_r2.legend()
    ax_r2.grid(color="gray", zorder=0, dashes=(4.0, 4.0))
    ax_r2.set_xlabel("EPOCH")
    ax_r2.set_ylabel("$R^2$")    
    ax_train_data = fig.add_subplot(2, 3, 4, projection='3d')  
    ax_target = fig.add_subplot(2, 3, 5, projection='3d')  
    ax_approximator = fig.add_subplot(2, 3, 6, projection='3d')         
    ax_train_data.set_title("TRAINING DATA", pad=-32)
    ax_train_data.scatter(X_train[:, 0], X_train[:, 1], y_train, marker=".")
    ax_target.set_title("TARGET (TO BE APPROXIMATED)", pad=-128)
    ax_target.plot_surface(X1, X2, Y_ref, cmap=cm.get_cmap("Spectral"))
    ax_approximator.set_title("NEURAL APPROXIMATOR")
    ax_approximator.plot_surface(X1, X2, Y_pred, cmap=cm.get_cmap("Spectral"))
    ax_train_data.set_box_aspect([2, 2, 1])
    ax_target.set_box_aspect([2, 2, 1])
    ax_approximator.set_box_aspect([2, 2, 1])
    plt.subplots_adjust(top=0.9, bottom=0.05, left=0.1, right=0.9, hspace=0.25, wspace=0.15)
    plt.show()