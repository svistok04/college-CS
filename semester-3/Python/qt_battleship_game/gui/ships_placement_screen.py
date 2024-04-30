import PyQt5.QtWidgets as qtw
import PyQt5.QtGui as qtg
import PyQt5.QtCore as qtc

class ShipsPlacementScreen(qtw.QWidget):
    start_game_clicked = qtc.pyqtSignal()
    back_clicked = qtc.pyqtSignal()

    def __init__(self, game_manager):
        super().__init__()
        self._game_manager = game_manager
        self.layout = qtw.QVBoxLayout(self)
        self.setLayout(self.layout)
        self.board_and_ships_layout = qtw.QHBoxLayout()
        self.count = 0
        self.start_game_button = qtw.QPushButton("Start game")
        self.start_game_button.setEnabled(False)
        self.board_and_ships_layout.addStretch(1)
        self.board_gui = BoardGUI()
        self.board_game = self._game_manager.human.get_board()
        self.board_and_ships_layout.addWidget(self.board_gui, alignment=qtc.Qt.AlignLeft)
        self.board_and_ships_layout.addStretch(5)
        self.ships_gui = ShipsGUI(self.board_gui, self.board_game, self)
        self.board_and_ships_layout.addLayout(self.ships_gui)
        self.board_and_ships_layout.addStretch(5)
        self.layout.addStretch(1)
        self.layout.addLayout(self.board_and_ships_layout)
        self.layout.addStretch(5)
        self.draw_buttons()
        self.layout.addStretch(2)

    def draw_buttons(self):
        buttons_layout = qtw.QHBoxLayout()
        buttons_layout.setAlignment(qtc.Qt.AlignCenter)
        self.start_game_button.setFixedSize(250, 63)
        self.start_game_button.clicked.connect(self.start_game_clicked.emit)
        self.start_game_button.setStyleSheet("QPushButton { background-color: black; color: white; font-size: 24px; "
                                        "padding: 10px; border-radius: 15px; }"
                                        "QPushButton:hover { background-color: grey; }")
        back_button = qtw.QPushButton("Back")
        back_button.setFixedSize(250, 63)
        back_button.clicked.connect(self.back_clicked.emit)
        back_button.setStyleSheet("QPushButton { background-color: black; color: white; font-size: 24px; "
                                    "padding: 10px; border-radius: 15px; }"
                                    "QPushButton:hover { background-color: grey; }")
        random_button = qtw.QPushButton("Place ships randomly")
        random_button.setFixedSize(300, 63)
        random_button.setStyleSheet("QPushButton { background-color: black; color: white; font-size: 24px; "
                                    "padding: 10px; border-radius: 15px; }"
                                    "QPushButton:hover { background-color: grey; }")
        random_button.clicked.connect(self.random_clicked)
        buttons_layout.addStretch(1)
        buttons_layout.addWidget(back_button)
        buttons_layout.addStretch(5)
        buttons_layout.addWidget(random_button)
        buttons_layout.addStretch(5)
        buttons_layout.addWidget(self.start_game_button)
        buttons_layout.addStretch(1)
        buttons_widget = qtw.QWidget()
        buttons_widget.setLayout(buttons_layout)
        self.layout.addWidget(buttons_widget)

    def random_clicked(self):
        self._game_manager.human.place_ships_randomly()
        self.start_game_button.setEnabled(True)
        for ship_label in self.ships_gui.ship_labels:
            opacity = qtw.QGraphicsOpacityEffect(self)
            opacity.setOpacity(0)
            ship_label.setGraphicsEffect(opacity)
            ship_label.row = self.board_game.ships.get_ship(ship_label.name).coordinates[0][0]
            ship_label.col = self.board_game.ships.get_ship(ship_label.name).coordinates[0][1]
            ship_label.orientation = self.board_game.ships.get_ship(ship_label.name).orientation
            # print(ship_label.name)
            # print(ship_label.row, ship_label.col)
            # print(ship_label.orientation)
            ship_label.ship_on_board = ShipOnBoard(ship_label.name, ship_label.pixmap, ship_label.board_gui,
                                                         ship_label.board_game, (ship_label.row, ship_label.col), ship_label, self)
            ship_label.ship_on_board.set_ship_pixmap(ship_label.orientation)
            for buffer_coords in self.board_game.ships.get_ship(ship_label.name).neighboring_coordinates:
                ship_label.ship_on_board.buffers.append(Buffer(self.board_gui, buffer_coords))
            match ship_label.name.split('-')[0]:
                case "carrier":
                    if ship_label.orientation == "vertical":
                        ship_label.ship_on_board.move(ship_label.col * 53 + 39 - 1 * ship_label.col,
                                                ship_label.row * 53 + 47 - 1 * ship_label.row - 53 * (ship_label.length - 1))
                    elif ship_label.orientation == "horizontal":
                        ship_label.ship_on_board.move(ship_label.col * 53 + 39 - 1 * ship_label.col,
                                                ship_label.row * 53 + 40 - 1 * ship_label.row)
                case "battleship":
                    if ship_label.orientation == "vertical":
                        ship_label.ship_on_board.move(ship_label.col * 53 + 40 - 1 * ship_label.col,
                                                ship_label.row * 53 + 45 - 1 * ship_label.row - 53 * (ship_label.length - 1))
                    elif ship_label.orientation == "horizontal":
                        ship_label.ship_on_board.move(ship_label.col * 53 + 39 - 1 * ship_label.col,
                                                ship_label.row * 53 + 40 - 1 * ship_label.row)
                case "cruiser":
                    if ship_label.orientation == "vertical":
                        ship_label.ship_on_board.move(ship_label.col * 53 + 39 - 1 * ship_label.col,
                                                ship_label.row * 53 + 42 - 1 * ship_label.row - 53 * (ship_label.length - 1))
                    elif ship_label.orientation == "horizontal":
                        ship_label.ship_on_board.move(ship_label.col * 53 + 39 - 1 * ship_label.col,
                                                ship_label.row * 53 + 40 - 1 * ship_label.row)
                case _:
                    if ship_label.orientation == "vertical":
                        ship_label.ship_on_board.move(ship_label.col * 53 + 40 - 1 * ship_label.col,
                                                ship_label.row * 53 + 32 - 1 * ship_label.row - 53 * (ship_label.length - 1))
                    elif ship_label.orientation == "horizontal":
                        ship_label.ship_on_board.move(ship_label.col * 53 + 39 - 1 * ship_label.col,
                                                ship_label.row * 53 + 40 - 1 * ship_label.row)



