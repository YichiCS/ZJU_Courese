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