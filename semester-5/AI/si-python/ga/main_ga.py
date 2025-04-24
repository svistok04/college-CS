import numpy as np
import time as time
from knapsack_ga import knapsackGA
import matplotlib.pyplot as plt


def random_knapsack_problem(n=100, scale=10**5, seed=None):
    if seed is not None:
        np.random.seed(seed)    
    items = np.ceil(scale * np.random.rand(n, 2)).astype("int32")
    v = items[:, 0]
    c = items[:, 1]
    C = int(np.ceil(0.5 * 0.5 * n * scale))
    return v, c, C

def knapsack_problem_dp_solve(v, c, C):
    n = v.size
    a = np.zeros((C + 1, n), dtype="int32") # a[i, j] = best pack of knapsack with capacity i using objects from set {0, ..., j - 1}
    b = np.empty((C + 1, n), dtype="object") # back pointers
    for j in range(n):
        b[0, j] = (0, 0)        
    for i in range(1, C + 1):
        if c[0] <= i:
            a[i, 0] = v[0]
            b[i, 0] = (int(i - c[0]), 0)
        else:
            b[i, 0] = (i, -1)
        for j in range(1, n):
            i_prev = int(i - c[j])
            if c[j] > i:
                a[i, j] = a[i, j - 1]
                b[i, j] = (i, j - 1)
            elif a[i, j - 1] >= a[i_prev, j - 1] + v[j]:
                a[i, j] = a[i, j - 1]
                b[i, j] = (i, j - 1)
            else:
                a[i, j] = a[i_prev, j - 1] + v[j]
                b[i, j] = (i_prev, j - 1)    
    solution = np.zeros(n, dtype="int8")
    i = C
    j = n - 1    
    while i > 0 and j >= 0:
        if b[i, j][0] < i:
            solution[j] = 1
        i, j = b[i, j]
    best_pack_value = a[C, n - 1] 
    return best_pack_value, solution                        

def run_test(m=1000, T=100, crossover_type='one_point', selection_name='ranking', la=0, elitism=True):
    n = 100
    scale = 2000
    history = True
    seed_problem = 0
    v, c, C = random_knapsack_problem(n=n, scale=scale, seed=seed_problem)
    print("RANDOM KNAPSACK PROBLEM:")
    print(f"v: {v}")
    print(f"c: {c}")
    print(f"C: {C}")

    print("SOLVING VIA DYNAMIC PROGRAMMING...")
    t1 = time.time()
    best_pack_value, dp_solution = knapsack_problem_dp_solve(v, c, C)
    t2 = time.time()
    print("SOLVING VIA DYNAMIC PROGRAMMING DONE IN: " + str(t2 - t1) + " S.")
    print("SOLUTION: " + str(dp_solution))
    print("BEST PACK VALUE: " + str(best_pack_value))
    print("PACK CAPACITY: " + str(dp_solution.dot(c)))

    print("\nSOLVING VIA GENETIC ALGORITHM...")
    t1 = time.time()
    knapsackga = knapsackGA(v, c, C, m=m, T=T, crossover_type=crossover_type, selection_name=selection_name, la=la, elitism=elitism)
    best_individual = knapsackga.run()
    t2 = time.time()

    pack_value = best_individual.dot(v)
    pack_capacity = best_individual.dot(c)

    print("SOLVING VIA GENETIC ALGORITHM DONE IN: " + str(t2 - t1) + " S.")
    print("BEST INDIVIDUAL: " + str(best_individual))
    print("PACK VALUE: " + str(pack_value))
    print("PACK CAPACITY: " + str(pack_capacity))

    value_ratio = (pack_value / best_pack_value) * 100
    bit_agreement = (np.sum(best_individual == dp_solution) / len(dp_solution)) * 100

    print("\nCOMPARISON METRICS:")
    print(f"VALUE RATIO (GA / DP): {value_ratio:.2f}%")
    print(f"BIT AGREEMENT: {bit_agreement:.2f}%")

    plt.plot(knapsackga.fitness_history)
    plt.xlabel('Generation')
    plt.ylabel('Best Score')
    plt.title('Evolution')
    plt.show()

if __name__ == '__main__':
    run_test(m=1000, T=200, crossover_type='one_point', selection_name='ranking', elitism=True)