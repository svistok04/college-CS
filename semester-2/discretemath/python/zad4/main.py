from sympy import isprime, gcd
from random import randint, seed
seed()


# Pollard's rho algorithm
def rho_pollard(n):
    x = y = randint(1, n - 1)  # using randint with a bigger scale of numbers because the original x = y = 2
    c = randint(1, n - 1)  # and c = 1 (a constant for formula x^2 + c) often won't work.
    d = 1
    while d == 1:
        x = (x * x + c) % n  # g(x)
        y = (y * y + c) % n
        y = (y * y + c) % n  # g(g(y))
        d = gcd(abs(x - y), n)  # gcd(|x - y|, n)
    return d


print("Make your choice: 1 to enter your own number, 2 to read a line"
      " from the file 'data.txt' and 3 to quit the program.")
n0 = n = 0
i = 0
try:
    f = open("data.txt")
    lines = f.readlines()
except FileNotFoundError:
    print("File data.txt not found!")
while True:
    continued = False  # used to return to the start of the while-loop if case 2 fails to perform its task.
    choice = int(input())
    match choice:
        case 1:
            n0 = n = int(input())
        case 2:
            if lines:
                try:
                    n0 = n = int(lines[i])  # Process each line at a time sequentially every time the user
                    i += 1  # enters '2' until the end of the file is reached.
                except IndexError:
                    print("No more lines to read from!")
                    continued = True
            else:
                print("File data.txt is empty!")
                continued = True
        case 3:
            print("That was entirely your choice!")
            quit()

    if continued:
        continue  # return to the start of the while-loop.

    if isprime(n):
        print("Oops!", n, "is a prime number itself.")
    else:
        factors = []

        while n > 1 and not isprime(n):
            f = rho_pollard(n)
            if isprime(f):
                factors.append(f)
                n //= f
        if n > 1:
            factors.append(n)

        print("Prime factors of", n0, "are:")
        for factor in factors:
            print(factor)
