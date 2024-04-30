import PyQt5.QtWidgets as qtw
from game import game_manager
# from gui_old import main_window
from gui import main_window

if __name__ == '__main__':
    game_manager_instance = game_manager.GameManager()
    app = qtw.QApplication([])
    gui = main_window.MainWindow(game_manager_instance)
    window = gui
    window.show()
    app.exec_()
