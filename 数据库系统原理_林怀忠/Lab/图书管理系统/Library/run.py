import sys
from PyQt5.QtWidgets import QApplication, QMainWindow
from main import Ui_Main
from search_ui import Ui_Search
from admin_ui import Ui_Admin
from reader_ui import Ui_Reader

import util
import admin
import reader
import connect

class Main(QMainWindow):
    def __init__(self):
        super().__init__()
        self.ui_main = Ui_Main()
        self.ui_main.setupUi(self)

        self.ui_main.Search.clicked.connect(self.show_search_window)
        self.ui_main.Reader.clicked.connect(self.show_reader_window)
        self.ui_main.Admin.clicked.connect(self.show_admin_window)
        self.ui_main.Exit.clicked.connect(self.close_all_windows)

    def show_admin_window(self):
        self.usr = admin.Admin()
        self.admin_window = QMainWindow()
        self.ui_admin = Ui_Admin()
        self.ui_admin.setupUi(self.admin_window)
        self.admin_window.show()

        self.ui_admin.Exit.clicked.connect(self.admin_window.close)
        self.ui_admin.Login.clicked.connect(self.admin_login)
        self.ui_admin.borrow.clicked.connect(self.borrow)
        self.ui_admin.Inquire.clicked.connect(self.inquire)
        self.ui_admin.Return.clicked.connect(self.Return)
        self.ui_admin.AddSingle.clicked.connect(self.addSingle)
        self.ui_admin.AddMulti.clicked.connect(self.addMulti)
        self.ui_admin.AddCard.clicked.connect(self.addCard)
        self.ui_admin.Delete.clicked.connect(self.deleteCard)

    def show_reader_window(self):
        self.usr = reader.Reader()
        self.reader_window = QMainWindow()
        self.ui_reader = Ui_Reader()
        self.ui_reader.setupUi(self.reader_window)
        self.reader_window.show()

        self.ui_reader.search.clicked.connect(self.show_search_window)
        self.ui_reader.login.clicked.connect(self.reader_login)
        self.ui_reader.Exit.clicked.connect(self.reader_window.close)
        self.ui_reader.getInfo.clicked.connect(self.getinfo)
        self.ui_reader.updateInfo.clicked.connect(self.updateinfo)

    def show_search_window(self):
        self.search_window = QMainWindow()
        self.ui_search = Ui_Search()
        self.ui_search.setupUi(self.search_window)
        self.search_window.show()

        self.ui_search.Exit.clicked.connect(self.search_window.close)
        self.ui_search.showAllBook.clicked.connect(self.show_all_book)
        self.ui_search.SearchButton.clicked.connect(self.show_search_book)

    def addCard(self):
        self.usr.add_card(self.ui_admin)

    def deleteCard(self):
        self.usr.delete_card(self.ui_admin)
    def addSingle(self):
        self.usr.add_single_newbook(self.ui_admin)

    def addMulti(self):
        self.usr.add_multi_newbook(self.ui_admin)
    def Return(self):
        self.usr.book_return(self.ui_admin)
    def borrow(self):
        self.usr.borrow(self.ui_admin)
    def inquire(self):
        self.usr.inquire(self.ui_admin)
    def admin_login(self):
        self.adminLoginCheck = self.usr.login(self.ui_admin)

    def close_all_windows(self):
        for widget in QApplication.topLevelWidgets():
            widget.close()

    def show_all_book(self):
        self.ui_search.Result.clear()
        util.show_all_book(self.ui_search)

    def show_search_book(self):
        self.ui_search.Result.clear()
        util.search_books(self.ui_search)

    def reader_login(self):
        self.usr.login(self.ui_reader)

    def getinfo(self):
        self.usr.getInfo(self.ui_reader)

    def updateinfo(self):
        self.usr.updateInfo(self.ui_reader)


if __name__ == "__main__":
    conn = connect.connect_to_library_db()
    app = QApplication(sys.argv)
    main_window = Main()
    main_window.show()
    sys.exit(app.exec_())