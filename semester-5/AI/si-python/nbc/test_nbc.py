import numpy as np
import csv
from sklearn.preprocessing import LabelEncoder

from nbc import NBCDiscrete, NBCContinuous

def read_wine_data(path):
    D = np.genfromtxt(path, delimiter=',')
    X = D[:, 1:]
    y = D[:, 0].astype(np.int8)
    return X, y

def read_mushroom_data(path):

    with open(path, 'r') as f:
        lines = f.readlines()

    data = [line.strip().split(',') for line in lines]
    data = np.array(data)

    y = data[:, 0]
    X = data[:, 1:]

    X[X == '?'] = 'missing'

    encoder = LabelEncoder()
    y = encoder.fit_transform(y)
    X_encoded = np.array([encoder.fit_transform(col) for col in X.T]).T

    return X_encoded, y


def read_college_data(path):
    D = np.genfromtxt(path, delimiter=';', dtype=str, skip_header=1)
    X = D[:, :-1].astype(float)
    y = D[:, -1]
    encoder = LabelEncoder()
    y = encoder.fit_transform(y)
    return X, y

def train_test_split(X, y, train_ratio=0.75):
    m = X.shape[0]
    indexes = np.random.permutation(m)
    X = X[indexes]
    y = y[indexes]
    i = int(np.round(train_ratio * m))
    X_train = X[:i]
    y_train = y[:i]
    X_test = X[i:]
    y_test = y[i:]
    return X_train, y_train, X_test, y_test

def discretize(X, bins, mins_ref=None, maxes_ref=None):
    if mins_ref is None:
        mins_ref = np.min(X, axis=0)
        maxes_ref = np.max(X, axis=0)

    X_d = np.clip(np.int8((X - mins_ref) / (maxes_ref - mins_ref) * bins), 0, bins - 1)
    return X_d, mins_ref, maxes_ref

def process_data(name, loader, path, bins=5, train_ratio=0.75, laplace=False, logs=False):
    np.random.seed(0)
    print(name)
    X, y = loader(path)
    if name != "Mushrooms":
        X_train, y_train, X_test, y_test = train_test_split(X, y, train_ratio)
        X_train_d, mins_ref, maxes_ref = discretize(X_train, bins)
        X_test_d, _, _ = discretize(X_test, bins, mins_ref, maxes_ref)
    else:
        X_train_d, y_train, X_test_d, y_test = train_test_split(X, y, train_ratio)
    n = X.shape[1]
    #domain_sizes = np.ones(n, dtype=np.int8) * bins
    domain_sizes = np.array([len(np.unique(X_train_d[:, j])) for j in range(n)], dtype=np.int8)

    clf = NBCDiscrete(domain_sizes, laplace, logs)
    clf.fit(X_train_d, y_train)
    # print(clf.PY_)
    acc_train = clf.score(X_train_d, y_train)
    acc_test = clf.score(X_test_d, y_test)
    print(f"LaPlace {laplace}")
    print(f"logs {logs}")
    print(f"ACCs -> TRAIN: {acc_train}, TEST: {acc_test} \n")
    return acc_train, acc_test, clf.division_by_zero

def add_zombie_features(X, num_features, mode="random", discrete=False, num_categories=10):
    m, n = X.shape
    if mode == "constant":
        zombie_features = np.zeros((m, num_features), dtype=int if discrete else float)
    elif mode == "random":
        if discrete:
            # Generate random discrete values in the range [0, num_categories)
            zombie_features = np.random.randint(0, num_categories, size=(m, num_features))
        else:
            # Generate random continuous values
            zombie_features = np.random.rand(m, num_features)

    return np.hstack((X, zombie_features))

def process_data_with_zombies(name, loader, path, bins=5, train_ratio=0.75, laplace=False, logs=False, zombie_features=0, zombie_mode="random"):
    np.random.seed(0)
    print(name)
    X, y = loader(path)

    # Add zombie features
    if zombie_features > 0:
        X = add_zombie_features(X, zombie_features, mode=zombie_mode, discrete=(name == "Mushrooms"))

    if name != "Mushrooms":
        X_train, y_train, X_test, y_test = train_test_split(X, y)
        X_train_d, mins_ref, maxes_ref = discretize(X_train, bins)
        X_test_d, _, _ = discretize(X_test, bins, mins_ref, maxes_ref)
    else:
        X_train_d, y_train, X_test_d, y_test = train_test_split(X, y)

    n = X.shape[1]
    # domain_sizes = np.ones(n, dtype=np.int8) * bins
    domain_sizes = np.array([len(np.unique(X_train_d[:, j])) for j in range(n)], dtype=np.int16)
    print(np.max(domain_sizes))

    clf = NBCDiscrete(domain_sizes, laplace, logs)
    clf.fit(X_train_d, y_train)

    acc_train = clf.score(X_train_d, y_train)
    acc_test = clf.score(X_test_d, y_test)
    print(f"ACCs -> TRAIN: {acc_train}, TEST: {acc_test} \n")

    return acc_train, acc_test, clf.division_by_zero