class BoardGUI(qtw.QWidget):
    class CellButton(qtw.QPushButton):
        def __init__(self, row, col):
            super().__init__()
            self.row = row
            self.col = col
            self.setFixedSize(53, 53)

    def __init__(self):
        super().__init__()
        self.setFixedSize(560, 560)
        self.board_layout = qtw.QGridLayout()
        self.draw_board()

    def draw_board(self):
        for row in range(1, 11):
            label = qtw.QLabel(str(row))
            label.setAlignment(qtc.Qt.AlignCenter)
            label.setStyleSheet("color: black; font-size: 20px;")
            self.board_layout.addWidget(label, row, 0)

        for col in range(1, 11):
            label = qtw.QLabel(chr(64 + col))
            label.setAlignment(qtc.Qt.AlignCenter)
            label.setStyleSheet("color: black; font-size: 20px;")
            self.board_layout.addWidget(label, 0, col)

        for row in range(1, 11):
            for col in range(1, 11):
                button = self.CellButton(row - 1, col - 1)
                # button.setStyleSheet("QPushButton {border: 1px solid black; }"
                #                    "QPushButton:hover { background-color: grey; }"
                #                     "QPushButton:pressed { background-color: black; }")
                self.board_layout.addWidget(button, row, col)
        self.setLayout(self.board_layout)



