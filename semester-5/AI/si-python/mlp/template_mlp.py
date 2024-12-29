import numpy as np
from sklearn.base import BaseEstimator, RegressorMixin
import time
import copy

class MLPApproximator(BaseEstimator, RegressorMixin):

    ALGO_NAMES = ["sgd_simple", "sgd_momentum", "rmsprop", "adam"]

    def __init__(self, structure=[16, 8, 4], activation_name="relu", targets_activation_name="linear", initialization_name="uniform",
                 algo_name="sgd_simple", learning_rate=1e-2,  n_epochs=100, batch_size=10, seed=0,
                 verbosity_e=100, verbosity_b=10):
        self.structure = structure
        self.activation_name = activation_name
        self.targets_activation_name = targets_activation_name
        self.initialization_name = initialization_name
        self.algo_name = algo_name
        if self.algo_name not in self.ALGO_NAMES:
            self.algo_name = self.ALGO_NAMES[0]
        self.loss_name = "squared_loss"
        self.learning_rate = learning_rate
        self.n_epochs = n_epochs
        self.batch_size = batch_size
        self.seed = seed
        self.verbosity_e = verbosity_e
        self.verbosity_b = verbosity_b
        self.history_weights = {}
        self.history_weights0 = {}
        self.n_params = None
        # params / constants for algorithms
        self.momentum_beta = 0.9
        self.rmsprop_beta = 0.9
        self.rmsprop_epsilon = 1e-7
        self.adam_beta1 = 0.9
        self.adam_beta2 = 0.999
        self.adam_epsilon = 1e-7

    def __str__(self):
        txt = f"{self.__class__.__name__}(structure={self.structure},"
        txt += "\n" if len(self.structure) > 32 else " "
        txt += f"activation_name={self.activation_name}, targets_activation_name={self.targets_activation_name}, initialization_name={self.initialization_name}, "
        txt += f"algo_name={self.algo_name}, learning_rate={self.learning_rate}, n_epochs={self.n_epochs}, batch_size={self.batch_size})"
        if self.n_params:
            txt += f" [n_params: {self.n_params}]"
        return txt

    @staticmethod
    def he_uniform(n_in, n_out):
        scaler = np.sqrt(6.0 / n_in)
        return ((np.random.rand(n_out, n_in)  * 2.0 - 1.0) * scaler).astype(np.float32)

    @staticmethod
    def he_normal(n_in, n_out):
        scaler = np.sqrt(2.0 / n_in)
        return (np.random.randn(n_out, n_in) * scaler).astype(np.float32)

    @staticmethod
    def glorot_uniform(n_in, n_out):
        scaler = np.sqrt(6.0 / (n_in + n_out))
        return ((np.random.rand(n_out, n_in)  * 2.0 - 1.0) * scaler).astype(np.float32)

    @staticmethod
    def glorot_normal(n_in, n_out):
        scaler = np.sqrt(2.0 / (n_in + n_out))
        return (np.random.randn(n_out, n_in) * scaler).astype(np.float32)

    @staticmethod
    def prepare_batch_ranges(m, batch_size):
        n_batches = int(np.ceil(m / batch_size))
        batch_ranges = batch_size * np.ones(n_batches, dtype=np.int32)
        remainder = m % batch_size
        if remainder > 0:
            batch_ranges[-1] = remainder
        batch_ranges = np.r_[0, np.cumsum(batch_ranges)]
        return n_batches, batch_ranges

    @staticmethod
    def sigmoid(S):
        return 1.0 / (1.0 + np.exp(-S))

    @staticmethod
    def sigmoid_d(phi_S):
        return phi_S * (1.0 - phi_S)

    @staticmethod
    def relu(S):
        pass # TODO

    @staticmethod
    def relu_d(phi_S):
        pass # TODO

    @staticmethod
    def linear(S):
        return S

    @staticmethod
    def linear_d(phi_S):
        return np.ones(phi_S.shape, dtype=np.float32)

    @staticmethod
    def squared_loss(y_MLP, y_target):
        return (y_MLP - y_target)**2

    @staticmethod
    def squared_loss_d(y_MLP, y_target):
        return 2.0 * (y_MLP - y_target)

    def pre_algo_sgd_simple(self):
        return # no special preparation needed for simple SGD

    def algo_sgd_simple(self, l):
        self.weights_[l] = self.weights_[l] - self.learning_rate * self.gradients[l]
        self.weights0_[l] = self.weights0_[l] - self.learning_rate * self.gradients0[l]

    def pre_algo_sgd_momentum(self):
        pass # TODO (homework)

    def algo_sgd_momentum(self, l):
        pass # TODO: self.weights_[l], self.weights0_[l] to be updated (l is a layer index)

    def pre_algo_rmsprop(self):
        pass # TODO (homework)

    def algo_rmsprop(self, l):
        pass # TODO: self.weights_[l], self.weights0_[l] to be updated (l is a layer index)

    def pre_algo_adam(self):
        pass # TODO (homework)

    def algo_adam(self, l):
        pass # TODO: self.weights_[l], self.weights0_[l] to be updated (l is a layer index)

    def fit(self, X, y):
        np.random.seed(self.seed)
        self.activation_ = getattr(MLPApproximator, self.activation_name)
        self.activation_d_ = getattr(MLPApproximator, self.activation_name + "_d")
        self.initialization_ = getattr(MLPApproximator, ("he_" if self.activation_name == "relu" else "glorot_") + self.initialization_name)
        self.targets_activation_ = getattr(MLPApproximator, self.targets_activation_name)
        self.targets_activation_d_ = getattr(MLPApproximator, self.targets_activation_name + "_d")
        self.loss_ = getattr(MLPApproximator, self.loss_name)
        self.loss_d_ = getattr(MLPApproximator, self.loss_name + "_d")
        self.pre_algo_ = getattr(self, "pre_algo_" + self.algo_name)
        self.algo_ = getattr(self, "algo_" + self.algo_name)
        self.weights_ = [None] # so that network inputs are considered layer 0, and actual layers of neurons are numbered 1, 2, ...
        self.weights0_ = [None] # so that network inputs are considered layer 0, and actual layers of neurons are numbered 1, 2, ...
        m, n = X.shape
        if len(y.shape) == 1:
            y = np.array([y]).T
        self.n_ = n
        self.n_targets_ = 1 if len(y.shape) == 1 else y.shape[1]
        self.n_params = 0
        for l in range(len(self.structure) + 1):
            n_in = n if l == 0 else self.structure[l - 1]
            n_out = self.structure[l] if l < len(self.structure) else self.n_targets_
            w = self.initialization_(n_in, n_out)
            w0 = np.zeros((n_out, 1), dtype=np.float32)
            self.weights_.append(w)
            self.weights0_.append(w0)
            self.n_params += w.size
            self.n_params += w0.size
        t1 = time.time()
        if self.verbosity_e > 0:
            print(f"FIT [total of weights (params): {self.n_params}]")
        self.pre_algo_() # if some preparation needed
        n_batches, batch_ranges = MLPApproximator.prepare_batch_ranges(m, self.batch_size)
        self.t = 0
        for e in range(self.n_epochs):
            t1_e = time.time()
            if e % self.verbosity_e == 0 or e == self.n_epochs - 1:
                print("-" * 3)
                print(f"EPOCH {e + 1}/{self.n_epochs}:")
                self.forward(X)
                loss_e_before = np.mean(self.loss_(self.signals[-1], y))
            p = np.random.permutation(m)
            for b in range(n_batches):
                indexes = p[batch_ranges[b] : batch_ranges[b + 1]]
                X_b = X[indexes]
                y_b = y[indexes]
                self.forward(X_b)
                loss_b_before = np.mean(self.loss_(self.signals[-1], y_b))
                self.backward(y_b)
                for l in range(1, len(self.structure) + 2):
                    self.algo_(l)
                if (e % self.verbosity_e == 0 or e == self.n_epochs - 1) and b % self.verbosity_b == 0:
                    self.forward(X_b)
                    loss_b_after = np.mean(self.loss_(self.signals[-1], y_b))
                    print(f"[epoch {e + 1}/{self.n_epochs}, batch {b + 1}/{n_batches} -> loss before: {loss_b_before}, loss after: {loss_b_after}]")
                self.t += 1
            t2_e = time.time()
            if e % self.verbosity_e == 0 or e == self.n_epochs - 1:
                self.forward(X)
                loss_e_after = np.mean(self.loss_(self.signals[-1], y))
                self.history_weights[e] = copy.deepcopy(self.weights_)
                self.history_weights0[e] = copy.deepcopy(self.weights0_)
                print(f"ENDING EPOCH {e + 1}/{self.n_epochs} [loss before: {loss_e_before}, loss after: {loss_e_after}; epoch time: {t2_e - t1_e} s]")
        t2 = time.time()
        if self.verbosity_e > 0:
            print(f"FIT DONE. [time: {t2 - t1} s]")

    def forward(self, X_b):
        self.signals = [None] * (len(self.structure) + 2)
        self.signals[0] = X_b
        L = len(self.structure)
        b = X_b.shape[0]
        ones = np.ones((1, b), dtype=np.float32)
        for l in range(1, L + 2): # l = 1, 2, ..., L, L + 1
            X_l = self.signals[l - 1]
            S_l = (self.weights_[l].dot(X_l.T) + self.weights0_[l].dot(ones)).T
            activation = self.activation_ if l <= L else self.targets_activation_
            self.signals[l] = activation(S_l)

    def backward(self, y_b):
        self.deltas = [None] * len(self.signals)
        self.gradients = [None] * len(self.signals)
        self.gradients0 = [None] * len(self.signals)
        y_MLP = self.signals[-1]
        self.deltas[-1] = self.targets_activation_d_(y_MLP) * self.loss_d_(y_MLP, y_b)
        L = len(self.structure)
        b = y_b.shape[0]
        ones = np.ones((b, 1), dtype=np.float32)
        for l in range(L, 0, -1): # l = L, L - 1, ..., 1
            S_lm1 = self.signals[l - 1]
            if l > 1:
                self.deltas[l - 1] = self.activation_d_(S_lm1) * (self.deltas[l].dot(self.weights_[l]))
            self.gradients[l] = self.deltas[l].T.dot(S_lm1)
            self.gradients0[l] = self.weights_[l].T.dot(ones)

# TODO: carry out backward computations throughout layers

    def predict(self, X):
        self.forward(X)
        y_pred = self.signals[-1]
        if self.n_targets_ == 1:
            y_pred = y_pred[:, 0]
        return y_pred