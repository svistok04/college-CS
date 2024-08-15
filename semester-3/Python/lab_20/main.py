import PyQt5.QtWidgets as qtw
import PyQt5.QtGui as qtg
import PyQt5.QtCore as qtc


class MainWindow(qtw.QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Traffic Light")
        self.setMinimumSize(1000, 700)
        self.setStyleSheet("background-color: black;")
        self.setUI()

    def setUI(self):
        central_widget = qtw.QWidget()
        self.setCentralWidget(central_widget)
        layout = qtw.QVBoxLayout(central_widget)

        self.light_red = qtw.QLabel()
        self.light_red.setStyleSheet("background-color: red; border-radius: 100px;")
        self.light_red.setMinimumSize(200, 200)  # Set a fixed size for the label
        self.light_yellow = qtw.QLabel()
        self.light_yellow.setStyleSheet("background-color: yellow; border-radius: 100px;")
        self.light_yellow.setMinimumSize(200, 200)  # Set a fixed size for the label
        self.light_green = qtw.QLabel()
        self.light_green.setStyleSheet("background-color: green; border-radius: 100px;")
        self.light_green.setMinimumSize(200, 200)  # Set a fixed size

        layout.addWidget(self.light_red, 1, qtc.Qt.AlignHCenter)
        layout.addWidget(self.light_yellow, 1, qtc.Qt.AlignHCenter)
        layout.addWidget(self.light_green, 1, qtc.Qt.AlignHCenter)
        central_widget.setLayout(layout)

        def resizeEvent(self, event):
            # This event is called when the window is resized.
            new_width = self.centralWidget().width()  # Get the width of the central widget
            new_height = self.centralWidget().height() // 3  # Divide the height by 3 to fit 3 lights vertically

            # Calculate the diameter for the traffic lights. Use the smaller of the two dimensions.
            diameter = min(new_width, new_height)
            # Update the fixed size of the labels with the new diameter
            self.light_red.setFixedSize(diameter, diameter)
            self.light_yellow.setFixedSize(diameter, diameter)
            self.light_green.setFixedSize(diameter, diameter)

            # The border-radius should be half the diameter to maintain the circular shape
            self.light_red.setStyleSheet("background-color: red; border-radius: %dpx;" % (diameter // 2))
            self.light_yellow.setStyleSheet("background-color: yellow; border-radius: %dpx;" % (diameter // 2))
            self.light_green.setStyleSheet("background-color: green; border-radius: %dpx;" % (diameter // 2))

            super(MainWindow, self).resizeEvent(event)  # Call the parent class's resize event

        def updateStyleSheet(self, light, radius):
            color = light.styleSheet().split('background-color: ')[1].split(';')[0]
            light.setStyleSheet(f"background-color: {color}; border-radius: {int(radius)}px;")


app = qtw.QApplication([])
window = MainWindow()
window.show()
app.exec_()

