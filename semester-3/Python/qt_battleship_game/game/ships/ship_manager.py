from .ship import Carrier, Battleship, Cruiser, Destroyer, Submarine


class ShipManager:
    def __init__(self):
        self._ships = {"submarine-1": Submarine(),
                       "submarine-2": Submarine(),
                       "submarine-3": Submarine(),
                       "destroyer-1": Destroyer(),
                       "destroyer-2": Destroyer(),
                       "cruiser-1": Cruiser(),
                       "battleship-1": Battleship(),
                       "carrier-1": Carrier()}

    def __iter__(self):
        return iter(self._ships)

    def get_ship(self, name):
        return self._ships[name]

    @property
    def ships(self):
        return self._ships