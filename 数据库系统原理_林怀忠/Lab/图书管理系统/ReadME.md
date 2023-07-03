# Lab5 图书管理系统实验

## 实验目的
设计并实现一个精简的图书管理系统, 要求具有图书入库、查询、借书、还书、借书证管理等功能。通过该图书馆系统的设计与实现，提高学生的系统编程能力，加深对数据库系统原理及应用的理解。

## 成果
实现了一个对图书馆数据库进行操作的图书库管理系统。实现了基本的**用户登录**、**图书入库**、**借阅/归还书籍**、**查询馆藏**、**用户管理**等功能。针对用户体验，我设计了一个**UI-based 的图书库管理系统**，用户可以在更加友好的可视化界面上进行操作。

在这个过程中我用到了 **MySQL**、**Python**、**PyMySQL**、**PyQt** 等技术来构建整个图书库管理系统，具体的技术细节将在后续章节提及。在本次报告的最后我还总结了本次实验的感想和体会，以及在实现整个系统过程中的不足和待改进的部分。

你可以在```Library```中运行```python run.py```来体验本程序，请提前保证你连接了对应的数据库以及程序所需要的库。

本报告和源码将在我的Github公开 https://github.com/YichiCS/Principles-of-Database-Systems/tree/main/Lab/Lab5  
如果你在运行过程中有任何疑惑或者发现了任何问题，欢迎联系 yichics02@gmail.com 与我交流

## 文件结构
本次图书库管理系统分为三个部分：
* 图书库数据库
* 前端用户交互界面 ```main.py``` ```admin_ui.py``` ```reader_ui.py``` ```search_ui.py``` 
* 后端数据处理类 ```admin.py``` ```reader.py``` ```util.py``` ```connect.py```
* 前后端交互方法 ```run.py```

## 系统设计详解

### 图书库数据库的设计
为能良好地存储图书库管理所需要的数据，我们设计了如下名为```Library```的数据库，包含以下四张表：
* ```Admin```
  * ```admin_id```, char(8)
  * ```password```, varchar(30)
  * ```name```, varchar(40)
  * ```contact```, varchar(40)
* ```Book```
  * ```book_id```, char(8)
  * ```category```, varchar(30)
  * ```title```, varchar(30)
  * ```press```, varchar(30)
  * ```year```, int 
  * ```author```, varchar(20)
  * ```price```, decimal
  * ```total```, int 
  * ```stock```, int 
* ```Card```
  * ```card_id```, char(8)
  * ```name```, varchar(30)
  * ```department```, varchar(30)
  * ```type```, varchar(20)
* ```Records```
  * ```id```, int 
  * ```book_id```, char(8)
  * ```card_id```, char(8)
  * ```borrow_date```, date
  * ```due_date```, date
  * ```admin_id```, char(8)
  * ```return```, tinyint
  * ```return_date```, date

### 前端用户交互界面的设计
在图书库管理系统中，我设计了四个主要的前端交互界面用于实现整个图书库管理系统，它们分别是：
* 图书库管理系统首页```main.py```，用于实现 **读者登陆/管理员登陆/搜索**
* 管理员交互终端```admin_ui.py```，用于实现 **管理员账号密码登陆/图书入库（单本、批量）/图书借阅与归还/用户管理**
* 读者交互终端```reader.py```，用于实现 **读者卡号登陆/读者信息查询/读者信息自定义**
* 搜索终端```search_ui.py```，用于实现 **展现所有馆藏/根据关键自搜索馆藏/根据关键字排列搜索结果**

接下来介绍各个前端交互界面。

#### 图书库管理系统首页
![fig2](fig/fig2.png)
在图书库管理系统首页中，总共有四个按钮，他们分别是：
* ```Admin Login```，用于实现 **跳转至管理员交互终端**
* ```Search```，用于实现 **跳转至搜索终端**
* ```Reader Login```，用于实现 **跳转至读者交互终端**
* ```Exit```，用于实现 **退出**


#### 管理员交互终端
![fig3](fig/fig3.png)
在管理员交互终端中，总共有九个按钮，他们分别是：
* ```Login```，用于实现 **管理员账号密码登陆**
* ```Inquire```，用于实现 **输入卡号，输出借阅记录**
* ```Borrow```，用于实现 **输入书号，借阅图书**
* ```Return```，用于实现 **输入借阅记录号，归还图书**
* ```AddSingle```， 用于实现 **输入图书信息，入库单本图书**
* ```AddMulti```，用于实现 **输入文件名，入库批量图书**
* ```AddCard```，用于实现 **输入读者信息，创建新读者**
* ```DeleteCard```，用于实现 **输入卡号，删除已有读者**
* ```Exit```，用于实现 **退出**


