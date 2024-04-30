from .players.computer import Computer
from .players.human import Human

class GameManager:
    def __init__(self):
        self._human = Human()
        self._computer = Computer(self._human)
        self._game_status = 'continue'

    @property
    def computer(self):
        return self._computer

    @property
    def human(self):
        return self._human

    @property
    def game_status(self):
        return self._game_status

    def check_game_status(self):
        if all(ship.is_sunk(self._computer.get_board()) for ship in self._computer.get_board().ships.ships.values()):
            self._game_status = 'human won'
            return self._game_status

        if all(ship.is_sunk(self._human.get_board()) for ship in self._human.get_board().ships.ships.values()):
            self._game_status = 'computer won'
            return self._game_status

        self._game_status = 'continue'
        return self._game_status