class ShipsGUI(qtw.QHBoxLayout):
    class DraggableShipLabel(qtw.QLabel):
        def __init__(self, name, pixmap, board_gui, board_game, parent_screen):
            super().__init__()
            self.name = name
            self.length = ship_lengths[name.split('-')[0]]
            self.pixmap = pixmap
            self.board_gui = board_gui
            self.board_game = board_game
            self.parent_screen = parent_screen
            self.original_position = None
            self.buffers = []
            self.set_ship_pixmap()
            self.setCursor(qtg.QCursor(qtc.Qt.OpenHandCursor))
            self.setAttribute(qtc.Qt.WA_TranslucentBackground)
            self.is_dragging = False
            self.is_placed = False
            self.orientation = "vertical"
            self.ship_on_board = None
            self.row = None
            self.col = None
            self.prevcol = 100
            self.prevrow = 100
            # self.timer = qtc.QTimer()
            # self.timer.timeout.connect(self.mouseMoveEvent)
            # self.timer.start(500)

        def set_ship_pixmap(self):
            size = ship_sizes[self.name.split('-')[0]]
            scaled_pixmap = self.pixmap.scaled(*size)
            self.setPixmap(scaled_pixmap)
            self.setFixedSize(scaled_pixmap.size())

        def mousePressEvent(self, event):
            if event.button() == qtc.Qt.LeftButton and not self.is_placed:
                self.is_dragging = True
                self.setCursor(qtg.QCursor(qtc.Qt.ClosedHandCursor))
                self.original_position = self.pos()

        def mouseMoveEvent(self, event):
            if self.is_dragging:
                new_pos = self.mapToParent(event.pos() - self.rect().center())
                self.move(new_pos)
                global_cursor_pos = self.mapToGlobal(event.pos())
                cell = 53
                board_pos = self.board_gui.mapFromGlobal(global_cursor_pos)
                self.col = (board_pos.x() - 15) // cell
                self.row = (board_pos.y() - 15) // cell

                if 0 <= self.col < 10 and 0 <= self.row < 10:
                    opacity = qtw.QGraphicsOpacityEffect(self)
                    opacity.setOpacity(0)
                    self.setGraphicsEffect(opacity)
                    if not self.is_placed:
                        self.ship_on_board = ShipOnBoard(self.name, self.pixmap, self.board_gui,
                                                         self.board_game, (self.row, self.col), self, self.parent_screen)
                    self.is_placed = True
                    if self.col != self.prevcol or self.row != self.prevrow:
                        self.ship_on_board.row = self.row
                        self.ship_on_board.col = self.col
                        self.prevcol = self.col
                        self.prevrow = self.row
                        if self.board_game.check_if_placeable((self.row, self.col), "vertical", self.name):
                            match self.name.split('-')[0]:
                                case "carrier":
                                    self.ship_on_board.move(self.col * 53 + 39 - 1 * self.col,
                                                            self.row * 53 + 47 - 1 * self.row - 53 * (self.length - 1))
                                case "battleship":
                                    self.ship_on_board.move(self.col * 53 + 39 - 1 * self.col,
                                                            self.row * 53 + 45 - 1 * self.row - 53 * (self.length - 1))
                                case "cruiser":
                                    self.ship_on_board.move(self.col * 53 + 39 - 1 * self.col,
                                                            self.row * 53 + 42 - 1 * self.row - 53 * (self.length - 1))
                                case _:
                                    self.ship_on_board.move(self.col * 53 + 39 - 1 * self.col,
                                                            self.row * 53 + 32 - 1 * self.row - 53 * (self.length - 1))
                            # print(f'Dragging over cell at row {self.row}, col {self.col}, at {board_pos.x()}, {board_pos.y()}')
                else:
                    self.is_placed = False
                    if self.ship_on_board is not None:
                        self.ship_on_board.hide()
                    opacity = qtw.QGraphicsOpacityEffect(self)
                    opacity.setOpacity(1)
                    self.setGraphicsEffect(opacity)


        def mouseReleaseEvent(self, event):
            self.is_dragging = False
            self.setCursor(qtg.QCursor(qtc.Qt.OpenHandCursor))
            if self.is_placed:
                self.board_game.ships.get_ship(self.name).is_set = True
                self.board_game.place_ship((self.row, self.col), "vertical", self.name)
                self.parent_screen.count += 1
                if self.parent_screen.count == 8:
                    self.parent_screen.start_game_button.setEnabled(True)
                else:
                    self.parent_screen.start_game_button.setEnabled(False)
                opacity = qtw.QGraphicsOpacityEffect(self)
                opacity.setOpacity(0)
                self.setGraphicsEffect(opacity)
                for buffer_coords in self.board_game.ships.get_ship(self.name).neighboring_coordinates:
                    self.ship_on_board.buffers.append(Buffer(self.board_gui, buffer_coords))
            self.move(self.original_position)
            # if not self.is_placed:
            #     self.ship_on_board.deleteLater()
            #     self.ship_on_board = None
            self.prevcol = 100
            self.prevrow = 100

        def enterEvent(self, event):
            if not self.is_placed:
                self.setCursor(qtg.QCursor(qtc.Qt.OpenHandCursor))
            super().enterEvent(event)

        def leaveEvent(self, event):
            self.setCursor(qtg.QCursor(qtc.Qt.ArrowCursor))
            super().leaveEvent(event)

    def __init__(self, board_gui, board_game, parent_screen):
        super().__init__()
        self.board_gui = board_gui
        self.board_game = board_game
        self.parent_screen = parent_screen
        self.ship_labels = []
        self.setSpacing(40)
        self.create_ships_layout()

    def create_ships_layout(self):
        ship_images = {name.split('-')[0]: qtg.QPixmap(f"./resources/{name.split('-')[0]}.png") for name in ship_names}
        for name in ship_names:
            pixmap = ship_images[name.split('-')[0]]
            ship_label = self.DraggableShipLabel(name, pixmap, self.board_gui, self.board_game, self.parent_screen)
            self.ship_labels.append(ship_label)
            self.addWidget(ship_label, alignment=qtc.Qt.AlignBottom)


