class Ship:
    def __init__(self, length):
        self._length = length
        self._orientation = "vertical"
        self._is_set = False
        self._coordinates = []
        self._neighboring_coordinates = []

    @property
    def length(self):
        return self._length

    @property
    def orientation(self):
        return self._orientation

    @orientation.setter
    def orientation(self, value):
        self._orientation = value

    @property
    def is_set(self):
        return self._is_set

    @is_set.setter
    def is_set(self, value):
        self._is_set = value

    @property
    def coordinates(self):
        return self._coordinates

    @coordinates.setter
    def coordinates(self, value):
        self._coordinates = value

    @property
    def neighboring_coordinates(self):
        return self._neighboring_coordinates

    @neighboring_coordinates.setter
    def neighboring_coordinates(self, value):
        self._neighboring_coordinates = value

    def is_sunk(self, board):
        for coordinate in self._coordinates:
            if not board.get_cell(coordinate).has_been_hit:
                return False
        return True


class Submarine(Ship):
    def __init__(self):
        super().__init__(1)


class Destroyer(Ship):
    def __init__(self):
        super().__init__(2)


class Cruiser(Ship):
    def __init__(self):
        super().__init__(3)


class Battleship(Ship):
    def __init__(self):
        super().__init__(4)


class Carrier(Ship):
    def __init__(self):
        super().__init__(5)

