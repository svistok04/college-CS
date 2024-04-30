import PyQt5.QtWidgets as qtw
import PyQt5.QtGui as qtg
import PyQt5.QtCore as qtc

class MainScreen(qtw.QWidget):
    play_clicked = qtc.pyqtSignal()

    def __init__(self):
        super().__init__()
        layout = qtw.QVBoxLayout()
        self.setLayout(layout)
        layout.setAlignment(qtc.Qt.AlignCenter)
        layout.setSpacing(20)
        name = qtw.QLabel("Battleship")
        name.setStyleSheet("color: white; font-size: 70px; font-weight: bold;")
        name.setAlignment(qtc.Qt.AlignCenter)
        play_button = qtw.QPushButton("Play")
        play_button.setStyleSheet("QPushButton { background-color: black; color: white; font-size: 24px; "
                                  "padding: 10px; border-radius: 15px; }"
                                  "QPushButton:hover { background-color: grey; }")
        play_button.setFixedSize(250, 63)
        play_button.clicked.connect(self.play_clicked.emit)
        quit_button = qtw.QPushButton("Quit")
        quit_button.setStyleSheet("QPushButton { background-color: black; color: white; font-size: 24px; "
                                  "padding: 10px; border-radius: 15px; }"
                                  "QPushButton:hover { background-color: grey; }")
        quit_button.setFixedSize(250, 63)
        quit_button.clicked.connect(lambda: qtw.QApplication.instance().quit())

        layout.addStretch(10)
        layout.addWidget(name, alignment=qtc.Qt.AlignCenter)
        layout.addStretch(5)
        layout.addWidget(play_button, alignment=qtc.Qt.AlignCenter)
        layout.addStretch(1)
        layout.addWidget(quit_button, alignment=qtc.Qt.AlignCenter)
        layout.addStretch(15)
