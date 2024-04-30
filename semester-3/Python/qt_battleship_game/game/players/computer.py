from game.board import Board
from game.ships import ShipManager
import random


def get_random_orientation():
    positions = ['horizontal', 'vertical']
    return random.choice(positions)


def get_random_coordinates():
    x = random.randint(0, 9)
    y = random.randint(0, 9)
    return x, y


class Computer:
    def __init__(self, player):
        self._ships = ShipManager()
        self._board = Board(self._ships)
        self.hit_cells = []
        self.hit_around = []
        self.potential_targets = []
        self.current_target = None
        self.current_orientation = None
        self.player = player
        self.player_ships_left = ['submarine-1',
                                  'submarine-2',
                                  'submarine-3',
                                  'destroyer-1',
                                  'destroyer-2',
                                  'cruiser-1',
                                  'battleship-1',
                                  'carrier-1']

    def get_ships(self):
        return self._ships

    def get_board(self):
        return self._board

    def place_ships(self):
        for name, ship in self._ships.ships.items():
            while not ship.is_set:
                coordinates = get_random_coordinates()
                orientation = get_random_orientation()
                ship.orientation = orientation
                if self._board.check_if_placeable(coordinates, orientation, name):
                    self._board.place_ship(coordinates, orientation, name)
                    ship._is_set = True


    def fire(self):
        if self.potential_targets:
            return self.target_from_list()
        else:
            return self.random_fire()

    def random_fire(self):
        while True:
            x, y = get_random_coordinates()
            cell = self._board.get_cell((x, y))
            if not cell.has_been_hit:
                cell.has_been_hit = True
                if cell.has_ship:
                    self.hit_cells.append((x, y))
                    self.add_cells_around(x, y)
                return x, y

    def target_from_list(self):
        x, y = self.potential_targets.pop(0)
        cell = self._board.get_cell((x, y))
        cell.has_been_hit = True
        if cell.has_ship:
            self.hit_cells.append((x, y))
            if self.current_orientation is None:
                self.determine_orientation(x, y)
                self.hit_around = []
                if self.current_orientation:
                    return self._continue_in_orientation(x, y)
            else:
                return self._continue_in_orientation(x, y)
        return x, y

    def add_cells_around(self, x, y):
        for offset in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
            if 0 <= x + offset[0] < 10 and 0 <= y + offset[1] < 10:
                self.potential_targets.append((x + offset[0], y + offset[1]))

    def determine_orientation(self, hit_x, hit_y):
        for offset in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
            adjacent_cell = (hit_x + offset[0], hit_y + offset[1])
            if adjacent_cell in self.hit_cells:
                if offset[0] == 0:
                    self.current_orientation = 'vertical'
                else:
                    self.current_orientation = 'horizontal'
                return

    def _continue_in_orientation(self, x, y):
        if self.current_orientation == 'horizontal':
            next_cells = [(x + 1, y), (x - 1, y)]
        elif self.current_orientation == 'vertical':
            next_cells = [(x, y + 1), (x, y - 1)]

        for next_x, next_y in next_cells:
            if 0 <= next_x < 10 and 0 <= next_y < 10 and (next_x, next_y) not in self.hit_cells:
                cell = self._board.get_cell((next_x, next_y))
                if not cell.has_been_hit:
                    cell.has_been_hit = True
                    if cell.has_ship:
                        self.hit_cells.append((next_x, next_y))
                    else:
                        self.current_orientation = None
                        self.current_target = None
                        self.potential_targets = []
                    return next_x, next_y

        self.current_orientation = None
        self.current_target = None
        self.potential_targets = []
        return self.random_fire()
