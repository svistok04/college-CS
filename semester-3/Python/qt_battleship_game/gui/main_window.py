import PyQt5.QtWidgets as qtw
import PyQt5.QtGui as qtg
import PyQt5.QtCore as qtc
from .main_screen import MainScreen
from .game_setup_screen import GameSetupScreen
from .game_screen import GameScreen
from .ships_placement_screen import ShipsPlacementScreen

class MainWindow(qtw.QMainWindow):

    def __init__(self, game_manager):
        super().__init__()
        self._game_manager = game_manager
        self.setWindowTitle("Battleship")
        self.central_widget = qtw.QStackedWidget()
        self.setCentralWidget(self.central_widget)
        self.setFixedSize(1400, 900)
        self.setStyleSheet("background: #e8d3d3")
        self.main_screen = MainScreen()
        self.game_setup_screen = GameSetupScreen(self._game_manager)
        self.ships_placing_screen = ShipsPlacementScreen(self._game_manager)
        self.central_widget.addWidget(self.main_screen)
        self.central_widget.addWidget(self.game_setup_screen)
        self.central_widget.addWidget(self.ships_placing_screen)
        self.central_widget.setCurrentWidget(self.main_screen)
        self.main_screen.play_clicked.connect(lambda: self.central_widget.setCurrentWidget(self.game_setup_screen))
        self.game_setup_screen.start_game_clicked.connect(self.start_game if
                                                          self.game_setup_screen.player_file_selected
                                                          else lambda:
        self.central_widget.setCurrentWidget(self.ships_placing_screen)
        )
        self.game_setup_screen.back_clicked.connect(lambda: self.central_widget.setCurrentWidget(self.main_screen))
        self.ships_placing_screen.start_game_clicked.connect(self.start_game)
        self.ships_placing_screen.back_clicked.connect(lambda: self.central_widget.setCurrentWidget(self.game_setup_screen))
        self.show()

    def start_game(self):
        player_flag = self.game_setup_screen.player_file_selected
        computer_flag = self.game_setup_screen.computer_file_selected
        self.game_screen = GameScreen(self._game_manager, player_flag, computer_flag)
        self.central_widget.addWidget(self.game_screen)
        self.central_widget.setCurrentWidget(self.game_screen)
