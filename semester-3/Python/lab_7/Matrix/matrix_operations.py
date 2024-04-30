from typing import List, Union


def addition(a: List[List[Union[int, float]]], b: List[List[Union[int, float]]]) -> List[List[Union[int, float]]]:
    """
    adds two matrices of the same size.
    \n
    >>> addition(a, b) # will add matrix a and matrix b and return the result
    """
    if len(a) != len(b) and len(a[0]) != len(b[0]):
        raise ValueError
    res = [[0] * len(a)] * len(a)
    # res = [x for x in [[0] * len(a[0])] * len(a)]
    for i in range(len(a)):
        for j in range(len(a[0])):
            res[i][j] = a[i][j] + b[i][j]
    return res


def addition_by_const(a: List[List[Union[int, float]]], b: Union[int, float]) -> List[List[Union[int, float]]]:
    """
    adds a constant (diagonal matrix) to a square matrix.
    :param a:
    :param b:
    :return:
    """
    if len(a) != len(a[0]):
        return a
    res = [[b if i == j else 0 for i in range(len(a))] for j in range(len(a))]
    for i in range(len(a)):
        for j in range(len(a)):
            res[i][j] += a[i][j]
    return res


def multiplication(a: List[List[Union[int, float]]], b: List[List[Union[int, float]]]) -> List[List[Union[int, float]]]:
    # multiplies two matrices
    # (the number of columns of the first matrix must correspond to the number of rows of the second one.
    if len(a[0]) != len(b):
        raise ValueError("")
    res = [[0] * len(b[0])] * len(a)  # cols * rows
    # res = [x for x in [[0] * len(b[0])] * len(a)]
    # c = [0 for _ in [[0] * len(b[0])] * len(a)]
    # c = [[0 for _ in range(len(b[0]))] for _ in range(len(a))]
    for i in range(len(a)):
        for j in range(len(b[0])):
            for k in range(len(b)):
                res[i][j] += a[i][k] * b[k][j]
    return res


def multiplication_by_const(a: List[List[Union[int, float]]], b: Union[int, float]) -> List[List[Union[int, float]]]:
    # multiplies a matrix by a const value.
    res = [[a[j][i] for i in range(len(a))] for j in range(len(a))]
    for i in range(len(a)):
        for j in range(len(a[0])):
            res[i][j] *= b
    return res


def hadamard_product(a: List[List[Union[int, float]]], b: List[List[Union[int, float]]]) -> List[List[Union[int, float]]]:
    # performs an operation of Hadamard product.
    if len(a) != len(b) or len(a[0]) != len(b[0]):
        raise ValueError("")
    res = [[0] * len(a[0])] * len(a)
    # res = [x[:] for x in [[0] * len(a[0])] * len(a)]
    for i in range(len(a)):
        for j in range(len(a[0])):
            res[i][j] = a[i][j] * b[i][j]
    return res


def kronecker_product(a: List[List[Union[int, float]]], b: List[List[Union[int, float]]]) -> List[List[Union[int, float]]]:
    # performs an operation of Kronecker product.
    res = [[0] * len(a[0])] * len(a)
    # res = [x[:] for x in [[0] * len(a[0])] * len(a)]
    for i in range(len(a)):
        for j in range(len(a[0])):
            res[i][j] = multiplication_by_const(b, a[i][j])
    return res