class ShipOnBoard(qtw.QLabel):
    def __init__(self, name, pixmap, board_gui, board_game, pos, parent_label, parent_screen):
        super().__init__()
        self.name = name
        self.length = ship_lengths[name.split('-')[0]]
        self.pixmap = pixmap
        self.board_gui = board_gui
        self.board_game = board_game
        self.orientation = "vertical"
        self.row, self.col = pos
        self.prevrow = None
        self.prevcol = None
        self.parent_label = parent_label
        self.parent_screen = parent_screen
        self.child_label = None
        self.buffers = []
        self.set_ship_pixmap(self.orientation)
        self.move_to_cell(pos)
        self.setCursor(qtg.QCursor(qtc.Qt.OpenHandCursor))
        self.setAttribute(qtc.Qt.WA_TranslucentBackground)
        self.is_dragging = False

    def set_ship_pixmap(self, orientation):
        pixmap = qtg.QPixmap(f"./resources/{self.name.split('-')[0]}.png") if orientation == "vertical" \
            else qtg.QPixmap(f"./resources/{self.name.split('-')[0]}-horizontal.png")
        scaled_pixmap = pixmap.scaled(*ship_sizes[self.name.split('-')[0]] if orientation == "vertical" else ship_sizes[self.name.split('-')[0]][::-1])
        self.setPixmap(scaled_pixmap)
        self.setFixedSize(*ship_sizes[self.name.split('-')[0]] if orientation == "vertical" else ship_sizes[self.name.split('-')[0]][::-1])

    def mousePressEvent(self, event):
        if event.button() == qtc.Qt.LeftButton:
            self.is_dragging = True
        if event.button() == qtc.Qt.RightButton:
            self.is_dragging = False
            removed_coords = []
            stop = False
            other_ships = {name: ship for name, ship in self.board_game.ships.ships.items() if name != self.name}
            for buffer_coords in self.board_game.ships.get_ship(self.name).neighboring_coordinates:
                for ship in other_ships.values():
                    if buffer_coords in ship.neighboring_coordinates and buffer_coords[1] == self.board_game.ships.get_ship(self.name).coordinates[0][1] + 1:
                        stop = True
                self.board_game.get_cell(buffer_coords).buffer = False
                removed_coords.append(buffer_coords)
                if stop:
                    break
            if not stop:
                for ship_coords in self.board_game.ships.get_ship(self.name).coordinates:
                    self.board_game.get_cell(ship_coords).has_ship = False
                if self.board_game.check_if_placeable((self.row, self.col), "horizontal" if self.orientation == "vertical" else "vertical", self.name):
                    for buffer in self.buffers:
                        buffer.deleteLater()
                    self.buffers = []
                    self.orientation = "horizontal" if self.orientation == "vertical" else "vertical"
                    self.board_game.ships.get_ship(self.name).orientation = self.orientation
                    x, y = self.pos().x(), self.pos().y()
                    self.set_ship_pixmap(self.orientation)
                    match self.name.split('-')[0]:
                        case "carrier":
                            if self.orientation == "vertical":
                                self.move(x, y - 53 * (self.length - 1) + 6)
                            elif self.orientation == "horizontal":
                                self.move(x, y + 53 * (self.length - 1) - 6)
                        case "battleship":
                            if self.orientation == "vertical":
                                self.move(x, y - 53 * (self.length - 1) + 6)
                            elif self.orientation == "horizontal":
                                self.move(x, y + 53 * (self.length - 1) - 6)
                        case "cruiser":
                            if self.orientation == "vertical":
                                self.move(x, y - 53 * (self.length - 1) + 1)
                            elif self.orientation == "horizontal":
                                self.move(x, y + 53 * (self.length - 1) - 1)
                        case "destroyer":
                            if self.orientation == "vertical":
                                self.move(x, y - 53 * (self.length - 1) - 8)
                            elif self.orientation == "horizontal":
                                self.move(x, y + 53 * (self.length - 1) + 8)
                        case "submarine":
                            if self.orientation == "vertical":
                                self.move(x, y - 53 * (self.length - 1) - 8)
                            elif self.orientation == "horizontal":
                                self.move(x, y + 53 * (self.length - 1) + 8)
                    self.board_game.place_ship((self.row, self.col), self.orientation, self.name)
                    for buffer_coords in self.board_game.ships.get_ship(self.name).neighboring_coordinates:
                        self.buffers.append(Buffer(self.board_gui, buffer_coords))
            else:
                for coords in removed_coords:
                    self.board_game.get_cell(coords).buffer = True

    def mouseMoveEvent(self, event):
        if self.is_dragging:
            if self.child_label is None:
                self.child_label = ShipOnBoard(self.name, self.pixmap, self.board_gui, self.board_game,
                                               (self.row, self.col), self, self.parent_screen)
                for buffer_coords in self.board_game.ships.get_ship(self.name).neighboring_coordinates:
                    self.board_game.get_cell(buffer_coords).buffer = False
                for ship_coords in self.board_game.ships.get_ship(self.name).coordinates:
                    self.board_game.get_cell(ship_coords).has_ship = False
                for buffer in self.buffers:
                    buffer.deleteLater()
                self.buffers = []
                opacity = qtw.QGraphicsOpacityEffect(self)
                opacity.setOpacity(0)
                self.setGraphicsEffect(opacity)
            new_pos = self.mapToParent(event.pos() - self.rect().center())
            self.move(new_pos)
            global_cursor_pos = self.mapToGlobal(event.pos())
            cell = 53
            board_pos = self.board_gui.mapFromGlobal(global_cursor_pos)
            self.col = (board_pos.x() - 15) // cell
            self.row = (board_pos.y() - 15) // cell
            if 0 <= self.col < 10 and 0 <= self.row < 10:
                if self.col != self.prevcol or self.row != self.prevrow:
                    self.prevcol = self.col
                    self.prevrow = self.row
                    if self.board_game.check_if_placeable((self.row, self.col), self.orientation, self.name):
                        match self.name.split('-')[0]:
                            case "carrier":
                                self.child_label.move(self.col * 53 + 39 - 1 * self.col,
                                                        self.row * 53 + 47 - 1 * self.row - 53 * (self.length - 1))
                            case "battleship":
                                self.child_label.move(self.col * 53 + 39 - 1 * self.col,
                                                        self.row * 53 + 45 - 1 * self.row - 53 * (self.length - 1))
                            case "cruiser":
                                self.child_label.move(self.col * 53 + 39 - 1 * self.col,
                                                        self.row * 53 + 42 - 1 * self.row - 53 * (self.length - 1))
                            case _:
                                self.child_label.move(self.col * 53 + 39 - 1 * self.col,
                                                        self.row * 53 + 32 - 1 * self.row - 53 * (self.length - 1))
                else:
                    pass
            else:
                self.parent_label.show()
                self.parent_label.is_placed = False
                self.board_game.ships.get_ship(self.name).is_set = False
                opacity = qtw.QGraphicsOpacityEffect(self)
                opacity.setOpacity(1)
                self.parent_label.setGraphicsEffect(opacity)

    def mouseReleaseEvent(self, event):
        if event.button() == qtc.Qt.LeftButton and self.is_dragging:
            if self.child_label is not None:
                self.child_label.hide()
                self.child_label.deleteLater()
            self.child_label = None
            if 0 <= self.col < 10 and 0 <= self.row < 10:
                self.board_game.place_ship((self.row, self.col), self.orientation, self.name)
                for buffer_coords in self.board_game.ships.get_ship(self.name).neighboring_coordinates:
                    self.buffers.append(Buffer(self.board_gui, buffer_coords))
                opacity = qtw.QGraphicsOpacityEffect(self)
                opacity.setOpacity(1)
                self.setGraphicsEffect(opacity)
                match self.name.split('-')[0]:
                    case "carrier":
                        self.move(self.col * 53 + 39 - 1 * self.col,
                                  self.row * 53 + 47 - 1 * self.row - 53 * (self.length - 1))
                    case "battleship":
                        self.move(self.col * 53 + 39 - 1 * self.col,
                                  self.row * 53 + 45 - 1 * self.row - 53 * (self.length - 1))
                    case "cruiser":
                        self.move(self.col * 53 + 39 - 1 * self.col,
                                  self.row * 53 + 42 - 1 * self.row - 53 * (self.length - 1))
                    case _:
                        self.move(self.col * 53 + 39 - 1 * self.col,
                                  self.row * 53 + 32 - 1 * self.row - 53 * (self.length - 1))
            else:
                self.parent_label.show()
                self.parent_screen.count -= 1
                opacity = qtw.QGraphicsOpacityEffect(self)
                opacity.setOpacity(1)
                self.parent_label.setGraphicsEffect(opacity)

    def move_to_cell(self, pos):
        # Move the ship to the specified cell
        cell_width, cell_height = 53, 53
        x = pos[1] * cell_width + 28
        y = pos[0] * cell_height + 35
        self.move(x, y)
        self.setParent(self.board_gui)
        self.show()


class Buffer(qtw.QLabel):
    def __init__(self, parent, coords):
        super().__init__(parent)
        self.setFixedSize(50, 50)
        self.pixmap = qtg.QPixmap("./resources/spray.png")
        self.setPixmap(self.pixmap)
        row, col = coords
        opacity = qtw.QGraphicsOpacityEffect(self)
        opacity.setOpacity(0.7)
        self.setGraphicsEffect(opacity)
        self.move(col * 53 + 40 - 1 * col, row * 53 + 40 - 1 * row)
        self.show()


ship_names = ["submarine-1", "submarine-2", "submarine-3", "destroyer-1",
              "destroyer-2", "cruiser-1", "battleship-1", "carrier-1"]
ship_lengths = {
    "submarine": 1,
    "destroyer": 2,
    "cruiser": 3,
    "battleship": 4,
    "carrier": 5
}
ship_sizes = {
    "submarine": (50, 62),
    "destroyer": (50, 112),
    "cruiser": (50, 155),
    "battleship": (50, 207),
    "carrier": (50, 255)
}