#### 读者交互终端
![fig4](fig/fig4.png)
在读者交互终端中，总共有五个按钮，他们分别是：
* ```Login```，用于实现 **读者卡号登陆**
* ```Self Information```，用于实现 **查看读者信息**
* ```Update Information```，用于实现 **更新读者信息**
* ```Search```，用于实现 **跳转到搜索终端**
* ```Exit```，用于实现 **退出**


#### 搜索终端
![fig5](fig/fig5.png)
在搜索终端中，总共有三个按钮，他们分别是：
* ```Show All Books```，用于实现 **展现所有馆藏**
* ```Search```， 用于实现**根据条件搜索**
* ```Exit```，用于实现 **退出**

### 后端数据处理类的设计
后端处理类用于处理前端用户交互界面传入的参数，对链接的数据库内容进行操作和查询。根据用户类型的不同，我么的后院数据处理类由以下几个文件组成：
* ```connect.py```，用于实现**数据库管理系统和数据库的链接**
* ```admin.py```，用于实现**管理员对数据库的操作**
* ```reader.py```，用于实现**读者对数据库的访问**
* ```util.py```，用于实现**一般用户对数据库的访问**

接下来依次介绍各个文件以及其中实现的功能以及设计思路。

#### 数据库管理系统和数据库的链接

在这个模块中我利用第三方库 PyMySQL 实现了对外部数据库的链接。在函数```connect_to_library_db()```中我利用```pymysql.connect()```获得了对外部数据库的链接，并将这个链接返回，打印链接结果，注意到这个链接成功与否并未打印到前端界面而是打印到 Terminnal 中。

```py
import pymysql

def connect_to_library_db():
    print("Hello, Library!")

    try:
        conn = pymysql.connect(
            host = '127.0.0.1',
            user = 'root', 
            passwd = 'mysql020915',
            port = 3306,
            db = 'Library',
            charset = 'utf8'
        )

        print("Database connection established successfully!")
        return conn

    except pymysql.Error as e:
        print("Error connecting to the database: ", e)
        return None
```


#### 管理员对数据库的操作

为了正确实现管理员对数据库的操作，首先我们设计一个```Admin```类，在这个类中我创建一个对数据库的链接```conn```，利用```conn.cursor()```从链接中获取一个访问光标，以便于后于函数对数据库进行访问和修改。
```py
class Admin():

    # 初始化 Admin 对象
    def __init__(self):
        self.conn = connect.connect_to_library_db()
        self.cursor = self.conn.cursor()
        self.admin_id = "00000000"
        self.temp_card_id = "00000000"
        self.Login = False
    
```

##### 管理员登陆

为实现管理员的登陆，我在```Admin```类下设计了```login```函数。这个函数从前端交互界面读入管理员的账号和密码，利用 SQL 语句在数据库中筛选，如果存在该账号且对应的密码正确，提示正确登陆。并将类中的```admin_id```设置成读入的账号和```Login```设置为```True```。如果未找到该账号，则提示账号不存在。如果账号存在但是密码不匹配，则提示密码错误。
```py
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
```

##### 账号借阅记录查询

为实现更加用户友好的图书借阅和归还，我的思路是先实现一个对当前用户借阅记录查询函数，再进一步实现下游任务。为此我设计了```inquire```函数，在管理员完成登陆后，从前端界面读入一个读者账号，利用 SQL 在数据库中查找，如果存在该账号，我们将```Card```和```Records```以```INNER JOIN```的方式连接起来，在其中借阅账号为读入账号且尚未归还的记录，按照预定归还日期从近到远排序，如果查找到相关记录将其打印。如果未找到该账号，则提示该账号不存在。如果该账号没有借阅记录，则提示目前并未借阅图书。

同时在完成查询后，我将读入的账号设置为```Amin```类中的```temp_card_id```后续的借阅和归还操作就是针对这个账号进行操作。
```py
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
        if len(results) == 0:
            ui_admin.output.append("No such card.")
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
```

##### 图书借阅功能

现在开始实现查阅之后的图书借阅，设计一个```borrow```函数中。首先检查```Amin```类中的```temp_card_id```是否被设置，即是否查询过账号的借阅记录，如果输入过，读入一个图书ID，在数据库中的```Book```表中搜索，如果图书ID存在库中且对应的图书存量不为0则成功借阅，如果该书在库中且存量为零，则提示一个最近的归还日期。

