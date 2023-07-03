import connect


def show_all_book(ui_search):
    try:
        conn = connect.connect_to_library_db()
        cursor = conn.cursor()
        sql = "SELECT * FROM book" + f" ORDER BY {ui_search.OrderKeyword.currentText()}"
        cursor.execute(sql)
        results = cursor.fetchall()
        for result in results:
            result = result[:6] + (float(result[6]),) + result[7:9]
            ui_search.Result.append(str(result))
    except Exception as e:
        ui_search.Result.append(f"Error: {e}")

def search_books(ui_search):
    try:
        conn = connect.connect_to_library_db()
        cursor = conn.cursor()
        results = []
        columns = ["book_id", "category", "title", "press", "year", "author", "price", "total", "stock"]
        option = ui_search.keywordField.currentIndex()
        option1 = ui_search.OrderKeyword.currentIndex()

        if option != 4 and option != 6:
            keyword = ui_search.keywordInput.text()
            sql = f"SELECT * FROM book WHERE {columns[option]} LIKE %s" + f" ORDER BY {columns[option1]}"
            cursor.execute(sql, ('%' + keyword + '%',))
        elif option == 4:
            year1 = ui_search.keyBottom.text()
            year2 = ui_search.keyUpper.text()
            sql = f"SELECT * FROM book WHERE year BETWEEN %s AND %s" + f" ORDER BY {columns[option1]}"
            cursor.execute(sql, (year1, year2))
        elif option == 6:
            price1 = ui_search.keyBottom.text()
            price2 = ui_search.keyUpper.text()
            sql = f"SELECT * FROM book WHERE price BETWEEN %s AND %s" + f" ORDER BY {columns[option1]}"
            cursor.execute(sql, (price1, price2))
        else:
            ui_search.Result.append("Invalid option! Please try again.")
        results = cursor.fetchall()
        if len(results) == 0:
            ui_search.Result.append("No results found.")
        else:
            ui_search.Result.append(f"Found {len(results)} results:")
            for result in results:
                result = result[:6] + (float(result[6]),) + result[7:9]
                ui_search.Result.append(str(result))
    except Exception as e:
        ui_search.Result.append(f"Error: {e}")