def process_data_with_duplication(name, loader, path, bins=5, train_ratio=0.75, laplace=False, logs=False, duplication_factor=1):
    np.random.seed(0)
    print(f"Processing {name} with feature duplication factor: {duplication_factor}")
    X, y = loader(path)

    # Duplicate features
    if duplication_factor > 1:
        X = np.hstack([X] * duplication_factor)

    if name != "Mushrooms":
        X_train, y_train, X_test, y_test = train_test_split(X, y, train_ratio)
        X_train_d, mins_ref, maxes_ref = discretize(X_train, bins)
        X_test_d, _, _ = discretize(X_test, bins, mins_ref, maxes_ref)
    else:
        X_train_d, y_train, X_test_d, y_test = train_test_split(X, y, train_ratio)

    n = X.shape[1]
    print(n)
    # domain_sizes = np.ones(n, dtype=np.int8) * bins
    domain_sizes = np.array([len(np.unique(X_train_d[:, j])) for j in range(n)], dtype=np.int8)
    print(np.max(domain_sizes))

    clf = NBCDiscrete(domain_sizes, laplace, logs)
    clf.fit(X_train_d, y_train)

    acc_train = clf.score(X_train_d, y_train)
    acc_test = clf.score(X_test_d, y_test)
    print(f"ACCs -> TRAIN: {acc_train}, TEST: {acc_test} \n")

    return acc_train, acc_test, clf.division_by_zero

def test_1():
    bin_sizes = [3, 5, 10]
    output_file = "nbc_test_results.csv"
    with open(output_file, mode="w", newline="") as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(["Dataset", "Bins", "Laplace", "Logs", "Train Accuracy", "Test Accuracy", "Division by Zero"])

        for name, loader, path in datasets:
            for bins in bin_sizes:
                for laplace in [True, False]:
                    for logs in [True, False]:
                        acc_train, acc_test, div_zero = process_data(
                            name, loader, path, bins=bins, laplace=laplace, logs=logs
                        )
                        writer.writerow([name, bins, laplace, logs, acc_train, acc_test, div_zero])

def test_2():
    zombie_feature_counts = [0, 5, 10, 20, 50]

    csv_filename = "zombie_features_test_results.csv"
    with open(csv_filename, mode="w", newline="") as file:
        writer = csv.writer(file)
        writer.writerow(["Dataset", "Zombie Features", "Train Accuracy", "Test Accuracy"])
        for name, loader, path in datasets:
            for num_zombies in zombie_feature_counts:
                acc_train, acc_test, div_zero = process_data_with_zombies(
                    name, loader, path, bins=5, laplace=True, logs=True, zombie_features=num_zombies
                )
                writer.writerow([name, num_zombies, acc_train, acc_test])

def test_3():

    duplication_factors = [1, 2, 3, 5, 10]

    csv_filename = "duplication_features_test_results.csv"

    with open(csv_filename, mode="w", newline="") as file:
        writer = csv.writer(file)
        writer.writerow(["Dataset", "Duplication Factor", "Train Accuracy", "Test Accuracy", "Division by Zero"])

        for name, loader, path in datasets:
            for factor in duplication_factors:
                acc_train, acc_test, div_zero = process_data_with_duplication(
                    name, loader, path, bins=5, laplace=True, logs=True, duplication_factor=factor
                )
                writer.writerow([name, factor, acc_train, acc_test, div_zero])

def process_continuous(name, loader, path, train_ratio=0.75, logs=False):

    np.random.seed(0)
    print(f"Processing {name} (continuous)")

    X, y = loader(path)

    X_train, y_train, X_test, y_test = train_test_split(X, y, train_ratio)

    clf = NBCContinuous(logs)

    clf.fit(X_train, y_train)

    acc_train = clf.score(X_train, y_train)
    acc_test = clf.score(X_test, y_test)

    print(f"ACCs -> TRAIN: {acc_train}, TEST: {acc_test} \n")

    return acc_train, acc_test

def test_4():
    datasets_continuous = [
        ("Wine", read_wine_data, "wine.data"),
        ("College", read_college_data, "data.csv"),
    ]

    csv_filename = "continuous_test_results.csv"

    with open(csv_filename, mode="w", newline="") as file:
        writer = csv.writer(file)
        writer.writerow(["Dataset", "Logs", "Train Accuracy", "Test Accuracy"])

        for name, loader, path in datasets_continuous:
            for logs in [True, False]:
                acc_train, acc_test = process_continuous(
                    name, loader, path, logs=logs
                )
                writer.writerow([name, logs, acc_train, acc_test])


datasets = [
    ("Wine", read_wine_data, "wine.data"),
    ("Mushrooms", read_mushroom_data, "agaricus-lepiota.data"),
    ("College", read_college_data, "data.csv"),
]
#
# test_1()
test_2()
test_3()
test_4()