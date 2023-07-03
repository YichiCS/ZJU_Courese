from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_Main(object):
    def setupUi(self, Main):
        Main.setObjectName("Main")
        Main.resize(1512, 860)
        Main.setToolTipDuration(-4)
        self.Hello = QtWidgets.QTextBrowser(Main)
        self.Hello.setGeometry(QtCore.QRect(460, 30, 591, 91))
        self.Hello.setObjectName("Hello")
        self.Reader = QtWidgets.QPushButton(Main)
        self.Reader.setGeometry(QtCore.QRect(870, 160, 181, 91))
        font = QtGui.QFont()
        font.setPointSize(25)
        self.Reader.setFont(font)
        self.Reader.setObjectName("Reader")
        self.Admin = QtWidgets.QPushButton(Main)
        self.Admin.setGeometry(QtCore.QRect(460, 160, 181, 91))
        font = QtGui.QFont()
        font.setPointSize(25)
        self.Admin.setFont(font)
        self.Admin.setObjectName("Admin")
        self.Search = QtWidgets.QPushButton(Main)
        self.Search.setGeometry(QtCore.QRect(670, 160, 181, 91))
        font = QtGui.QFont()
        font.setPointSize(25)
        self.Search.setFont(font)
        self.Search.setObjectName("Search")
        self.Exit = QtWidgets.QPushButton(Main)
        self.Exit.setGeometry(QtCore.QRect(950, 570, 100, 32))
        self.Exit.setObjectName("Exit")

        self.retranslateUi(Main)
        QtCore.QMetaObject.connectSlotsByName(Main)

    def retranslateUi(self, Main):
        _translate = QtCore.QCoreApplication.translate
        Main.setWindowTitle(_translate("Main", "Main"))
        self.Hello.setHtml(_translate("Main", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:\'.AppleSystemUIFont\'; font-size:13pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:64pt;\">Welcome to Library</span></p></body></html>"))
        self.Reader.setText(_translate("Main", "Reader Login"))
        self.Admin.setText(_translate("Main", "Admin Login"))
        self.Search.setText(_translate("Main", "Search"))
        self.Exit.setText(_translate("Main", "Exit"))
