# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'test01.ui'
##
## Created by: Qt User Interface Compiler version 5.15.2
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide2.QtCore import *
from PySide2.QtGui import *
from PySide2.QtWidgets import *


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        if not MainWindow.objectName():
            MainWindow.setObjectName(u"MainWindow")
        MainWindow.resize(800, 600)
        self.centralwidget = QWidget(MainWindow)
        self.centralwidget.setObjectName(u"centralwidget")
        self.tabWidget = QTabWidget(self.centralwidget)
        self.tabWidget.setObjectName(u"tabWidget")
        self.tabWidget.setGeometry(QRect(20, 10, 761, 541))
        self.main = QWidget()
        self.main.setObjectName(u"main")
        self.tabWidget.addTab(self.main, "")
        self.config = QWidget()
        self.config.setObjectName(u"config")
        self.tabWidget.addTab(self.config, "")
        self.macro = QWidget()
        self.macro.setObjectName(u"macro")
        self.tabWidget.addTab(self.macro, "")
        self.light = QWidget()
        self.light.setObjectName(u"light")
        self.tabWidget.addTab(self.light, "")
        MainWindow.setCentralWidget(self.centralwidget)
        self.statusbar = QStatusBar(MainWindow)
        self.statusbar.setObjectName(u"statusbar")
        MainWindow.setStatusBar(self.statusbar)
        self.menuBar = QMenuBar(MainWindow)
        self.menuBar.setObjectName(u"menuBar")
        self.menuBar.setGeometry(QRect(0, 0, 800, 22))
        MainWindow.setMenuBar(self.menuBar)

        self.retranslateUi(MainWindow)

        self.tabWidget.setCurrentIndex(3)


        QMetaObject.connectSlotsByName(MainWindow)
    # setupUi

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QCoreApplication.translate("MainWindow", u"MainWindow", None))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.main), QCoreApplication.translate("MainWindow", u"\u4e3b\u9875", None))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.config), QCoreApplication.translate("MainWindow", u"\u53c2\u6570\u8bbe\u7f6e", None))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.macro), QCoreApplication.translate("MainWindow", u"\u5b8f\u5b9a\u4e49", None))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.light), QCoreApplication.translate("MainWindow", u"\u5149\u6c61\u67d3", None))
    # retranslateUi