这样的设计可以保证对图书的借阅成功与否只取决于以下几个元素：
* 尝试借阅的账户存在
* 尝试借阅的图书存在库中
* 尝试借阅的图书库存量不为0

```py
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
                ui_admin.output.append(\
                "The book is out of stock and no one has borrowed it before.")
            else:
                ui_admin.output.clear()
                return_date = result[0].strftime("%Y-%m-%d")
                ui_admin.output.append(\
                f"The book is out of stock. The earliest return date is {return_date}.")
        else:
            borrow_date = datetime.date.today()
            due_date = borrow_date + datetime.timedelta(days=30)
            sql = "INSERT INTO Records \
            (book_id, card_id, borrow_date, due_date, admin_id, `return`) \
            VALUES (%s, %s, %s, %s, %s, 0)"
            self.cursor.execute(sql, \
            (book_id, self.temp_card_id, borrow_date, due_date, self.admin_id))
            sql = "UPDATE book SET stock = %s WHERE book_id = %s"
            self.cursor.execute(sql, (stock-1, book_id))
            self.conn.commit()
            ui_admin.output.clear()
            ui_admin.output.append("Borrow success.")
    except Exception as e:
        ui_admin.output.clear()
        ui_admin.output.append(f"Error: {e}")
```
##### 图书归还功能
现在开始实现查阅之后的图书归还，设计一个```book_return```函数，首先检查```Amin```类中的```temp_card_id```是否被设置，读入一个借阅记录ID，这个ID可在之前的查询中读出，在数据库中搜索是否有这么一条由该账号借阅的记录，如果有，更新```Records```和```Book```表中的数据，实现还书。

这样的设计可以保证对图书的归还成功与否只取决于以下几个元素：
* 尝试归还的账户存在
* 尝试归还的图书由本账户借阅
* 尝试归还的图书之前并未归还

```py           
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
```
##### 图书入库功能
为实现图书的单本入库和批量入库我分别设计了```add_single_newbook```和```add_multi_newbook```。

在```add_single_newbook```中从前端交互界面中读入图书相关的各个数据，检查库中是否已经存在同一本书，如果没有则插入一条新的记录。如果发现已有相同```book_id```的记录，检查记录中的内容是否冲突，如果冲突，显示图书信息有问题，如果没有冲突，图书库存和总量都加一。

在```add_multi_newbook```中从前端交互界面中读入一个文件名，按照相同的逻辑按行对图书进行入库，注意到由于数据中含有图书数量，此时如果更新记录，图书库存和总量加上的是对应的入库数量。
```py
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
                self.cursor.execute(sql, (data[0], data[1], data[2], data[3], \
                int(data[4]), data[5], float(data[6]), int(data[7]), int(data[7])))
                self.conn.commit()
                ui_admin.output.append(f"New book {data[0]} added successfully!")
            else:
                sql = "UPDATE book SET stock = stock + %s, \
                total = total + %s WHERE book_id = %s"
                self.cursor.execute(sql, (int(data[7]), int(data[7]), data[0]))
                self.conn.commit()
                ui_admin.output.append(f"Book {data[0]} stock updated successfully!")
        ui_admin.output.append("All books added/updated successfully!")
    except Exception as e:
        ui_admin.output.clear()
        ui_admin.output.append(f"Error: {e}")

```

##### 增加新用户功能

为实现增加新用户的功能，设计一个```add_card```函数，从前端交互界面中分别读入所需要的数据，由于```card_id```被设置为主键，所以不必考虑重复，在数据表中插入对应的记录即可。
```py
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
        if len(new_card_id) != 8 or len(new_name) > 30 or \
        len(new_department) > 40 or len(new_type) > 20:
            ui_admin.output.append("Invalid input! Please check your input and try again.")
            return
        sql = "INSERT INTO card (card_id, name, department, type) VALUES (%s, %s, %s, %s)"
        self.cursor.execute(sql, (new_card_id, new_name, new_department, new_type))
        self.conn.commit()
        ui_admin.output.append(f"New card {new_card_id} added successfully!")
    except Exception as e:
        ui_admin.output.clear()
        ui_admin.output.append(f"Error: {e}")
```

##### 删除已有用户功能
为实现删除已有用户功能，设计一个```delete_card```函数，读入一个账号，在数据表中搜索记录，若存在则查询其借阅记录如果没有相关的未归还借阅记录，则成功删除。若账号不存在则提示错误账号，若存在未归还图书则提示尚有未归还图书不可删除该账号。
```py   
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
```

