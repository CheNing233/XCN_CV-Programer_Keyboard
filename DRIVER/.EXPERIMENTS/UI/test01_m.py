# 从生成的.py文件导入定义的窗口类
from test01 import Ui_MainWindow, QMainWindow,QApplication


# 定义主窗体
class MainWindow(QMainWindow):
    def __init__(self):
        super(MainWindow, self).__init__()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)

        
app = QApplication([])

window = MainWindow()
window.show()

app.exec_()