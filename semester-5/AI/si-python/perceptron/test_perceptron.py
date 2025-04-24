import numpy as np
import time
from matplotlib import pyplot as plt
from perceptron import SimplePerceptron, SimplePerceptronNonLinear
from mpl_toolkits.mplot3d import Axes3D  # For surface plots

def fake_data(m=100):
    X = np.zeros((m, 2))
    half = m // 2
    X[:, 0] = np.random.rand(m)
    X[:half, 1] = np.random.rand(half) * 0.4999
    X[half:, 1] = np.random.rand(half) * 0.4999 + 0.5001
    y = np.ones(m, dtype=np.int8)
    y[half:] = -1

    return X, y

def fake_data_sinus(m=100):
    X = np.zeros((m, 2))
    half = m // 2
    X[:, 0] = np.random.uniform(0.0, 2*np.pi, m)
    X[:, 1] = np.random.uniform(-1, 1, m)
    y = np.ones(m, dtype=np.int8)
    y[np.abs(np.sin(X[:, 0])) > np.abs(X[:, 1])] = -1

    return X, y

def test_linear():
    X, y = fake_data(m=6)
    clf = SimplePerceptron(learning_rate=1e-6)
    t1 = time.time()
    clf.fit(X, y)
    t2 = time.time()
    print(f'weights: {clf.w_}')
    print(f'steps {clf.k_}')
    print(f'time: {t2 - t1} s')
    print(f'ACC: {clf.score(X, y)}')
    x1 = np.array([0.0, 1.0])
    x2 = -(clf.w_[0] + clf.w_[1] * x1) / clf.w_[2]
    plt.plot(x1, x2)
    plt.scatter(X[:, 0], X[:, 1], c=y, marker='.')
    plt.show()

def test_non_linear(learning_rate=1.0, dimensions=60, k_max=10000, sigma=0.2):
    np.random.seed(0)
    t = time.time()
    X, y = fake_data_sinus(m=2000)
    X[:, 0] = (X[:, 0] - np.pi) / (np.pi) # normalization
    print(f'x1 min {np.min(X[:, 0])}, x1 max {np.max(X[:, 0])}, x2 min {np.min(X[:, 1])}, x2 max {np.max(X[:, 1])}')
    clf = SimplePerceptronNonLinear(learning_rate=learning_rate, dimensions=dimensions, k_max=k_max, sigma=sigma)

    t1 = time.time()
    clf.fit(X, y)
    t2 = time.time()
    print(f'weights: {clf.w_}')
    print(f'steps {clf.k_}')
    print(f'time: {t2 - t1} s')
    print(f'ACC: {clf.score(X, y)}')


    x1_range = np.linspace(-1, 1, 200)
    x2_range = np.linspace(-1, 1, 200)
    X1, X2 = np.meshgrid(x1_range, x2_range)
    grid_points = np.c_[X1.ravel(), X2.ravel()]

    Z = clf.decision_function(grid_points).reshape(X1.shape)
    plt.figure(figsize=(8, 6))
    plt.scatter(X[:, 0], X[:, 1], c=y, edgecolors='k', facecolors='none', marker='o', cmap='coolwarm', s=30)
    plt.scatter(clf.C_[:, 0], clf.C_[:, 1], c='k', edgecolors='k', marker='o', s=60)

    # plt.contourf(X1, X2, Z, levels=20, cmap='RdYlGn', alpha=0.7)
    plt.contour(X1, X2, Z, levels=[0], colors='black', linewidths=2)
    plt.title("Contour Plot of Decision Boundary")
    plt.xlabel(r'$x_1$')
    plt.ylabel(r'$x_2$')
    plt.show()

    fig = plt.figure(figsize=(10, 8))
    ax = fig.add_subplot(111, projection='3d')
    ax.plot_surface(X1, X2, Z, cmap='coolwarm', alpha=0.8, linewidth=0, antialiased=True)
    ax.set_title("Surface Plot of Weighted Sum (No Thresholding)")
    ax.set_xlabel(r'$x_1$')
    ax.set_ylabel(r'$x_2$')
    ax.set_zlabel("Weighted Sum")
    plt.show()

    plt.contourf(X1, X2, Z, levels=20, cmap='RdYlBu', alpha=0.7)
    plt.show()



if __name__ == '__main__':
    np.random.seed(0)
    # for j in range(36, 37):
    #     for i in range(20, 201):
    #         k_max = i * 25
    #         print(f'dimension {j}, k_max {k_max}')
    #         test_non_linear(dimensions=j, k_max=k_max)

test_non_linear()