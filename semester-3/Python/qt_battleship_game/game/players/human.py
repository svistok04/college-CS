from game.board import Board
from game.ships import ShipManager
import random


def get_random_orientation():
    positions = ['horizontal']
    return random.choice(positions)


def get_random_coordinates():
    x = random.randint(0, 9)
    y = random.randint(0, 9)
    return x, y

class Human:
    def __init__(self):
        self._ships = ShipManager()
        self._board = Board(self._ships)

    def get_ships(self):
        return self._ships

    def get_board(self):
        return self._board

    def place_ships_randomly(self):
        for name, ship in self._ships.ships.items():
            while not ship.is_set:
                coordinates = get_random_coordinates()
                orientation = get_random_orientation()
                ship.orientation = orientation
                if self._board.check_if_placeable(coordinates, orientation, name):
                    self._board.place_ship(coordinates, orientation, name)
                    ship._is_set = True

    def fire(self, board, coordinates):
        cell = board.get_cell(coordinates)
        if not cell.has_been_hit:
            for name, ship in board.ships.ships.items():
                if coordinates in ship.coordinates:
                    print("there's a ship", name, "at", coordinates)
            cell.has_been_hit = True
            return True
        return False

