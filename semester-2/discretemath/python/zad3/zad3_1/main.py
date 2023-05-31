import matplotlib.pyplot as plt
import time
import pandas
import numpy
from math import sqrt, ceil, factorial
from random import randint, seed

seed()


# naive method 1 - check if the given number "n" is divisible by any from 2 to n - 1, if it is, return "is not prime",
# otherwise return "is prime"
def naive_1(n):
    if n <= 1:
        return "is not prime"
    for i in range(2, n - 1):
        if n % i == 0:
            return "is not prime"

    return "is prime"


# naive method 2 - check if the given number "n" is divisible by any from 2 to sqrt(n) rounded up, if it is,
# return "is not prime", otherwise return "is prime"
def naive_2(n):
    if n <= 1:
        return "is not prime"
    for i in range(2, ceil(sqrt(n))):
        if n % i == 0:
            return "is not prime"

    return "is prime"


# Wilson theorem
def wilson_theorem(n):
    if n <= 1:
        return "is not prime"

    return "is prime" if (factorial(n - 1) + 1) % n == 0 else "is not prime"


# Fermat's little theorem reversed - if the number doesn't fit to the Fermat's little theorem - return "is not prime".
# the method is checked multiple times (5 times) because there is a possibility that the generated number is a
# Carmichael number, which can satisfy the theorem even if it is not a prime number
def fermat_little_theorem_reversed(n):
    if n <= 1:
        return "is not prime"

    for _ in range(5):
        rand = randint(2, n - 1)
        if pow(rand, n - 1) % n != 1:
            return "is not prime"

    return "is prime"


# a list to format specific columns later
columns_to_format = ['Naive Method 1', 'Naive Method 2', 'Wilson\'s theorem', 'Fermat\'s Little Theorem Reversed']

# dataframe generating
table_all = pandas.DataFrame(columns=['Number', 'Naive Method 1', 'Naive Method 2', 'Wilson\'s theorem',
                                      'Fermat\'s Little Theorem Reversed', 'Is Prime'])
try:
    table_prime = pandas.read_excel("prime_numbers.xlsx")
except FileNotFoundError:
    table_prime = pandas.DataFrame(columns=['Number', 'Naive Method 1', 'Naive Method 2', 'Wilson\'s theorem',
                                            'Fermat\'s Little Theorem Reversed'])
try:
    table_composite = pandas.read_excel("composite_numbers.xlsx")
except FileNotFoundError:
    table_composite = pandas.DataFrame(columns=['Number', 'Naive Method 1', 'Naive Method 2', 'Wilson\'s theorem',
                                                'Fermat\'s Little Theorem Reversed'])


numbers = []

upper_bound = 800000

# generate random numbers
for i in range(10):
    numbers.append(randint(100, upper_bound))


# run all 4 methods
for n in numbers:
    start_time = time.time()

    result = is_prime = naive_1(n)

    naive_1_time = "%.9f" % (time.time() - start_time)

    print(f"Method 1 gives the result {is_prime} for the number {n} and it took {naive_1_time} seconds to compute")

    start_time = time.time()

    is_prime = naive_2(n)

    naive_2_time = "%.9f" % (time.time() - start_time)

    print(f"Method 2 gives the result {is_prime} for the number {n} and it took {naive_2_time} seconds to compute")

    start_time = time.time()

    is_prime = wilson_theorem(n)

    wilson_time = "%.9f" % (time.time() - start_time)

    print(f"Method 3 gives the result {is_prime} for the number {n} and it took {wilson_time} seconds to compute")

    start_time = time.time()

    is_prime = fermat_little_theorem_reversed(n)

    fermat_time = "%.9f" % (time.time() - start_time)

    print(f"Method 4 gives the result {is_prime} for the number {n} and it took {fermat_time} seconds to compute\n")

    # add composite results
    if result == "is not prime":
        table_composite = table_composite._append({
            'Number': n,
            'Naive Method 1': naive_1_time,
            'Naive Method 2': naive_2_time,
            'Wilson\'s theorem': wilson_time,
            'Fermat\'s Little Theorem Reversed': fermat_time
        }, ignore_index=True)
    # add prime results
    else:
        table_prime = table_prime._append({
            'Number': n,
            'Naive Method 1': naive_1_time,
            'Naive Method 2': naive_2_time,
            'Wilson\'s theorem': wilson_time,
            'Fermat\'s Little Theorem Reversed': fermat_time
        }, ignore_index=True)

# format columns of times of all methods in the tables with prime and composite numbers as floats with 9 decimal places,
# sort them and save each to a file
table_prime[columns_to_format] = table_prime[columns_to_format].astype(float).applymap(lambda x: "%.9f" % x)
table_prime.sort_values(by='Number').to_excel('prime_numbers.xlsx', index=False)

table_composite[columns_to_format] = table_composite[columns_to_format].astype(float).applymap(lambda x: "%.9f" % x)
table_composite.sort_values(by='Number').to_excel('composite_numbers.xlsx', index=False)

# merge previous two tables to a table with all numbers, sort this table, add a column "Is Prime" with "yes" and "no"
# values, save this table to a file
table_all = pandas.merge(table_prime, table_composite, how="outer") \
    .sort_values(by='Number')
table_all['Is Prime'] = numpy.where(table_all['Number'].isin(table_prime['Number']), 'Yes', 'No')
table_all.to_excel('all_numbers.xlsx', index=False)

# creating a plot with time to compute for all methods for all numbers

# extract columns from the table
numbers = table_all['Number']
methods = ['Naive Method 1', 'Naive Method 2', 'Wilson\'s theorem', 'Fermat\'s Little Theorem Reversed']

# create a dictionary to associate methods with colors
method_colors = {
    'Naive Method 1': 'red',
    'Naive Method 2': 'blue',
    'Wilson\'s theorem': 'green',
    'Fermat\'s Little Theorem Reversed': 'purple'
}

plt.figure(figsize=(30, 55))

# plot the data points (different colors for each method)
for method in methods:
    times = table_all[method]
    plt.scatter(numbers, times, c=method_colors[method], label=method)

times = pandas.to_numeric(times, errors='coerce')

# add labels and title
plt.xlabel('Number')
plt.ylabel('Time')
plt.title('Computation time for all 4 methods')

# failed to change the way it displays values on the y-axis
# min_time = float(numpy.min(time))
# max_time = float(numpy.max(time))
# step = pandas.to_numeric(time, errors='coerce').mean()
# step /= times.size
# yticks = numpy.arange(min_time, max_time + step, step)
# plt.yticks(yticks)

# hide y-axis tick labels if there are many data points, as displaying all of them would occupy too much space
# and makes it unreadable anyways.
if numbers.size > 230:
    plt.yticks([])

# add a legend
plt.legend()
# add a grid
plt.grid(True)

if numbers.size < 5000:
    plt.savefig("4methods.svg")

plt.savefig("4methods.png", dpi=150)
