# # Zadanie 1
# print("Zadanie 1")
# lorem_ipsum = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec a diam lectus. Sed sit amet ipsum mauris. " \
#                 "Maecenas congue ligula ac quam viverra nec consectetur ante hendrerit. Donec et mollis dolor. " \
#                 "Praesent et diam eget libero egestas mattis sit amet vitae augue. Nam tincidunt congue enim, " \
#                 "ut porta lorem lacinia consectetur. Donec ut libero sed arcu vehicula ultricies a non tortor. " \
#                 "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aenean ut gravida lorem. " \
#                 "Ut turpis felis, pulvinar a semper sed, adipiscing id dolor. Pellentesque auctor nisi id magna " \
#                 "consequat sagittis. Curabitur dapibus enim sit amet elit pharetra tincidunt feugiat nisl " \
#                 "imperdiet. Ut convallis libero in urna ultrices accumsan. Donec sed odio eros. Donec viverra " \
#                 "mi quis quam pulvinar at malesuada arcu rhoncus. Cum sociis natoque penatibus et magnis dis " \
#                 "parturient montes, nascetur ridiculus mus. In rutrum accumsan ultricies. Mauris vitae nisi at " \
#                 "sem facilisis semper ac in est. "
#
# zbior = set(lorem_ipsum.replace('.', '').replace('', '').lower().split())
# tablica = list(lorem_ipsum.replace('.', ' ').replace('', '').lower().split())
#
# print(zbior)
# print(len(tablica))
# print(len(zbior))
#
# # Zadanie 2
# print("Zadanie 2")
# A = {2, 4, 6, 8, 10}
# B = {2, 4, 5, 10}
#
# print(A.issubset(B))
# print(A.issuperset(B))
# print(A.intersection(B))
# print(A.union(B))
# print(A.difference(B))
# print(A.symmetric_difference(B))
# # Zadanie 3
# print("Zadanie 3")
# iloczyn_kartezjanski = [[a, b] for a in A for b in B]
# print(*iloczyn_kartezjanski)
# print(len(iloczyn_kartezjanski))
#
# # Zadanie 4
# print("Zadanie 4")
# polish_numbers = {
#     0 : "zero",
#     1 : "jeden",
#     2 : "dwa",
#     3 : "trzy",
#     4 : "cztery",
#     5 : "pięć",
#     6 : "sześć",
#     7 : "siedem",
#     8 : "osiem",
#     9 : "dziewięć",
#     10 : "dziesięć",
#     11 : "jedenaście",
#     14 : "czternascie",
#     15 : "pietnascie",
#     16 : "szesnascie",
#     19 : "dziewietnascie",
#     20: "dwadzieścia",
#     30: "trzydzieści",
#     40: "czterdzieści"
# }
#
# liczba = int(input('Wpisz liczbe '))
#
#
# cyfra_dziesiatek = int(liczba/10)
#
# cyfra_jednosci = liczba - cyfra_dziesiatek * 10
#
# if 11 == liczba or 14 <= liczba <= 16 or 19 == liczba:
#     slowo = polish_numbers[liczba]
# if 12 <= liczba <= 13 or 17 <= liczba <= 19:
#     slowo = polish_numbers[cyfra_jednosci] + "naście"
#
# if 0 <= liczba <= 10:
#     slowo = polish_numbers[liczba]
#
# if 5 <= cyfra_dziesiatek <= 9:
#     slowo = polish_numbers[cyfra_dziesiatek] + "dziesiąt"
# if 2 <= cyfra_dziesiatek <= 4:
#     slowo = polish_numbers[cyfra_dziesiatek*10]
#
# if cyfra_jednosci != 0 and cyfra_dziesiatek > 1:
#     slowo = slowo + " " + polish_numbers[cyfra_jednosci]
#
#
# print("To jej slowna reprezentacja:", slowo)
#

# Zadanie 5
print("Zadanie 5")

base64_dict = {0: "A", 1: "B", 2: "C", 3: "D", 4: "E",
                5: "F", 6: "G", 7: "H", 8: "I", 9: "J",
                10: "K", 11: "L", 12: "M", 13: "N", 14: "O",
                15: "P", 16: "Q", 17: "R", 18: "S", 19: "T",
                20: "U", 21: "V", 22: "W", 23: "X", 24: "Y",
                25: "Z", 26: "a", 27: "b", 28: "c", 29: "d",
                30: "e", 31: "f", 32: "g", 33: "h", 34: "i",
                35: "j", 36: "k", 37: "l", 38: "m", 39: "n",
                40: "o", 41: "p", 42: "q", 43: "r", 44: "s",
                45: "t", 46: "u", 47: "v", 48: "w", 49: "x",
                50: "y", 51: "z", 52: "0", 53: "1", 54: "2",
                55: "3", 56: "4", 57: "5", 58: "6", 59: "7",
                60: "8", 61: "9", 62: "+", 63: "/"}


def ascii_to_base64(target):
    result = ""
    chars_binary = "".join([bin(ord(char))[2:].zfill(8) for char in [*target]])
    for i in range(int(len(chars_binary)/24)):
        base64_decimal = [int(binary, 2) for binary in
                          [chars_binary[i:i + 6].ljust(6, '0') for i in range(0, len(chars_binary), 6)]]
        result = [base64_dict[char] for char in base64_decimal]
    if len(result) % 4 != 0:
        result.extend('=' * (4 - (len(result) % 4)))
    return result


print("".join(ascii_to_base64('TEST')))

