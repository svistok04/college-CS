import numpy
import copy


def zad1(n: int) -> numpy.array:
    arr = numpy.zeros([n, n], dtype=int)
    for i in range(n):
        for j in range(n):
            arr[i][j] = pow(i + 1, j)


    return arr


# zad1 = zad1(5)
# print(zad1)


def zad2(n: int) -> numpy.array:
    arr = numpy.zeros([n, n], dtype=int)
    for i in range(0, pow(n, 2), n):
        for j in range(n):
            if (i/n) % 2 == 0:
                arr[int(i/n)][j] = i + j + 1
            else:
                arr[int(i/n)][n-j-1] = i + j + 1
    return arr


zad2 = zad2(4)
print(zad2)


def zad3(n: int) -> numpy.array:
    arr = numpy.zeros([n, n], dtype=int)
    direction = "up"
    level = 0
    for i in range(0, pow(n, 2), n):
        match direction:
            case "up":
                for j in range(n):
                    index1 = n - j - 1
                    index2 = int(i/n)
                    arr[n - j - 1][int(i/n)] = i + j + 1
                direction = "right"
            case "right":
                for j in range(1, n):
                    index1 = j
                    index2 = int(-i/n)
                    arr[int(i/n) - 1][j] = i + j
                direction = "down"
            case "down":
                for j in range(1, n):
                    index1 = j
                    index2 = int(i/n) - 1
                    arr[j][int(i/n) + 1] = i + j - 1
                direction = "left"
            case "left":
                for j in range(1, n - 1):
                    index1 = int(i/n)
                    index2 = -j
                    arr[int(i/n)][-j] = i + j
                level += 1
                direction = "up"
    return arr



def zad3(n: int) -> numpy.array:
    arr = numpy.zeros((n, n), dtype=int)
    direction = "up"
    level = 0
    value = 1

    while value <= n * n:
        match direction:
            case "up":
                for i in range(level, n - level):
                    arr[n - 1 - i][level] = value
                    value += 1
                direction = "right"
            case "right":
                for i in range(level + 1, n - level):
                    arr[level][i] = value
                    value += 1
                direction = "down"
            case "down":
                for i in range(level + 1, n - level):
                    arr[i][n - 1 - level] = value
                    value += 1
                direction = "left"
            case "left":
                for i in range(level + 1, n - 1 - level):
                    arr[n - 1 - level][n - 1 - i] = value
                    value += 1
                direction = "up"
                level += 1

    return arr


zad3 = zad3(6)
print(zad3)


def zad4(arr: numpy.array) -> numpy.array:
    output = numpy.array(arr, dtype=int)
    boolean_array = (arr % 3 == 0) | (arr % 5 == 0)
    output[boolean_array] = 0
    return output


zad4 = zad4(zad2)
print(zad4)


def graph_matrices_no_weights(neighborhoods):
    num_nodes = len(neighborhoods)

    neighborhood_matrix = numpy.zeros((num_nodes, num_nodes), dtype=int)
    edge_list = []

    for i, neighbors in enumerate(neighborhoods):
        for j in neighbors:
            neighborhood_matrix[i, j] = 1
            edge_list.append((i, j))

    num_edges = len(edge_list)
    incidence_matrix = numpy.zeros((num_nodes, num_edges), dtype=int)

    for edge_idx, (start, end) in enumerate(edge_list):
        incidence_matrix[start, edge_idx] = -1
        incidence_matrix[end, edge_idx] = 1

    return neighborhood_matrix, incidence_matrix


neighborhoods_example = [
    {1, 3, 5},
    {2},
    {},
    {},
    {3, 4},
    {2}
]

neighborhood_matrix, incidence_matrix = graph_matrices_no_weights(neighborhoods_example)
print(neighborhood_matrix)
print(incidence_matrix)

