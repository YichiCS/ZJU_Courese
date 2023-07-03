from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_Reader(object):
    def setupUi(self, Reader):
        Reader.setObjectName("Reader")
        Reader.resize(1512, 860)
        self.output = QtWidgets.QTextEdit(Reader)
        self.output.setGeometry(QtCore.QRect(450, 180, 781, 211))
        font = QtGui.QFont()
        font.setPointSize(24)
        self.output.setFont(font)
        self.output.setObjectName("output")
        self.cardIDInput = QtWidgets.QLineEdit(Reader)
        self.cardIDInput.setGeometry(QtCore.QRect(540, 430, 281, 41))
        font = QtGui.QFont()
        font.setPointSize(32)
        self.cardIDInput.setFont(font)
        self.cardIDInput.setText("")
        self.cardIDInput.setObjectName("cardIDInput")
        self.getInfo = QtWidgets.QPushButton(Reader)
        self.getInfo.setGeometry(QtCore.QRect(260, 590, 221, 111))
        font = QtGui.QFont()
        font.setPointSize(24)
        self.getInfo.setFont(font)
        self.getInfo.setObjectName("getInfo")
        self.Neko = QtWidgets.QLabel(Reader)
        self.Neko.setGeometry(QtCore.QRect(150, 180, 281, 211))
        font = QtGui.QFont()
        font.setPointSize(16)
        self.Neko.setFont(font)
        self.Neko.setObjectName("Neko")
        self.updateInfo = QtWidgets.QPushButton(Reader)
        self.updateInfo.setGeometry(QtCore.QRect(510, 590, 221, 111))
        font = QtGui.QFont()
        font.setPointSize(24)
        self.updateInfo.setFont(font)
        self.updateInfo.setObjectName("updateInfo")
        self.search = QtWidgets.QPushButton(Reader)
        self.search.setGeometry(QtCore.QRect(760, 590, 221, 111))
        font = QtGui.QFont()
        font.setPointSize(24)
        self.search.setFont(font)
        self.search.setObjectName("search")
        self.Exit = QtWidgets.QPushButton(Reader)
        self.Exit.setGeometry(QtCore.QRect(30, 810, 100, 32))
        self.Exit.setObjectName("Exit")
        self.nameInput = QtWidgets.QLineEdit(Reader)
        self.nameInput.setGeometry(QtCore.QRect(950, 430, 281, 41))
        font = QtGui.QFont()
        font.setPointSize(32)
        self.nameInput.setFont(font)
        self.nameInput.setText("")
        self.nameInput.setObjectName("nameInput")
        self.deptInput = QtWidgets.QLineEdit(Reader)
        self.deptInput.setGeometry(QtCore.QRect(540, 510, 281, 41))
        font = QtGui.QFont()
        font.setPointSize(32)
        self.deptInput.setFont(font)
        self.deptInput.setText("")
        self.deptInput.setObjectName("deptInput")
        self.type = QtWidgets.QLabel(Reader)
        self.type.setGeometry(QtCore.QRect(880, 510, 61, 41))
        font = QtGui.QFont()
        font.setPointSize(24)
        self.type.setFont(font)
        self.type.setObjectName("type")
        self.name = QtWidgets.QLabel(Reader)
        self.name.setGeometry(QtCore.QRect(870, 430, 71, 41))
        font = QtGui.QFont()
        font.setPointSize(24)
        self.name.setFont(font)
        self.name.setObjectName("name")
        self.cardID = QtWidgets.QLabel(Reader)
        self.cardID.setGeometry(QtCore.QRect(440, 430, 91, 41))
        font = QtGui.QFont()
        font.setPointSize(24)
        self.cardID.setFont(font)
        self.cardID.setObjectName("cardID")
        self.department = QtWidgets.QLabel(Reader)
        self.department.setGeometry(QtCore.QRect(400, 510, 131, 41))
        font = QtGui.QFont()
        font.setPointSize(24)
        self.department.setFont(font)
        self.department.setObjectName("department")
        self.comboBox = QtWidgets.QComboBox(Reader)
        self.comboBox.setGeometry(QtCore.QRect(950, 520, 291, 32))
        self.comboBox.setObjectName("comboBox")
        self.comboBox.addItems(["undergraduate", "graduate ", "teacher", "others"])
        self.comboBox.setCurrentIndex(0)
        self.login = QtWidgets.QPushButton(Reader)
        self.login.setGeometry(QtCore.QRect(1010, 590, 221, 111))
        font = QtGui.QFont()
        font.setPointSize(24)
        self.login.setFont(font)
        self.login.setObjectName("login")
        self.label = QtWidgets.QLabel(Reader)
        self.label.setGeometry(QtCore.QRect(530, 50, 441, 61))
        font = QtGui.QFont()
        font.setPointSize(64)
        self.label.setFont(font)
        self.label.setObjectName("label")

        self.retranslateUi(Reader)
        QtCore.QMetaObject.connectSlotsByName(Reader)

    def retranslateUi(self, Reader):
        _translate = QtCore.QCoreApplication.translate
        Reader.setWindowTitle(_translate("Reader", "Reader"))
        self.output.setHtml(_translate("Reader", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:\'.AppleSystemUIFont\'; font-size:24pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:48pt;\">Welcome, Input your card ID to login.</span></p></body></html>"))
        self.getInfo.setText(_translate("Reader", "Self Information"))
        self.Neko.setText(_translate("Reader",
"⣿⣿⣿⠟⠛⠛⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⢋⣩⣉⢻⣿⣿⣿\n"
"⣿⣿⣿⠀⣿⣶⣕⣈⠹⠿⠿⠿⠿⠟⠛⣛⢋⣰⠣⣿⣿⠀⣿⣿⣿\n"
"⣿⣿⣿⡀⣿⣿⣿⣧⢻⣿⣶⣷⣿⣿⣿⣿⣿⣿⠿⠶⡝⠀⣿⣿⣿\n"
"⣿⣿⣿⣷⠘⣿⣿⣿⢏⣿⣿⣋⣀⣈⣻⣿⣿⣷⣤⣤⣿⡐⢿⣿⣿\n"
"⣿⣿⣿⣿⣆⢩⣝⣫⣾⣿⣿⣿⣿⡟⠿⠿⠦⠀⠸⠿⣻⣿⡄⢻⣿\n"
"⣿⣿⣿⣿⣿⡄⢻⣿⣿⣿⣿⣿⣿⣿⣿⣶⣶⣾⣿⣿⣿⣿⠇⣼⣿\n"
"⣿⣿⣿⣿⣿⣿⡄⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⣰⣿⣿\n"
"⣿⣿⣿⣿⣿⣿⠇⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢀⣿⣿⣿\n"
"⣿⣿⣿⣿⣿⠏⢰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢸⣿⣿⣿\n"
"⣿⣿⣿⣿⠟⣰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⣿⣿⣿\n"
"⣿⣿⣿⠋⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄⣿⣿⣿\n"
"⣿⣿⠋⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⢸⣿⣿"))
        self.updateInfo.setText(_translate("Reader", "Update Information"))
        self.search.setText(_translate("Reader", "Search"))
        self.Exit.setText(_translate("Reader", "Exit"))
        self.type.setText(_translate("Reader", "Type:"))
        self.name.setText(_translate("Reader", "name:"))
        self.cardID.setText(_translate("Reader", "Card_id:"))
        self.department.setText(_translate("Reader", "Department:"))
        self.login.setText(_translate("Reader", "Login"))
        self.label.setText(_translate("Reader", "Reader Terminal"))
