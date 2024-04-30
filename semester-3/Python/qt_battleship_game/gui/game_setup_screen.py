import sys

import PyQt5.QtWidgets as qtw
import PyQt5.QtGui as qtg
import PyQt5.QtCore as qtc


class GameSetupScreen(qtw.QWidget):
    start_game_clicked = qtc.pyqtSignal()
    back_clicked = qtc.pyqtSignal()

    def __init__(self, game_manager):
        super().__init__()
        self.player_file_selected = False
        self.computer_file_selected = False
        layout = qtw.QVBoxLayout(self)
        self.setLayout(layout)
        self.game_manager = game_manager
        start_game_button = qtw.QPushButton("Start game")
        start_game_button.setFixedSize(250, 63)
        start_game_button.clicked.connect(self.start_game_clicked.emit)
        start_game_button.setStyleSheet("QPushButton { background-color: black; color: white; font-size: 24px; "
                                        "padding: 10px; border-radius: 15px; }"
                                        "QPushButton:hover { background-color: grey; }")
        back_button = qtw.QPushButton("Back")
        back_button.setFixedSize(250, 63)
        back_button.clicked.connect(self.back_clicked.emit)
        back_button.setStyleSheet("QPushButton { background-color: black; color: white; font-size: 24px; "
                                  "padding: 10px; border-radius: 15px; }"
                                  "QPushButton:hover { background-color: grey; }")

        player_layout = qtw.QHBoxLayout()
        self.load_players_board = qtw.QCheckBox("Load player's board from file")
        self.load_players_board.setEnabled(False)  # Initially disabled
        self.load_players_board.setStyleSheet("color: black")
        self.load_players_board.stateChanged.connect(self.player_checkbox_changed)
        player_select_button = qtw.QPushButton("Select File")
        player_select_button.clicked.connect(self.select_player_file)
        player_select_button.setStyleSheet("QPushButton { background-color: black; color: white; font-size: 14px; "
                                           "padding: 10px; border-radius: 10px; font-weight: bold; }"
                                           "QPushButton:hover { background-color: grey; }")
        player_select_button.setFixedSize(90, 40)
        player_layout.addWidget(self.load_players_board, alignment=qtc.Qt.AlignLeft)
        player_layout.addWidget(player_select_button, alignment=qtc.Qt.AlignLeft)
        player_widget = qtw.QWidget()
        player_widget.setLayout(player_layout)
        player_widget.setFixedWidth(525)

        computer_layout = qtw.QHBoxLayout()
        self.load_computers_board = qtw.QCheckBox("Load computer's board from file")
        self.load_computers_board.setStyleSheet("color: black")
        self.load_computers_board.stateChanged.connect(self.computer_checkbox_changed)
        computer_select_button = qtw.QPushButton("Select File")
        computer_select_button.clicked.connect(self.select_computer_file)
        computer_select_button.setStyleSheet("QPushButton { background-color: black; color: white; font-size: 14px; "
                                             "padding: 10px; border-radius: 10px; font-weight: bold; }"
                                             "QPushButton:hover { background-color: grey; }")
        computer_select_button.setFixedSize(90, 40)
        computer_layout.addWidget(self.load_computers_board, alignment=qtc.Qt.AlignLeft)
        computer_layout.addWidget(computer_select_button, alignment=qtc.Qt.AlignLeft)
        computer_widget = qtw.QWidget()
        computer_widget.setLayout(computer_layout)
        computer_widget.setFixedWidth(500)

        checkboxes_layout = qtw.QVBoxLayout()
        checkboxes_layout.setAlignment(qtc.Qt.AlignCenter)
        checkboxes_layout.addWidget(player_widget, alignment=qtc.Qt.AlignCenter)
        checkboxes_layout.addWidget(computer_widget, alignment=qtc.Qt.AlignCenter)
        checkboxes_widget = qtw.QWidget()
        checkboxes_widget.setFixedWidth(500)
        checkboxes_widget.setLayout(checkboxes_layout)

        layout.addStretch(7)
        layout.addWidget(start_game_button, alignment=qtc.Qt.AlignCenter)  # Center the button
        layout.addStretch(1)
        layout.addWidget(back_button, alignment=qtc.Qt.AlignCenter)
        layout.addStretch(1)
        layout.addWidget(checkboxes_widget, alignment=qtc.Qt.AlignCenter)
        layout.addStretch(6)

    def select_player_file(self):
        file_dialog = qtw.QFileDialog(self, "Select Player Board File", "./board_layouts/", "Text Files (*.txt)")
        file_dialog.setStyleSheet("QFileDialog { background-color: black; color: white;}")
        file_name, _ = file_dialog.getOpenFileName()
        if file_name:
            ships = self.read_file(file_name)
            if not ships:
                return
            for name, data in ships.items():
                coords = data['coords']
                orientation = data['orientation']
                if not self.game_manager.human.get_board().check_if_placeable(coords, orientation, name):
                    for ship in self.game_manager.human.get_board().ships.ships.values():
                        ship.is_set = False
                    for cell in self.game_manager.human.get_board():
                        cell.has_ship = False
                        cell.buffer = False
                    self.create_message_box("Error", f"Invalid file format\nWrong ship placement\n{name} at {coords}")
                    return
                self.game_manager.human.get_board().place_ship(coords, orientation, name)
                self.game_manager.human.get_ships().ships[name].is_set = True
                self.game_manager.human.get_ships().ships[name].orientation = orientation
            self.create_message_box("Success", "All ships placed successfully!")
            self.load_players_board.setChecked(True)
            self.load_players_board.setEnabled(True)
            self.player_file_selected = True

    def select_computer_file(self):
        file_dialog = qtw.QFileDialog(self, "Select Computer Board File", "./board_layouts/", "Text Files (*.txt)")
        file_dialog.setStyleSheet("QFileDialog { background-color: black; color: white;}")
        file_name, _ = file_dialog.getOpenFileName()
        if file_name:
            ships = self.read_file(file_name)
            if not ships:
                return
            for name, data in ships.items():
                coords = data['coords']
                orientation = data['orientation']
                if not self.game_manager.computer.get_board().check_if_placeable(coords, orientation, name):
                    for ship in self.game_manager.computer.get_board().ships.ships.values():
                        ship.is_set = False
                    for cell in self.game_manager.computer.get_board():
                        cell.has_ship = False
                        cell.buffer = False
                    self.create_message_box("Error", f"Invalid file format\nWrong ship placement\n{name} at {coords}")
                    return
                self.game_manager.computer.get_board().place_ship(coords, orientation, name)
                self.game_manager.computer.get_ships().ships[name].is_set = True
                self.game_manager.computer.get_ships().ships[name].orientation = orientation
            self.create_message_box("Success", "All ships placed successfully!")
            self.load_computers_board.setChecked(True)
            self.load_computers_board.setEnabled(True)
            self.computer_file_selected = True

    def read_file(self, file_name):
        ships_names = ['submarine-1', 'submarine-2', 'submarine-3', 'destroyer-1', 'destroyer-2', 'cruiser-1',
                       'battleship-1', 'carrier-1']
        ships = {name: {'coords': (999, 999), 'orientation': ''} for name in ships_names}
        with open(file_name, 'r') as file:
            for line in file:
                if len(line.strip().split(': ')) != 2:
                    self.create_message_box("Error", "Invalid file format\n")
                    return False
                ship_name, other = line.strip().split(': ')
                if len(other.split(') ')) != 2:
                    self.create_message_box("Error", "Invalid file format\n")
                    return False
                starting_coord, orientation = other.split(') ')
                orientation = orientation.strip()
                if ship_name not in ships:
                    self.create_message_box("Error", f"Invalid file format\nWrong ship {ship_name}")
                    return False
                x, y = starting_coord.strip().replace('(', '').split(', ')
                ships[ship_name]['coords'] = (int(x), int(y))
                ships[ship_name]['orientation'] = orientation
            for ship_data in ships.values():
                if not (isinstance(ship_data['coords'], tuple) and
                        0 <= ship_data['coords'][0] <= 9 and
                        0 <= ship_data['coords'][1] <= 9):
                    self.create_message_box("Error", "Invalid file format\nWrong coordinates")
                    return False
                if not (isinstance(ship_data['orientation'], str) and
                        (ship_data['orientation'] in ['horizontal', 'vertical'])):
                    self.create_message_box("Error", "Invalid file format\nWrong orientation")
                    return False

        return ships

    def player_checkbox_changed(self, state):
        if state == qtc.Qt.Unchecked:
            self.load_players_board.setEnabled(False)
            self.player_file_selected = False

    def computer_checkbox_changed(self, state):
        if state == qtc.Qt.Unchecked:
            self.load_computers_board.setEnabled(False)
            self.computer_file_selected = False

    def create_message_box(self, tittle, text):
        box = qtw.QMessageBox(self)
        box.setWindowTitle(tittle)
        box.setText(text)
        original_icon = qtg.QPixmap('./resources/critical.png') if tittle == "Error" else qtg.QPixmap('./resources/correct.png')
        icon = qtg.QPixmap(original_icon.size())
        icon.fill(qtg.QColor('black'))
        painter = qtg.QPainter(icon)
        painter.setCompositionMode(qtg.QPainter.CompositionMode_SourceOver)
        painter.drawPixmap(0, 0, original_icon)
        painter.end()
        box.setIconPixmap(icon.scaled(64, 64, qtc.Qt.KeepAspectRatio, qtc.Qt.SmoothTransformation))
        box.setStyleSheet("""
            QMessageBox {
                background-color: black;
                color: white;
            }
            QLabel {
                background-color: black;
                color: white;
            }
            QPushButton {
                background-color: black;
                border: 1px solid gray;
                color: white;
            }
        """)
        box.setStandardButtons(qtw.QMessageBox.Ok)
        box.exec_()
