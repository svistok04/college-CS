import PyQt5.QtWidgets as qtw
import PyQt5.QtGui as qtg
import PyQt5.QtCore as qtc

class MyWindow1(qtw.QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle('My first program')
        self.setFixedSize(600, 600)
        self.wid = qtw.QWidget(self)
        self.setCentralWidget(self.wid)
        self.layout = qtw.QVBoxLayout()
        self.editor = qtw.QLineEdit()
        self.layout.addWidget(self.editor)
        self.label = qtw.QLabel()
        self.label.setText('Hello World!')
        self.layout.addWidget(self.label)
        self.button1 = qtw.QPushButton('Click me!')
        self.button1.clicked.connect(self.click)
        self.button2 = qtw.QPushButton('Click me2!')
        self.button2.clicked.connect(lambda x: self.label.setText('Hello World2!') if self.label.text() == 'Hello World!' else self.label.setText('Hello World!'))
        self.layout.addWidget(self.button1)
        self.layout.addWidget(self.button2)
        self.wid.setLayout(self.layout)

    def click(self):
        qtw.QMessageBox.information(self, 'Message', 'Pierwszy program gotowy!')


class Calculator(qtw.QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle('Kalkulator')
        self.setFixedSize(650, 700)
        self.setStyleSheet("background : white;")
        self.setUI()

    def setUI(self):
        self.label = qtw.QLabel(self)
        self.label.setWordWrap(True)
        self.label.setGeometry(5, 10, 640, 130)
        self.label.setStyleSheet("QLabel"
                                 "{"
                                 "border : 4px solid black;"
                                 "background : white;"
                                 "font-size: 20px;"
                                 "color: black;"
                                 "}")
        self.label.setFont(qtg.QFont('Arial', 15))

        pushclear = qtw.QPushButton('C', self)
        pushclear.setGeometry(10, 150, 310, 100)
        pushclear.setStyleSheet("color: black; font-size: 20px;")
        pushdel = qtw.QPushButton('DEL', self)
        pushdel.setGeometry(330, 150, 310, 100)
        pushdel.setStyleSheet("color: black; font-size: 20px;")

        col1 = 10
        col2 = 170
        col3 = 330
        col4 = 490
        row1 = 260
        row2 = 370
        row3 = 480
        row4 = 590
        height = 100
        width = 150

        push1 = qtw.QPushButton('1', self)
        push1.setGeometry(col1, row1, width, height)
        push1.setStyleSheet("color: black; font-size: 20px;")
        push4 = qtw.QPushButton('4', self)
        push4.setGeometry(col1, row2, width, height)
        push4.setStyleSheet("color: black; font-size: 20px;")
        push7 = qtw.QPushButton('7', self)
        push7.setGeometry(col1, row3, width, height)
        push7.setStyleSheet("color: black; font-size: 20px;")
        push0 = qtw.QPushButton('0', self)
        push0.setGeometry(col1, row4, width, height)
        push0.setStyleSheet("color: black; font-size: 20px;")

        push2 = qtw.QPushButton('2', self)
        push2.setGeometry(col2, row1, width, height)
        push2.setStyleSheet("color: black; font-size: 20px;")
        push5 = qtw.QPushButton('5', self)
        push5.setGeometry(col2, row2, width, height)
        push5.setStyleSheet("color: black; font-size: 20px;")
        push8 = qtw.QPushButton('8', self)
        push8.setGeometry(col2, row3, width, height)
        push8.setStyleSheet("color: black; font-size: 20px;")
        pushdot = qtw.QPushButton('.', self)
        pushdot.setGeometry(col2, row4, width, height)
        pushdot.setStyleSheet("color: black; font-size: 20px;")

        push3 = qtw.QPushButton('3', self)
        push3.setGeometry(col3, row1, width, height)
        push3.setStyleSheet("color: black; font-size: 20px;")
        push6 = qtw.QPushButton('6', self)
        push6.setGeometry(col3, row2, width, height)
        push6.setStyleSheet("color: black; font-size: 20px;")
        push9 = qtw.QPushButton('9', self)
        push9.setGeometry(col3, row3, width, height)
        push9.setStyleSheet("color: black; font-size: 20px;")
        pushdivide = qtw.QPushButton('/', self)
        pushdivide.setGeometry(col3, row4, width, height)
        pushdivide.setStyleSheet("color: black; font-size: 20px;")

        pushmultiply = qtw.QPushButton('*', self)
        pushmultiply.setGeometry(col4, row1, width, height)
        pushmultiply.setStyleSheet("color: black; font-size: 20px;")
        pushminus = qtw.QPushButton('-', self)
        pushminus.setGeometry(col4, row2, width, height)
        pushminus.setStyleSheet("color: black; font-size: 20px;")
        pushplus = qtw.QPushButton('+', self)
        pushplus.setGeometry(col4, row3, width, height)
        pushplus.setStyleSheet("color: black; font-size: 20px;")
        pushequal = qtw.QPushButton('=', self)
        pushequal.setGeometry(col4, row4, width, height)
        c_effect = qtw.QGraphicsColorizeEffect()
        c_effect.setColor(qtg.QColor('blue'))  # Set the color using QColor
        pushequal.setGraphicsEffect(c_effect)
        pushequal.setStyleSheet("color : black; font-size: 20px;")

        push1.clicked.connect(self.action1)
        push2.clicked.connect(self.action2)
        push3.clicked.connect(self.action3)
        push4.clicked.connect(self.action4)
        push5.clicked.connect(self.action5)
        push6.clicked.connect(self.action6)
        push7.clicked.connect(self.action7)
        push8.clicked.connect(self.action8)
        push9.clicked.connect(self.action9)
        push0.clicked.connect(self.action0)
        pushdot.clicked.connect(self.actiondot)
        pushplus.clicked.connect(self.actionplus)
        pushminus.clicked.connect(self.actionminus)
        pushmultiply.clicked.connect(self.actionmultiply)
        pushdivide.clicked.connect(self.actiondivide)
        pushclear.clicked.connect(self.actionclear)
        pushdel.clicked.connect(self.actiondel)
        pushequal.clicked.connect(self.actionequal)

    def action1(self):
        self.label.setText(self.label.text() + '1')

    def action2(self):
        self.label.setText(self.label.text() + '2')

    def action3(self):
        self.label.setText(self.label.text() + '3')

    def action4(self):
        self.label.setText(self.label.text() + '4')

    def action5(self):
        self.label.setText(self.label.text() + '5')

    def action6(self):
        self.label.setText(self.label.text() + '6')

    def action7(self):
        self.label.setText(self.label.text() + '7')

    def action8(self):
        self.label.setText(self.label.text() + '8')

    def action9(self):
        self.label.setText(self.label.text() + '9')

    def action0(self):
        self.label.setText(self.label.text() + '0')

    def actiondot(self):
        self.label.setText(self.label.text() + '.')

    def actionplus(self):
        self.label.setText(self.label.text() + '+')

    def actionminus(self):
        self.label.setText(self.label.text() + '-')

    def actionmultiply(self):
        self.label.setText(self.label.text() + '*')

    def actiondivide(self):
        self.label.setText(self.label.text() + '/')

    def actionclear(self):
        self.label.setText('')

    def actiondel(self):
        self.label.setText(self.label.text()[:-1])

    def actionequal(self):
        self.label.setText(str(eval(self.label.text())))

class WindowAddition(qtw.QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle('Addition')
        self.setFixedSize(600, 600)


app = qtw.QApplication([])
choice = 2
match choice:
    case 1:
        window = MyWindow1()
    case 2:
        window = Calculator()
    case 3:
        window = WindowAddition()
    case _:
        window = MyWindow1()
window.show()
app.exec_()



