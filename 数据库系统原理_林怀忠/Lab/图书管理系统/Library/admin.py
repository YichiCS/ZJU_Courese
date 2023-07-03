import datetime
import connect

class Admin():

    def __init__(self):
        self.conn = connect.connect_to_library_db()
        self.cursor = self.conn.cursor()
        self.admin_id = "00000000"
        self.temp_card_id = "00000000"
        self.Login = False
    
    def login(self, ui_admin):
        try:
            ui_admin.output.clear()
            admin_id = ui_admin.adminInput.text()
            password = ui_admin.nameInput.text()
            sql = "SELECT * FROM Admin WHERE admin_id = %s"
            self.cursor.execute(sql, (admin_id,))
            result = self.cursor.fetchone()
            if result is None:
                ui_admin.output.append("No such admin ID.")
                return
            if result[1] != password:
                ui_admin.output.append("Wrong password.")
                return
            ui_admin.output.append(f"Login successful! \nWelcome Admin {admin_id}")
            self.admin_id = admin_id
            self.Login = True
        except Exception as e:
            ui_admin.output.clear()
            ui_admin.output.append(f"Error: {e}")
            return

    def inquire(self, ui_admin):
        if self.Login == False:
            ui_admin.output.clear()
            ui_admin.output.append("Login first.")
            return
        try:
            ui_admin.output.clear()
            card_id = ui_admin.cardIDBorrowIn.text()
            sql = "SELECT * FROM card WHERE card_id = %s"
            self.cursor.execute(sql, (card_id,))
            results = self.cursor.fetchone()
            if results is None:
                ui_admin.output.append("No such card.")
                return
            self.temp_card_id = card_id
            sql = "SELECT records.id, book.book_id, book.category, book.title, book.press, \
                 book.year, book.author, book.price, records.due_date FROM book \
                 INNER JOIN records ON book.book_id = records.book_id \
                 WHERE records.card_id = %s AND records.return = 0 \
                 Order by records.due_date"
            self.cursor.execute(sql, (card_id,))
            results = self.cursor.fetchall()
            if len(results) == 0:
                ui_admin.output.clear()
                ui_admin.output.append("No borrowed books found.")
            else:
                ui_admin.output.clear()
                ui_admin.output.append("Borrowed books:")
                for result in results:
                    result = result[:7] + (float(result[7]),) + (result[8].strftime("%Y-%m-%d"),)
                    ui_admin.output.append(str(result))
        except Exception as e:
            ui_admin.output.clear()
            ui_admin.output.append(f"Error: {e}")

    def borrow(self, ui_admin):
        if not self.Login:
            ui_admin.output.clear()
            ui_admin.output.append("Login first.")
            return
        try:
            ui_admin.output.clear()
            if self.temp_card_id == "00000000" :
                ui_admin.output.append("Input CardID first")
                return
            book_id = ui_admin.bookid.text()
            sql = "SELECT stock FROM book WHERE book_id = %s"
            self.cursor.execute(sql, (book_id,))
            result = self.cursor.fetchone()
            if result is None:
                ui_admin.output.clear()
                ui_admin.output.append("Book not found.")
                return
            stock = result[0]
            if stock == 0:
                sql = "SELECT MIN(due_date) FROM Records WHERE book_id = %s AND `return` = 0"
                self.cursor.execute(sql, (book_id,))
                result = self.cursor.fetchone()
                if result[0] is None:
                    ui_admin.output.clear()
                    ui_admin.output.append("The book is out of stock and no one has borrowed it before.")
                else:
                    ui_admin.output.clear()
                    return_date = result[0].strftime("%Y-%m-%d")
                    ui_admin.output.append(f"The book is out of stock. The earliest return date is {return_date}.")
            else:
                borrow_date = datetime.date.today()
                due_date = borrow_date + datetime.timedelta(days=30)
                sql = "INSERT INTO Records (book_id, card_id, borrow_date, due_date, admin_id, `return`) \
                VALUES (%s, %s, %s, %s, %s, 0)"
                self.cursor.execute(sql, (book_id, self.temp_card_id, borrow_date, due_date, self.admin_id))
                sql = "UPDATE book SET stock = %s WHERE book_id = %s"
                self.cursor.execute(sql, (stock-1, book_id))
                self.conn.commit()
                ui_admin.output.clear()
                ui_admin.output.append("Borrow success.")
        except Exception as e:
            ui_admin.output.clear()
            ui_admin.output.append(f"Error: {e}")
            
    def book_return(self, ui_admin):
        if not self.Login:
            ui_admin.output.clear()
            ui_admin.output.append("Login first.")
            return
        try:
            ui_admin.output.clear()
            if self.temp_card_id == "00000000":
                ui_admin.output.append("Input CardID first")
                return
            record_id = ui_admin.RecordID.text()
            sql = "SELECT book_id, card_id FROM records WHERE id = %s AND `return` = 0 "
            self.cursor.execute(sql, (record_id,))
            result = self.cursor.fetchone()
            if result is None:
                ui_admin.output.append("No such borrow record!")
                return
            if result[1] != self.temp_card_id:
                ui_admin.output.append("Return the book borrowed by yourself.")
                return
            book_id = result[0]
            sql = "SELECT stock FROM book WHERE book_id = %s"
            self.cursor.execute(sql, (book_id,))
            result = self.cursor.fetchone()
            if result is None:
                ui_admin.output.clear()
                ui_admin.output.append("Book not found.")
                return
            stock = result[0]
            sql = "UPDATE Records SET return_date = %s, `return` = 1 \
            WHERE id = %s"
            self.cursor.execute(sql, (datetime.date.today(), record_id))
            sql = "UPDATE book SET stock = %s WHERE book_id = %s"
            self.cursor.execute(sql, (stock+1, book_id))
            self.conn.commit()
            ui_admin.output.clear()
            ui_admin.output.append("Return success.")
        except Exception as e:
            ui_admin.output.clear()
            ui_admin.output.append(f"Error: {e}")

    def add_single_newbook(self, ui_admin):
        if not self.Login:
            ui_admin.output.clear()
            ui_admin.output.append("Login first.")
            return
        try:
            ui_admin.output.clear()
            bookID = ui_admin.bookid.text()
            category = ui_admin.category.text()
            title = ui_admin.title.text()
            press = ui_admin.press.text()
            year = ui_admin.year.text()
            author = ui_admin.author.text()
            price = ui_admin.price.text()
            sql = "SELECT * FROM book WHERE book_id = %s"
            self.cursor.execute(sql, (bookID,))
            result = self.cursor.fetchone()
            if result is None:
                sql = "INSERT INTO book VALUES (%s, %s, %s, %s, %s, %s, %s, %s, %s)"
                self.cursor.execute(sql,
                                    (bookID, category, title, press, int(year), author, float(price), int(1), int(1)))
                self.conn.commit()
                ui_admin.output.clear()
                ui_admin.output.append("New book added successfully!")
            else:
                # check if other fields are consistent with the existing data
                if result[1] != category or result[2] != title or result[3] != press or result[4] != int(year) or \
                        result[5] != author or result[6] != float(price):
                    # you can either raise an error or overwrite the existing data
                    # here I choose to raise an error
                    raise Exception("The input data is inconsistent with the existing data.")
                else:
                    sql = "UPDATE book SET stock = stock + %s , total = total + 1 WHERE book_id = %s"
                    self.cursor.execute(sql, (int(1), bookID))
                    self.conn.commit()
                    ui_admin.output.clear()
                    ui_admin.output.append("Book stock updated successfully!")
        except Exception as e:
            ui_admin.output.clear()
            ui_admin.output.append(f"Error: {e}")

    def add_multi_newbook(self, ui_admin):
        if not self.Login:
            ui_admin.output.clear()
            ui_admin.output.append("Login first.")
            return
        try:
            ui_admin.output.clear()
            filename = ui_admin.fileName.text()
            with open(filename, "r") as f:
                lines = f.readlines()
            for line in lines:
                line = line.strip()[1:-1]
                data = tuple(line.split(", "))
                if len(data) != 8:
                    ui_admin.output.clear()
                    ui_admin.output.append("Invalid input! Please check the file and try again.")
                    return
                sql = "SELECT * FROM book WHERE book_id = %s"
                self.cursor.execute(sql, (data[0],))
                result = self.cursor.fetchone()
                if result is None:
                    sql = "INSERT INTO book VALUES (%s, %s, %s, %s, %s, %s, %s, %s, %s)"
                    self.cursor.execute(sql, (data[0], data[1], data[2], data[3], int(data[4]), data[5], float(data[6]), int(data[7]), int(data[7])))
                    self.conn.commit()
                    ui_admin.output.append(f"New book {data[0]} added successfully!")
                else:
                    sql = "UPDATE book SET stock = stock + %s, total = total + %s WHERE book_id = %s"
                    self.cursor.execute(sql, (int(data[7]), int(data[7]), data[0]))
                    self.conn.commit()
                    ui_admin.output.append(f"Book {data[0]} stock updated successfully!")
            ui_admin.output.append("All books added/updated successfully!")
        except Exception as e:
            ui_admin.output.clear()
            ui_admin.output.append(f"Error: {e}")


    def add_card(self, ui_admin):
        if not self.Login:
            ui_admin.output.clear()
            ui_admin.output.append("Login first.")
            return
        try:
            ui_admin.output.clear()
            new_card_id = ui_admin.cardIDAddIn.text()
            new_name = ui_admin.nameInput_4.text()
            new_department = ui_admin.deptInput.text()
            new_type = ui_admin.comboBox.currentText()
            if len(new_card_id) != 8 or len(new_name) > 30 or len(new_department) > 40 or len(new_type) > 20:
                ui_admin.output.append("Invalid input! Please check your input and try again.")
                return
            sql = "INSERT INTO card (card_id, name, department, type) VALUES (%s, %s, %s, %s)"
            self.cursor.execute(sql, (new_card_id, new_name, new_department, new_type))
            self.conn.commit()
            ui_admin.output.append(f"New card {new_card_id} added successfully!")
        except Exception as e:
            ui_admin.output.clear()
            ui_admin.output.append(f"Error: {e}")
    
    def delete_card(self, ui_admin):
        if not self.Login:
            ui_admin.output.clear()
            ui_admin.output.append("Login first.")
            return
        try:
            ui_admin.output.clear()
            card_id = ui_admin.cardIDAddIn.text()
            sql = "SELECT * FROM card WHERE card_id = %s"
            self.cursor.execute(sql, (card_id,))
            result = self.cursor.fetchone()
            if result is None:
                ui_admin.output.append("Wrong card ID.")
                return
            sql = "SELECT COUNT(*) FROM records WHERE card_id = %s AND `return` = 0"
            self.cursor.execute(sql, (card_id,))
            result = self.cursor.fetchone()
            if result[0] > 0:
                ui_admin.output.append(f"Cannot delete card because \
                there are {result[0]} unreturned records.")
                return
            sql = "DELETE FROM card WHERE card_id = %s"
            self.cursor.execute(sql, (card_id,))
            self.conn.commit()
            ui_admin.output.append(f"Card {card_id} deleted successfully!")
        except Exception as e:
            ui_admin.output.clear()
            ui_admin.output.append(f"Error: {e}")