##### 其他设计
在具体实现中为保证管理员必须先登陆再操作，设计了一个```Login```变量用于检查管理员是否登陆，采用以下代码段
```py
if not self.Login:
    ui_admin.output.clear()
    ui_admin.output.append("Login first.")
    return
```
防止在未登录时点击按钮出现错误。此外，采用了
```py
try:
    # sentence
except Exception as e:
    # sentence 
```
来防止执行过程中出现的问题导致程序崩溃，有利于系统维护和程序纠错。

#### 读者对数据库的查询

为了正确实现管理员对数据库的操作，首先我们设计一个```Reader```类，在这个类中我创建一个对数据库的链接```conn```，利用```conn.cursor()```从链接中获取一个访问光标，以便于后于函数对数据库进行访问和修改。
```py
class Reader():

    def __init__(self):
        self.conn = connect.connect_to_library_db()
        self.cursor = self.conn.cursor()
        self.Login = False
```
##### 读者登陆

为了实现更加用户友好的用户查询，我在读者进行操作之前设计了一个```login```函数，读入读者的账号，利用 SQL 语句在数据库中筛选，如果存在该账号且对应的密码正确，提示正确登陆，并将```Reader```类中的```self.card_id```设置为对应的账号，```Login```设置为```True```。
```py
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
```
##### 读者信息展示
为实现对读者自身信息的查询，设计一个```getInfo```，对```Reader```类中的```self.card_id```在数据库中进行查询，输出其相关信息。
```py
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
```
##### 读者信息修改

为实现对读者信息的修改，设计一个```updateInfo```函数，从前端交互界面读入所需要的数据，检查```card_id```是否不变，若相同则对类中储存的账号在数据库中进行更新。如果```card_id```被改变，则提示不可改变账号本身。
```py
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
        sql = "UPDATE card SET name = %s, \
        department = %s, type = %s WHERE card_id = %s"
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
```
##### 其他设计
在具体实现中为保证管理员必须先登陆再操作，设计了一个```Login```变量用于检查管理员是否登陆，采用以下代码段
```py
if not self.Login:
    ui_admin.output.clear()
    ui_admin.output.append("Login first.")
    return
```
防止在未登录时点击按钮出现错误。此外，采用了
```py
try:
    # sentence
except Exception as e:
    # sentence 
```
来防止执行过程中出现的问题导致程序崩溃，有利于系统维护和程序纠错。

#### 一般用户对数据库的查询

##### 列出所有馆藏
为列出所有的馆藏，设计一个```show_all_book```函数，直接查找```book```中所有的记录，根据给定的关键词进行排序。
```py
def show_all_book(ui_search):
    try:
        cursor = conn.cursor()
        sql = "SELECT * FROM book" + f" ORDER BY {ui_search.OrderKeyword.currentText()}"
        cursor.execute(sql)
        results = cursor.fetchall()
        for result in results:
            result = result[:6] + (float(result[6]),) + result[7:9]
            ui_search.Result.append(str(result))
    except Exception as e:
        ui_search.Result.append(f"Error: {e}")
```

##### 搜索指定的图书
为实现搜索指定的图书，设计一个```search_book```函数，读入一个或者多个关键字，对于选定的关键词进行查找和排序。
```py
def search_books(ui_search):
    try:
        cursor = conn.cursor()
        results = []
        columns = ["book_id", "category", "title", "press", \
        "year", "author", "price", "total", "stock"]
        option = ui_search.keywordField.currentIndex()
        option1 = ui_search.OrderKeyword.currentIndex()

        if option != 4 and option != 6:
            keyword = ui_search.keywordInput.text()
            sql = f"SELECT * FROM book WHERE {columns[option]} LIKE %s" \
            + f" ORDER BY {columns[option1]}"
            cursor.execute(sql, ('%' + keyword + '%',))
        elif option == 4:
            year1 = ui_search.keyBottom.text()
            year2 = ui_search.keyUpper.text()
            sql = f"SELECT * FROM book WHERE year BETWEEN %s AND %s" \
            + f" ORDER BY {columns[option1]}"
            cursor.execute(sql, (year1, year2))
        elif option == 6:
            price1 = ui_search.keyBottom.text()
            price2 = ui_search.keyUpper.text()
            sql = f"SELECT * FROM book WHERE price BETWEEN %s AND %s" \
            + f" ORDER BY {columns[option1]}"
            cursor.execute(sql, (price1, price2))
        else:
            ui_search.Result.append("Invalid option! Please try again.")
        results = cursor.fetchall()
        if len(results) == 0:
            ui_search.Result.append("No results found.")
        else:
            ui_search.Result.append(f"Found {len(results)} results:")
            for result in results:
                ui_search.Result.append(str(result))
    except Exception as e:
        ui_search.Result.append(f"Error: {e}")

```
##### 其他设计
采用了
```py
try:
    # sentence
except Exception as e:
    # sentence 
```
来防止执行过程中出现的问题导致程序崩溃，有利于系统维护和程序纠错。

