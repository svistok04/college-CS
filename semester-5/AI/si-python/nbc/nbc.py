import numpy as np
from sklearn.base import BaseEstimator, ClassifierMixin


class NBCDiscrete(BaseEstimator, ClassifierMixin):

    def __init__(self, domain_sizes, laplace=False, logs=False):
        self.domain_sizes = domain_sizes
        self.laplace = laplace
        self.logs = logs
        self.division_by_zero = False

    def fit(self, X, y):
        self.classes_ = np.unique(y)
        K = self.classes_.size
        m, n = X.shape
        q_max = np.max(self.domain_sizes)
        self.PY_ = np.zeros(K)
        self.P_ = np.zeros((K, n, q_max)) # 3 * 13 * 5; P_[2,7,4] = Prob(X_7 = 4 | Y = 2)
        yy = np.zeros(m, dtype=np.int8)
        for y_index, label in enumerate(self.classes_):
            indexes = y == label
            self.PY_[y_index] = np.mean(indexes)
            yy[indexes] = y_index

        for i in range(m):
            for j in range(n):
                self.P_[yy[i], j, X[i, j]] += 1

        for y_index in range(K):

            if not self.laplace:
                if (self.P_[y_index] <= 0).any():
                    self.division_by_zero = True
                self.P_[y_index] /= self.PY_[y_index] * m
                if self.logs:
                    self.P_[y_index] = np.log(self.P_[y_index])
            else:
                for j in range(n):
                    self.P_[y_index, j] = (self.P_[y_index, j] + 1) / (self.PY_[y_index] * m + self.domain_sizes[j])
                    if self.logs:
                        self.P_[y_index, j] = np.log(self.P_[y_index, j])
        if self.logs:
            self.PY_ = np.log(self.PY_)


    def predict(self, X):
        return self.classes_[np.argmax(self.predict_proba(X), axis=1)]

    def predict_proba(self, X):
        m, n = X.shape
        K = self.classes_.size
        probas = np.ones((m, K))
        for i in range(m):
            for y_index in range(K):
                probas[i, y_index] = self.PY_[y_index]
                for j in range(n):
                    if self.logs:
                        probas[i, y_index] += self.P_[y_index, j, X[i, j]]
                    else:
                        probas[i, y_index] *= self.P_[y_index, j, X[i, j]]
          # probas /= np.sum(probas[i])
        return np.exp(probas) if self.logs else probas


class NBCContinuous(BaseEstimator, ClassifierMixin):
    def __init__(self, logs=False):
        self.logs = logs
        self.classes_ = None
        self.means_ = None
        self.stds_ = None
        self.PY_ = None

    def fit(self, X, y):
        self.classes_ = np.unique(y)
        K = self.classes_.size
        m, n = X.shape

        self.means_ = np.zeros((K, n))
        self.stds_ = np.zeros((K, n))
        self.PY_ = np.zeros(K)

        for y_index, label in enumerate(self.classes_):
            X_class = X[y == label]
            self.PY_[y_index] = X_class.shape[0] / m
            self.means_[y_index, :] = np.mean(X_class, axis=0)
            self.stds_[y_index, :] = np.std(X_class, axis=0)

        if self.logs:
            self.PY_ = np.log(self.PY_)

    def predict_proba(self, X):
        m, n = X.shape
        K = self.classes_.size
        probas = np.zeros((m, K))

        for y_index in range(K):
            likelihood = (
                    1 / (np.sqrt(2 * np.pi) * self.stds_[y_index])
                    * np.exp(-0.5 * ((X - self.means_[y_index]) / self.stds_[y_index]) ** 2))
#             likelihood[np.isnan(likelihood)] = 0

            if self.logs:
                probas[:, y_index] = np.sum(np.log(likelihood), axis=1) + self.PY_[y_index]
            else:
                probas[:, y_index] = np.prod(likelihood, axis=1) * self.PY_[y_index]

        if self.logs:
            probas = np.exp(probas)

        probas /= np.sum(probas, axis=1, keepdims=True)
        return probas

    def predict(self, X):
        return self.classes_[np.argmax(self.predict_proba(X), axis=1)]