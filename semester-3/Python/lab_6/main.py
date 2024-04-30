import collections

# Zadanie 1

print("Zadanie 1")

lorem_ipsum = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec a diam lectus. Sed sit amet ipsum mauris. " \
                "Maecenas congue ligula ac quam viverra nec consectetur ante hendrerit. Donec et mollis dolor. " \
                "Praesent et diam eget libero egestas mattis sit amet vitae augue. Nam tincidunt congue enim, " \
                "ut porta lorem lacinia consectetur. Donec ut libero sed arcu vehicula ultricies a non tortor. " \
                "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aenean ut gravida lorem. " \
                "Ut turpis felis, pulvinar a semper sed, adipiscing id dolor. Pellentesque auctor nisi id magna " \
                "consequat sagittis. Curabitur dapibus enim sit amet elit pharetra tincidunt feugiat nisl " \
                "imperdiet. Ut convallis libero in urna ultrices accumsan. Donec sed odio eros. Donec viverra " \
                "mi quis quam pulvinar at malesuada arcu rhoncus. Cum sociis natoque penatibus et magnis dis " \
                "parturient montes, nascetur ridiculus mus. In rutrum accumsan ultricies. Mauris vitae nisi at " \
                "sem facilisis semper ac in est. "

lorem_counter = collections.Counter(lorem_ipsum.
                                    replace('.', '').
                                    replace(',', '').
                                    lower().
                                    split())

for item, key in lorem_counter.items():
    print(f"Word {item} and its number of occurrences: {key}")

# Zadanie 2

print("Zadanie 2")

table = [["sunny", 85, 85, False, "no"],
         ["sunny", 80, 90, True, "no"],
         ["overcast", 83, 86, False, "yes"],
         ["rainy", 70, 96, False, "yes"],
         ["rainy", 68, 80, False, "yes"],
         ["rainy", 65, 70, True, "no"],
         ["overcast", 64, 65, True, "yes"],
         ["sunny", 72, 95, False, "no"],
         ["sunny", 69, 70, False, "yes"],
         ["rainy", 75, 80, False, "yes"],
         ["sunny", 75, 70, True, "yes"],
         ["overcast", 72, 90, True, "yes"],
         ["overcast", 81, 75, False, "yes"],
         ["rainy", 71, 91, True, "no"]]

outlook = collections.Counter(table[i][0] for i in range(len(table)))
temperature = collections.Counter(table[i][1] for i in range(len(table)))
humidity = collections.Counter(table[i][2] for i in range(len(table)))
windy = collections.Counter(table[i][3] for i in range(len(table)))
play = collections.Counter(table[i][4] for i in range(len(table)))
number_of_elements = sum(outlook.values())

for key in outlook.keys():
    print(f"Probability of {key} outlook: {(outlook[key] / number_of_elements):.3f}")
for key in temperature.keys():
    print(f"Probability of {key}F temperature: {(temperature[key] / number_of_elements):.3f}")
for key in humidity.keys():
    print(f"Probability of {key}% humidity: {(humidity[key] / number_of_elements):.3f}")
print(f"Probability of windy weather: {(windy[True] / number_of_elements):.3f}")
print(f"Probability of calm weather: {(windy[False] / number_of_elements):.3f}")
print(f"Probability of deciding to go out to play: {(play['yes'] / number_of_elements):.3f}")
print(f"Probability of deciding to stay home: {(play['no'] / number_of_elements):.3f}")


# Zadanie 3

print("Zadanie 3")

print(collections.OrderedDict(sorted(outlook.items(), key=lambda i: i[1])))
print(collections.OrderedDict(sorted(temperature.items(), key=lambda i: i[1])))
print(collections.OrderedDict(sorted(humidity.items(), key=lambda i: i[1])))
print(collections.OrderedDict(sorted(windy.items(), key=lambda i: i[1])))
print(collections.OrderedDict(sorted(play.items(), key=lambda i: i[1])))

# Zadanie 4

print("Zadanie 4")

defdict = collections.defaultdict(lambda: int(5))

key1 = input("Enter the first key: ")
print(f"The value for the first key {key1} is {defdict[key1]}")
defdict[key1] += 1
key2 = input("Enter the second key: ")
print(f"The value for the second key {key2} is {defdict[key2]}")
defdict[key2] += 1
key3 = input("Enter the third key: ")
print(f"The value for the third key {key3} is {defdict[key3]}")
defdict[key3] += 1
key4 = input("Enter the fourth key: ")
print(f"The value for the fourth key {key4} is {defdict[key4]}")
defdict[key4] += 1
key5 = input("Enter the fifth key: ")
print(f"The value for the fifth key {key5} is {defdict[key5]}")
defdict[key5] += 1

# Zadanie 5

print("Zadanie 5")

palindrome = "kajak"

is_a_palindrome = True

palindrome_deque = collections.deque([*palindrome])
while len(palindrome_deque) > 1:
    if palindrome_deque.pop() != palindrome_deque.popleft():
        is_a_palindrome = False
        break


if not is_a_palindrome:
    print(f"{palindrome} is not a palindrome")
else:
    print(f"{palindrome} is a palindrome")