### 前后端交互方法设计
至此我完成了前端用户交互界面和后端数据处理类的设计，为链接二者我设计了一套前后端交互方法。这个方法具体体现在```run.py```中。实现这个方法后，也就正式实现了整个图书库管理系统。整个系统的功能可以用流程图表示。
![fig1](fig/fig1.png)
```py
class Main(QMainWindow):
    def __init__(self):
        super().__init__()
        self.ui_main = Ui_Main()
        self.ui_main.setupUi(self)

        self.ui_main.Search.clicked.connect(self.show_search_window)
        self.ui_main.Reader.clicked.connect(self.show_reader_window)
        self.ui_main.Admin.clicked.connect(self.show_admin_window)
        self.ui_main.Exit.clicked.connect(self.close_all_windows)

    # 管理员界面及其槽函数链接
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

    # 读者界面及其槽函数链接
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

    # 搜索界面及其槽函数链接
    def show_search_window(self):
        self.search_window = QMainWindow()
        self.ui_search = Ui_Search()
        self.ui_search.setupUi(self.search_window)
        self.search_window.show()

        self.ui_search.Exit.clicked.connect(self.search_window.close)
        self.ui_search.showAllBook.clicked.connect(self.show_all_book)
        self.ui_search.SearchButton.clicked.connect(self.show_search_book)

    # 对应的槽函数和后端数据处理类的函数链接与传递
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

# 主函数循环
if __name__ == "__main__":
    conn = connect.connect_to_library_db()
    app = QApplication(sys.argv)
    main_window = Main()
    main_window.show()
    sys.exit(app.exec_())
```
## 额外实现的功能
除去实现基本功能之外，我额外实现了以下的内容
* 实现了一个用户友好的前端UI以实现更好的用户交互
* 在图书查询中，实现了根据指定列的排序
* 在管理员操作中，针对用户交互设计了一个查询功能，为借阅和归还书本提供了更好的用户交互
* 在读者操作中，设计了一个读者登陆的功能，为读者功能提供了更好的用户交互
* 实现了更好的系统鲁棒性，所有的运行错误都会被正常打印，以便于系统维护


以上内容在系统设计讲解的过程中已经进行了详尽的说明。

## 实验总结
### 感想
1. 事实上在实验的一开始我设计了一个在 Terminal 进行交互的程序，在这个过程中我需要在函数中设计一个循环以相应用户的输入，而且需要对用户的输入进行识别和处理。在设计了 UI 后，我只需要将对应的 Button 连接到槽函数，就能方便地运行我所需要的函数。由于经历了这个程序的修改过程，体会到了二者之间实际上只有接口需要进行微调，内在的函数逻辑事实上还是不变的。    
2. 在设计终端的过程中，我发现我有两种设计的思路，一种是正如我现在设计的那样，针对需要的输入设计对应的输入框，另一种则是设计一个类似 Terminal 的图形界面。后者需要用户对指令有着更加熟悉的运用，相对来说在交互方面不是很友好，但是在设计上简单有效。  
3. 在设计函数的过程中，需要用到排序、冲突检查等功能，我发现单一地在函数中设计这些功能是笨重且低效的，因为 SQL 语句和数据库已经提供相对应的高效简洁的方法，比如 ```ORDER```、主键、外键等设计，如果熟练运用可以减少很大的代码量。

### 设计的不足之处
1. 程序的可维护性有待提高，事实上针对 UI 进行函数设计导致了我在打包函数时将整个窗体传入，这样一来当窗体中的部件改变就需要重新修改实现具体功能的函数。事实上在整个程序运行并测试完成之后我意识到可以将**部件作为参数传入函数**以实现更好的打包效果。  
2. 程序的安全性有待提高，在调用 SQL 语句的过程中我大多使用了直接将参数传入 SQL 语句中对应位置的方法，并未对传入的参数进行类型和格式的检查，这样一来使得数据库容易受到注入式攻击，可能会导致用户绕过登陆获取管理员权限的功能。对于这一问题需要对系统进行长久的测试才可以获得解决，考虑到该系统的目的在于熟悉数据库操作，故在此问题上不进行深究。
