import PyQt5.QtWidgets as qtw
import PyQt5.QtGui as qtg
import PyQt5.QtCore as qtc
import os


class GameScreen(qtw.QWidget):
    def __init__(self, game_manager, player_flag, computer_flag):
        super().__init__()
        if not computer_flag:
            game_manager.computer.place_ships()
        for name, ship in game_manager.computer.get_board().ships.ships.items():
            print(name, ship.coordinates)
        layout = qtw.QVBoxLayout()
        self.setLayout(layout)
        layout.setAlignment(qtc.Qt.AlignTop)
        filling = qtw.QWidget()
        filling.setFixedHeight(50)
        layout.addWidget(filling)
        self.text = qtw.QLabel()
        computer_ships_left = len([ship for ship in game_manager.computer.get_board().ships.ships.values() if
                                   not ship.is_sunk(game_manager.computer.get_board())])
        self.text.setText(f"It's your turn! Computer got {computer_ships_left} ships left")
        layout.addLayout(self.BoardsGUI(game_manager, self.text))
        layout.addStretch(2)
        layout.addWidget(self.text, alignment=qtc.Qt.AlignCenter)
        self.text.setStyleSheet("color: white; font-size: 50px; font-weight: bold;")
        layout.addStretch(2)
        self.text.show()
        self.create_files(game_manager, player_flag, computer_flag)

    def create_files(self, game_manager, player_flag, computer_flag):
        if not player_flag:
            x = 1
            while True:
                player_path = f"./board_layouts/players_layout{x}.txt"
                if not os.path.isfile(player_path):
                    with open(player_path, 'w') as pf:
                        for name, ship in game_manager.human.get_board().ships.ships.items():
                            start_coord = ship.coordinates[0]
                            orientation = ship.orientation
                            pf.write(f"{name}: ({start_coord[0]}, {start_coord[1]}) {orientation}\n")
                    break
                x += 1

        if not computer_flag:
            x = 1
            while True:
                computer_path = f"./board_layouts/computers_layout{x}.txt"
                if not os.path.isfile(computer_path):
                    with open(computer_path, 'w') as cf:
                        for name, ship in game_manager.computer.get_board().ships.ships.items():
                            start_coord = ship.coordinates[0]
                            orientation = ship.orientation
                            cf.write(f"{name}: ({start_coord[0]}, {start_coord[1]}) {orientation}\n")
                    break
                x += 1

    class BoardsGUI(qtw.QHBoxLayout):
        def __init__(self, game_manager, text):
            super().__init__()
            self.buttons = []
            self.text = text
            self.game_manager = game_manager
            self.players_ships = {}
            self.computer_ships = {}
            self.players_board_game = self.game_manager.human.get_board()
            self.computers_board_game = self.game_manager.computer.get_board()
            self.player_board_widget = self.draw_board("Player")
            self.addWidget(self.player_board_widget)
            self.addSpacerItem(qtw.QSpacerItem(250, 0, qtw.QSizePolicy.Fixed))
            self.computer_board_widget = self.draw_board("Computer")
            self.addWidget(self.computer_board_widget, 2)
            self.draw_ships("Player")
            self.draw_ships("Computer")

        def draw_board(self, board_name):
            board_layout = qtw.QGridLayout()
            for row in range(1, 11):
                label = qtw.QLabel(str(row))
                label.setAlignment(qtc.Qt.AlignCenter)
                label.setStyleSheet("color: black; font-size: 20px; margin-left: 10px;" if board_name == "Computer"
                                    else "color: black; font-size: 20px;")
                board_layout.addWidget(label, row, 0 if board_name == "Player" else 11)

            for col in range(1, 11):
                label = qtw.QLabel(chr(64 + col))
                label.setAlignment(qtc.Qt.AlignCenter)
                label.setStyleSheet("color: black; font-size: 20px;")
                board_layout.addWidget(label, 0, col)

            for row in range(1, 11):
                row_buttons = []
                for col in range(1, 11):
                    button = qtw.QPushButton()
                    row_buttons.append(button)
                    button.setFixedSize(53, 53)
                    # button.setStyleSheet("QPushButton {border: 1px solid black; }"
                    #                    "QPushButton:hover { background-color: grey; }"
                    #                     "QPushButton:pressed { background-color: black; }")
                    if board_name == "Computer":
                        button.clicked.connect(lambda _, r=row, c=col: self.cell_clicked(r - 1, c - 1, board_name))
                    else:
                        button.setEnabled(False)
                    board_layout.addWidget(button, row, col)
                self.buttons.append(row_buttons)
            board_widget = qtw.QWidget()
            board_widget.setLayout(board_layout)
            board_widget.setFixedSize(560, 560)

            return board_widget

        def draw_ships(self, board_name):
            board = self.game_manager.computer.get_board() if board_name == "Computer" else self.game_manager.human.get_board()
            for name, ship in board.ships.ships.items():
                if len(ship.coordinates) != 0:
                    ship_label = qtw.QLabel()
                    ship_label.setObjectName(name)
                    orientation = ship.orientation
                    ship_label.setAttribute(qtc.Qt.WA_TranslucentBackground)
                    x, y = ship.coordinates[0]
                    pixmap = qtg.QPixmap(
                        f"./resources/{name.split('-')[0]}.png") if orientation == "vertical" else qtg.QPixmap(
                        f"./resources/{name.split('-')[0]}-horizontal.png")
                    scaled_pixmap = pixmap.scaled(
                        *ship_sizes[name.split('-')[0]] if orientation == "vertical" else ship_sizes[
                                                                                              name.split('-')[0]][::-1])
                    ship_label.setPixmap(scaled_pixmap)
                    ship_label.setFixedSize(scaled_pixmap.size())
                    ship_label.setFixedSize(*ship_sizes[name.split('-')[0]] if orientation == "vertical"
                    else ship_sizes[name.split('-')[0]][::-1])
                    ship_label.move(y, x)
                    match name.split('-')[0]:
                        case "carrier":
                            if board_name == "Player":
                                if orientation == "vertical":
                                    ship_label.move(y * 53 + 39 + 7 - 1 * y,
                                                    x * 53 + 47 - 1 * x - 53 * (ship.length - 1))
                                elif orientation == "horizontal":
                                    ship_label.move(y * 53 + 39 - 1 * y,
                                                    x * 53 + 32 - 1 * x + 9)
                            elif board_name == "Computer":
                                if orientation == "vertical":
                                    ship_label.move(y * 53 - 1 * y + 5,
                                                    x * 53 - 1 + 12 * x - 55 * (ship.length - 1))
                                elif orientation == "horizontal":
                                    ship_label.move(y * 53 - 1 * y + 3,
                                                    x * 53 - 1 * x + 42)
                        case "battleship":
                            if board_name == "Player":
                                if orientation == "vertical":
                                    ship_label.move(y * 53 + 39 - 1 * y,
                                                    x * 53 + 47 - 1 * x - 53 * (ship.length - 1))
                                elif orientation == "horizontal":
                                    ship_label.move(y * 53 + 39 - 1 * y + 2,
                                                    x * 53 - 1 * x + 40)
                            elif board_name == "Computer":
                                if orientation == "vertical":
                                    ship_label.move(y * 53 - 1 * y + 3,
                                                    x * 53 - 1 * x - 55 * (ship.length - 1) + 50)
                                elif orientation == "horizontal":
                                    ship_label.move(y * 53 - 1 * y,
                                                    x * 53 - 1 * x + 45)
                        case "cruiser":
                            if board_name == "Player":
                                if orientation == "vertical":
                                    ship_label.move(y * 53 + 39 - 1 * y,
                                                    x * 53 + 47 - 40 - 1 * x - 53 * (ship.length - 1))
                                elif orientation == "horizontal":
                                    ship_label.move(y * 53 + 39 - 1 * y,
                                                    x * 53 + 35 - 1 * x + 6)
                            elif board_name == "Computer":
                                if orientation == "vertical":
                                    ship_label.move(y * 53 - 1 * y + 10,
                                                    x * 53 + 41 - 1 * x - 53 * (ship.length - 1))
                                elif orientation == "horizontal":
                                    ship_label.move(y * 53 + 39 - 1 * y - 45,
                                                    x * 53 + 32 - 1 * x + 12)
                        case "destroyer":
                            if board_name == "Player":
                                if orientation == "vertical":
                                    ship_label.move(y * 53 + 39 - 1 * y,
                                                    x * 53 + 47 - 1 * x - 53 * (ship.length - 1))
                                elif orientation == "horizontal":
                                    ship_label.move(y * 53 + 39 - 1 * y,
                                                    x * 53 + 35 - 1 + 5)
                            elif board_name == "Computer":
                                if orientation == "vertical":
                                    ship_label.move(y * 53 - 1 * y + 5,
                                                    x * 53 - 1 * x - 56 * (ship.length - 1) + 45)
                                elif orientation == "horizontal":
                                    ship_label.move(y * 53 - 1 * y + 3,
                                                    x * 53 - 1 * x + 42)
                        case "submarine":
                            if board_name == "Player":
                                if orientation == "vertical":
                                    ship_label.move(y * 53 + 39 - 1 * y,
                                                    x * 53 + 35 - 1 * x - 53 * (ship.length - 1))
                                elif orientation == "horizontal":
                                    ship_label.move(y * 53 + 37 - 1 * y + 3,
                                                    x * 53 + 37 - 1 * x + 5)
                            elif board_name == "Computer":
                                if orientation == "vertical":
                                    ship_label.move(y * 53 - 1 * y + 8,
                                                    x * 53 - 2 * x - 53 * (ship.length - 1) + 35)
                                elif orientation == "horizontal":
                                    ship_label.move(y * 53 - 1 * y + 6,
                                                    x * 53 - 1 * x + 39)
                    ship_label.setParent(
                        self.player_board_widget if board_name == "Player" else self.computer_board_widget)
                    if board_name == "Player":
                        ship_label.show()
                        self.players_ships[name] = ship_label
                    else:
                        ship_label.hide()
                        self.computer_ships[name] = ship_label

        def cell_clicked(self, row, col, board_name):
            if self.game_manager.human.fire(self.game_manager.computer.get_board(), (row, col)):
                self.buttons[row][col].setEnabled(False)
                print(row, col)
                if self.computers_board_game.get_cell((row, col)).buffer:
                    self.draw_missed(row, col, self.computer_board_widget)
                    for _, ship in self.computers_board_game.ships.ships.items():
                        if (row, col) in ship.neighboring_coordinates:
                            ship.neighboring_coordinates.remove((row, col))
                if self.computers_board_game.get_cell((row, col)).has_ship:
                    self.draw_hit(row, col, self.computer_board_widget)
                    for name, ship in self.computers_board_game.ships.ships.items():
                        if ship.is_sunk(self.game_manager.computer.get_board()):
                            self.computer_ships[name].show()
                            for coordinate in ship.neighboring_coordinates:
                                row, col = coordinate
                                self.draw_missed(row, col, self.computer_board_widget)
                                self.buttons[row][col].setEnabled(False)
                        # if (row, col) in ship.coordinates:
                        # ship.coordinates.remove((row, col))
                computer_ships_left = len(
                    [ship for ship in self.game_manager.computer.get_board().ships.ships.values() if
                     not ship.is_sunk(self.game_manager.computer.get_board())])

                self.text.setText(f"It's your turn! Computer got {computer_ships_left} ships left")
                self.game_manager.check_game_status()
                if self.game_manager.game_status != 'continue':
                    match self.game_manager.game_status:
                        case 'human won':
                            self.text.setText("Congratulations, you won!")
                            print('human won')
                        case 'computer won':
                            self.text.setText("Unfortunately, you lost!")
                            print('computer won')
                else:
                    computer_fire_coordinates = self.game_manager.computer.fire()
                    if self.players_board_game.get_cell(computer_fire_coordinates).buffer:
                        self.draw_missed(computer_fire_coordinates[0], computer_fire_coordinates[1],
                                         self.player_board_widget)
                        # for _, ship in self.players_board_game.ships.ships.items():
                        #     if computer_fire_coordinates in ship.neighboring_coordinates:
                        #         ship.neighboring_coordinates.remove(computer_fire_coordinates)
                    if self.players_board_game.get_cell(computer_fire_coordinates).has_ship:
                        self.draw_hit(computer_fire_coordinates[0], computer_fire_coordinates[1],
                                      self.player_board_widget)
                        for name, ship in self.players_board_game.ships.ships.items():
                            if ship.is_sunk(self.game_manager.human.get_board()):
                                self.players_ships[name].show()
                                for coordinate in ship.neighboring_coordinates:
                                    row, col = coordinate
                                    self.game_manager.human.get_board().get_cell((row, col)).buffer = True
                                    self.draw_missed(row, col, self.player_board_widget)
                                # if computer_fire_coordinates in ship.coordinates:
                                # ship.coordinates.remove(computer_fire_coordinates)
                    self.game_manager.check_game_status()
                    print(self.game_manager.game_status)
                    match self.game_manager.game_status:
                        case 'human won':
                            print('human won')
                            self.draw_message_box(self.game_manager.game_status)
                        case 'computer won':
                            print('computer won')
                            self.draw_message_box(self.game_manager.game_status)

        def draw_missed(self, row, col, board_widget):
            missed = qtw.QLabel()
            pixmap = qtg.QPixmap("./resources/missed.png")
            scaled_pixmap = pixmap.scaled(53, 53)
            missed.setPixmap(scaled_pixmap)
            missed.setFixedSize(53, 53)
            missed.setAttribute(qtc.Qt.WA_TranslucentBackground)
            missed.setStyleSheet("background-color: red;")
            if board_widget == self.computer_board_widget:
                missed.move(col * 53 + 2 - 2 * col, row * 53 + 35)
            else:
                missed.move(col * 53 + 30, row * 53 + 30)
            missed.setParent(board_widget)
            missed.show()

        def draw_hit(self, row, col, board_widget):
            hit = qtw.QLabel()
            pixmap = qtg.QPixmap("./resources/hit.png")
            scaled_pixmap = pixmap.scaled(53, 53)
            hit.setPixmap(scaled_pixmap)
            hit.setFixedSize(53, 53)
            hit.setAttribute(qtc.Qt.WA_TranslucentBackground)
            hit.setStyleSheet("background-color: red;")
            if board_widget == self.computer_board_widget:
                hit.move(col * 53, row * 53 + 50)
            else:
                hit.move(col * 53 + 39, row * 53 + 44)
            hit.setParent(board_widget)
            hit.show()

        def draw_message_box(self, status):
            box = qtw.QMessageBox(self.player_board_widget)
            if status == "human won":
                box.setWindowTitle("Victory")
                box.setText("Congratulations, you won!")
            else:
                box.setWindowTitle("Game over")
                box.setText("Unfortunately, you lost!")
            original_icon = qtg.QPixmap('./resources/victory.png') if status == "" else qtg.QPixmap(
                './resources/game-over.png')
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

ship_sizes = {
    "submarine": (50, 62),
    "destroyer": (50, 112),
    "cruiser": (50, 155),
    "battleship": (50, 207),
    "carrier": (50, 255)
}
