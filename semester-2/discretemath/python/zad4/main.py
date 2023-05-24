from sympy import isprime, gcd
from random import randint, seed
from numpy import prod

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
lines = []
file_opened = True
try:
    file = open("data.txt")
    lines = file.readlines()
    file.close()
except FileNotFoundError:
    file_opened = False
while True:
    j = 0
    continued = False  # used to return to the start of the while-loop if case 2 fails to perform its task.
    try:
        choice = int(input())
    except ValueError:
        print("Please, provide only such numbers as: 1, 2 or 3!")
        continue
    if choice not in range(1, 4):
        print("Please, provide only such numbers as: 1, 2 or 3!")
        continue
    match choice:
        case 1:
            try:
                n0 = n = int(input())
            except ValueError:
                print("The number must be a positive integer!")
                continued = True
        case 2:
            if lines:
                try:
                    n0 = n = int(lines[i])  # Process each line at a time sequentially every time the user
                    i += 1  # enters '2' until the end of the file is reached.
                except IndexError:
                    print("No more lines to read from!")
                    continued = True
                except ValueError:
                    print("The number must be a positive integer!")
                    continued = True
            else:
                if file_opened:
                    print("File data.txt is empty!")
                else:
                    print("File data.txt was never opened since it does not exist, hence "
                          "there are no number to work on.")
                continued = True
        case 3:
            print("That was entirely your choice!")
            quit()

    if n0 < 0:
        print("Only positive integers are allowed!")
        continued = True

    if continued:
        continue  # return to the start of the while-loop.

    if isprime(n):
        print("Oops!", n, "is a prime number itself.")
    elif n == 1:
        print("Sorry, but factorization does not apply to the number 1 as it is a special case "
              "being the smallest positive integer.")
    else:
        factors = []
        while n > 1 and not isprime(n) and j < 7000:
            file = rho_pollard(n)
            if isprime(file):
                factors.append(file)
                n //= file
            j += 1
        if n > 1:
            factors.append(n)

        shouldPrint = True

        for factor in factors:
            if not isprime(factor):
                print("Unfortunately, it's not possible to factorize", n0)
                shouldPrint = False
                break

        if shouldPrint:
            print("Prime factors of", n0, "are:")
            for factor in factors:
                print(factor)
