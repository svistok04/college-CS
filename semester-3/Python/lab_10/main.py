class callablePowers:
    def __init__(self, a=0):
        self.a = a
        self.b = 0

    def __call__(self):
        self.b += 1
        return self.a**self.b

first = callablePowers(2)

# for i in range(5):
    # print(first())

class iterativePowers:
    def __init__(self, a=0, start=0, end=0):
        self.a = a
        self.start = start
        self.end = end

    def __iter__(self):
        return self

    def __next__(self):
        if self.start == self.end:
            raise StopIteration
        self.start += 1
        return self.a**self.start

second = iterativePowers(2, 0, 5)

# for power in second:
#     print(power)

class DList:
    class Element:
        def __init__(self, value):
            self.__value = value
            self.next = None
            self.prev = None

        @property
        def value(self):
            return self.__value

    def __init__(self, args):
        self.__root = None
        self.__end = None
        for i in args:
            self.insert(i)

    def insert(self, value):
        new_node = self.Element(value)
        if self.__root is None:
            self.__root = new_node
            self.__end = self.__root
            return

        if value < self.__root.value:
            if self.__root.next is not None:
                self.__root.next.prev = new_node
            self.__root.prev = new_node
            new_node.next = self.__root
            self.__root = new_node
            return

        curr = self.__root
        while curr.next is not None:
            if value < curr.next.value:
                new_node.prev = curr
                new_node.next = curr.next
                curr.next.prev = new_node
                curr.next = new_node
                return
            curr = curr.next

        new_node.prev = curr
        curr.next = new_node
        self.__end = new_node

    def __iter__(self):
        curr = self.__root
        while curr is not None:
            yield curr.value
            curr = curr.next

    def __reversed__(self):
        curr = self.__end
        while curr is not None:
            yield curr.value
            curr = curr.prev

    def __contains__(self, value):
        curr = self.__root
        while curr is not None:
            if curr.value == value:
                return True
            if curr.value > value or curr == self.__end:
                return False
            curr = curr.next

    @property
    def root(self):
        return self.__root

    @property
    def end(self):
        return self.__end


dlista = DList([2, 3, 4, 5])
for i in dlista:
    print(i)
print('\n------------\n')
dlista = DList([8, 10, 9, 13])
dlista.insert(7)
dlista.insert(12)
dlista.insert(15)
for i in dlista:
    print(i)
print('\n------------\n')
for i in reversed(dlista):
    print(i)
print('\n------------\n')
print('Contains 8: ', 8 in dlista)
print('Contains 13: ', 13 in dlista)
print('Contains 15: ', 15 in dlista)
print('Contains 6: ', 6 in dlista)
print('Contains 11: ', 11 in dlista)
print('Contains 17: ', 17 in dlista)
