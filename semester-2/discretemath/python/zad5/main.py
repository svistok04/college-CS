from math import gcd


def check_if_moduli_are_coprime(n_):
    return all(gcd(n_[i], n_[j]) == 1 for i in range(len(n_)) for j in range(i + 1, len(n_)))  # compares all moduli
    # using two for loops and returns True if gcd() always returns True for all pairs.

    # alternatively:

    # for i in range(len(n_)):
        # for j in range(i + 1, len(n_)):
            # if gcd(n_[i], n_[j]) != 1:
                # return False

    # return True


# Chinese remainder theorem
def chinese_remainder_theorem(rems, mods): # rems - short for remainder, mods - short for moduli
    n = 1
    # n, the product of all moduli
    for ni in mods:
        n *= ni

    x = 0
    Ni = []
    Mi = []
    for i, (ai, ni) in enumerate(zip(rems, mods)):

        # "N, the product of all moduli except the current one (ni) being iterated over in the congruence
        Ni.append(int(n / ni))

        # extended Euclidean algorithm (EEA) recursive, where Ni (N) and ni (mod - current modulus)
        # are passed as arguments
        def euclidean_extended(N, mod):
            if mod == 0:
                return N, 1, 0
            gcd, p, q = euclidean_extended(mod, N % mod)

            return gcd, q, p - (N // mod) * q

        # getting M, the modulo inverse of N, from the function's return
        _, M, _ = euclidean_extended(Ni[i] % ni, ni)

        Mi.append(M)

        # accumulating the contribution of the current remainder (ai), N (Ni[i]) and M (Mi[i]) to the result
        x += ai * Ni[i] * Mi[i]

    return int(x % n), Ni, Mi, n


print("Hi! Please, enter your system of congruences as follows: x ≡ a mod n, where 'a' is a remainder and 'n' "
      "is modulus. Print 'finish' if you're done.")
remainders = []
moduli = []
user_finished = False
while not user_finished:
    rem = input("x ≡ ")

    if rem.lower() == "finished":
        print("Nice! You're done, now be happy with your solution (if there's any).")
        user_finished = True
    else:
        mod = input("mod ")

        try:
            rem_append = int(rem)
            mod_append = int(mod)
            if rem_append > 0 and mod_append > 0:
                remainders.append(rem_append)
                moduli.append(mod_append)
            else:
                print("You're supposed to enter natural numbers(!) for your system of congruences! "
                      "Try again or type 'finished' if you're done.")
        except ValueError:
            print("You're supposed to enter natural numbers(!) for your system of congruences! "
                  "Try again or type 'finished' if you're done.")


if check_if_moduli_are_coprime(moduli):
    result, Ni, Mi, n = chinese_remainder_theorem(remainders, moduli)
    print("The n is", n)
    print("The Ns are", Ni)
    print("The Ms are", Mi)

    print("The solved system of congruences can be represented as follows:")
    for remainder, modulus in zip(remainders, moduli):
        print(f"{result} ≡ {remainder} mod {modulus}")

else:
    print("Unfortunately, the moduli are not coprime, "
          "which means the Chinese Remainder Theorem cannot be applied in this case")
