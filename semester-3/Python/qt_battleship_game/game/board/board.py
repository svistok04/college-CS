from game.ships import Ship, Carrier, Battleship, Cruiser, Destroyer, Submarine
class Board:
    class Cell:
        def __init__(self):
            self._has_ship = False
            self._buffer = False
            self._has_been_hit = False

        @property
        def has_ship(self):
            return self._has_ship

        @has_ship.setter
        def has_ship(self, value):
            self._has_ship = value

        @property
        def buffer(self):
            return self._buffer

        @buffer.setter
        def buffer(self, value):
            self._buffer = value

        @property
        def has_been_hit(self):
            return self._has_been_hit

        @has_been_hit.setter
        def has_been_hit(self, value):
            self._has_been_hit = value

    def __init__(self, ships):
        self._ships = ships
        self._board = [[self.Cell() for _ in range(10)] for _ in range(10)]

    def __iter__(self):
        for row in self._board:
            for cell in row:
                yield cell

    def get_cell(self, coordinates):
        return self._board[coordinates[0]][coordinates[1]]

    @property
    def ships(self):
        return self._ships

    def check_if_placeable(self, coordinates, orientation, name):
        row, col = coordinates
        ship_length = self._ships.get_ship(name).length
        if col < 0 or col > 9 or row < 0 or row > 9:
            return False
        match orientation:
            case 'horizontal':
                if col + ship_length > 10:
                    return False
                for i in range(ship_length):
                    if self._board[row][col + i].has_ship or self._board[row][col + i].buffer:
                        return False
            case 'vertical':
                if row - ship_length < -1:
                    return False
                for i in range(ship_length):
                    if self._board[row - i][col].has_ship or self._board[row - i][col].buffer:
                        return False
        return True

    def place_ship(self, coordinates, orientation, name):
        row = coordinates[0]
        col = coordinates[1]
        ship = self._ships.get_ship(name)
        ship.coordinates = []
        ship.neighboring_coordinates = []
        match orientation:
            case 'horizontal':
                for i in range(ship.length):
                    self._board[row][col + i].has_ship = True
                    ship.coordinates.append((row, col + i))
                    if row - 1 >= 0:
                        ship.neighboring_coordinates.append((row - 1, col + i))
                        self._board[row - 1][col + i].buffer = True
                    if row + 1 < 10:
                        ship.neighboring_coordinates.append((row + 1, col + i))
                        self._board[row + 1][col + i].buffer = True
                if col - 1 >= 0:
                    ship.neighboring_coordinates.append((row, col - 1))
                    self._board[row][col - 1].buffer = True
                    if row - 1 >= 0:
                        ship.neighboring_coordinates.append((row - 1, col - 1))
                        self._board[row - 1][col - 1].buffer = True
                    if row + 1 < 10:
                        ship.neighboring_coordinates.append((row + 1, col - 1))
                        self._board[row + 1][col - 1].buffer = True
                if col + ship.length < 10:
                    ship.neighboring_coordinates.append((row, col + ship.length))
                    self._board[row][col + ship.length].buffer = True
                    if row - 1 >= 0:
                        ship.neighboring_coordinates.append((row - 1, col + ship.length))
                        self._board[row - 1][col + ship.length].buffer = True
                    if row + 1 < 10:
                        ship.neighboring_coordinates.append((row + 1, col + ship.length))
                        self._board[row + 1][col + ship.length].buffer = True
            case 'vertical':
                for i in range(ship.length):
                    ship.coordinates.append((row - i, col))
                    self._board[row - i][col].has_ship = True
                    if col - 1 >= 0:
                        ship.neighboring_coordinates.append((row - i, col - 1))
                        self._board[row - i][col - 1].buffer = True
                    if col + 1 < 10:
                        ship.neighboring_coordinates.append((row - i, col + 1))
                        self._board[row - i][col + 1].buffer = True
                if row - ship.length >= 0:
                    ship.neighboring_coordinates.append((row - ship.length, col))
                    self._board[row - ship.length][col].buffer = True
                    if col - 1 >= 0:
                        ship.neighboring_coordinates.append((row - ship.length, col - 1))
                        self._board[row - ship.length][col - 1].buffer = True
                    if col + 1 < 10:
                        ship.neighboring_coordinates.append((row - ship.length, col + 1))
                        self._board[row - ship.length][col + 1].buffer = True
                if row + 1 < 10:
                    ship.neighboring_coordinates.append((row + 1, col))
                    self._board[row + 1][col].buffer = True
                    if col - 1 >= 0:
                        ship.neighboring_coordinates.append((row + 1, col - 1))
                        self._board[row + 1][col - 1].buffer = True
                    if col + 1 < 10:
                        ship.neighboring_coordinates.append((row + 1, col + 1))
                        self._board[row + 1][col + 1].buffer = True
            # case 'horizontal-left':
            #     for i in range(ship.length):
            #         self._board[row][col - i].has_ship = True
            #         ship.coordinates.append((row, col - i))
            # case 'vertical-down':
            #     for i in range(ship.length):
            #         self._board[row + i][col].has_ship = True
            #         ship.coordinates.append((row + i, col))

