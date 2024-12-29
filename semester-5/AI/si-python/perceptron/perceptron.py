import numpy as np
from sklearn.base import BaseEstimator, ClassifierMixin
class SimplePerceptron(BaseEstimator, ClassifierMixin):

    def __init__(self, learning_rate=1.0):
        self.learning_rate = learning_rate

    def fit(self, X, y):
        self.classes_ = np.unique(y) # zakladamy dwie klasy i ze self.classes_[0] -> -1, self.classes_[1] -> +1
        m, n = X.shape
        yy = np.ones(m, dtype=np.int8)
        yy[y == self.classes_[0]] = -1
        self.w_ = np.zeros(n + 1) # licznik wag
        self.k_ = 0 # licznik kroków
        X_extended = np.hstack((np.ones((m, 1)), X))
        while True:
            # E = [] # indeksy błędów
            # for i in range(m):
            #     s = self.w_.dot(X_extended[i])
            #     phi = 1 if s > 0.0 else -1
            #     if phi != yy[i]:
            #         E.append(i)
            S = self.w_.dot(X_extended.T)
            E = np.where(S * yy <= 0)[0]
            if len(E) == 0:
                # print(f'X {X_extended}')
                # print(f'w {self.w_}')
                # print(f'S {S}')
                break
            i = np.random.choice(E)
            self.w_ = self.w_ + self.learning_rate * yy[i] * X_extended[i]
            self.k_ += 1

    def predict(self, X):
        return self.classes_[(self.decision_function(X) > 0.0) * 1]

    def decision_function(self, X):
        m = X.shape[0]
        X_extended = np.hstack((np.ones((m, 1)), X))
        return self.w_.dot(X_extended.T)

class SimplePerceptronNonLinear(BaseEstimator, ClassifierMixin):
    def __init__(self, learning_rate=1.0, dimensions=20, k_max=500, sigma=0.5):
        self.learning_rate = learning_rate
        self.dimensions = dimensions
        self.k_max = k_max
        self.sigma = sigma

    def fit(self, X, y):
        np.random.seed(0)
        self.classes_ = np.unique(y)
        m, n = X.shape
        yy = np.ones(m, dtype=np.int8)
        yy[y == self.classes_[0]] = -1
        self.C_ = np.random.uniform(-1, 1, (self.dimensions, 2))
        self.Z_ = np.exp(-(np.sum((X[:, np.newaxis, :] - self.C_) ** 2, axis=2)) / (2 * self.sigma ** 2))
        # print('INIT')
        # print(f'X = {X}')
        # print(f'C = {self.C_}')
        # print(f'Z = {self.Z_}')
        Z_extended = np.hstack((np.ones((m, 1)), self.Z_))
        self.w_ = np.random.uniform(-0.01, 0.01, self.dimensions + 1)
        # self.w_ = np.zeros(self.dimensions + 1)
        self.k_ = 0
        while self.k_ < self.k_max:
            S = self.w_.dot(Z_extended.T)
            E = np.where(S * yy <= 0)[0]
            if len(E) == 0:
                break
            print(len(E))
            # self.w_ = self.w_ + self.learning_rate * yy[E].dot(Z_extended[E])
            i = np.random.choice(E)
            self.w_ = self.w_ + self.learning_rate * y[i] * Z_extended[i]
            # print(f'we\'re at step {self.k_}')
            # print(f'S {S}')
            # print(f'E {E}')
            # print(f'i {i}')
            # print(f'w_ {self.w_}')
            self.k_ += 1

    def predict(self, X):
        return self.classes_[(self.decision_function(X) > 0.0) * 1]

    def decision_function(self, X):
        m = X.shape[0]
        Z = np.exp(-np.sum((X[:, np.newaxis, :] - self.C_) ** 2, axis=2) / (2 * self.sigma ** 2))
        Z_extended = np.hstack((np.ones((m, 1)), Z))
        return self.w_.dot(Z_extended.T)
