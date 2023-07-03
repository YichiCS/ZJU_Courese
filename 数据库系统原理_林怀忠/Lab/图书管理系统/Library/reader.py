import connect

class Reader():

    def __init__(self):
        self.conn = connect.connect_to_library_db()
        self.cursor = self.conn.cursor()
        self.Login = False

    def login(self, ui_reader):
            card_id = ui_reader.cardIDInput.text()
            ui_reader.output.clear()
            sql = "SELECT * FROM card WHERE card_id = %s"
            self.cursor.execute(sql, (card_id,))
            result = self.cursor.fetchone()
            if result is None:
                ui_reader.output.append("Wrong card ID.")
                return
            ui_reader.output.append("Login successful!")
            ui_reader.output.append(f"Welcome, user {card_id}")
            self.card_id = card_id
            self.Login = True

    def getInfo(self, ui_reader):
        if self.Login == False:
            ui_reader.output.clear()
            ui_reader.output.append("Login first.")
            return
        try:
            sql = "SELECT * FROM card WHERE card_id = %s"
            ui_reader.output.clear()
            ui_reader.output.append("Here are your information :D")
            self.cursor.execute(sql, (self.card_id,))
            result = self.cursor.fetchone()
            card_id, name, department, card_type = result
            ui_reader.output.append(f"card_id: {card_id}")
            ui_reader.output.append(f"Name: {name}")
            ui_reader.output.append(f"Department: {department}")
            ui_reader.output.append(f"Type: {card_type}")
        except Exception as e:
            ui_reader.output.clear()
            ui_reader.output.append(f"Error: {e}")

    def updateInfo(self, ui_reader):
        if self.Login == False:
            ui_reader.output.clear()
            ui_reader.output.append("Login first.")
            return
        try:
            if ui_reader.cardIDInput.text() != self.card_id :
                ui_reader.output.append("Cannot update card ID")
                return
            department = ui_reader.deptInput.text()
            name = ui_reader.nameInput.text()
            card_type = ui_reader.comboBox.currentText()
            sql = "UPDATE card SET name = %s, department = %s, type = %s WHERE card_id = %s"
            self.cursor.execute(sql, (name, department, card_type, self.card_id))
            self.conn.commit()
            ui_reader.output.clear()
            ui_reader.output.append("Update successfully!")
            ui_reader.output.append(f"card_id: {self.card_id}")
            ui_reader.output.append(f"Name: {name}")
            ui_reader.output.append(f"Department: {department}")
            ui_reader.output.append(f"Type: {card_type}")
            return
        except Exception as e:
            ui_reader.output.clear()
            ui_reader.output.append(f"Please Input your card ID to Login. {e}")
