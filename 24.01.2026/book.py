#Class books
class Book:
    #Поля и свойства классов
    def __init__(self, title, author, year, isbn, pages):
        self.title = title
        self.author = author
        self.year = year
        self.isbn = isbn
        self.pages = pages
        self.check = True   #Для изменения статуса доступности книги

    #Метод вывода инфомации на экран
    def display_info(self):
        print(f"\n\nИНФОРМАЦИЯ О КНИГЕ")
        print(f"Название: {self.title}")
        print(f"Автор: {self.author}")
        print(f"Год издания: {self.year}")
        print(f"ISBN номер: {self.isbn}")
        print(f"Количество страниц: {self.pages}")

    #Метод взятия книги и измененения статуса доступности
    def borrow_book(self):
        print(f"Меняем статус доступности книги {self.title}")
        
        if self.check:
            self.check = False
            print("Книга выдана")                   #Условие: если статус книги True, то выдаем книгу, меняем статус и делаем недоступной
        else:                                       #Иначе не можем выдать книгу
            print("Книга не может быть выдана") 

    #Метод возврата книги и изменения статуса
    def return_book(self):
        print(f"Меняем статус доступности книги {self.title}")

        if not self.check:  
            self.check = True 
            print("Книга возвращена в библиотеку")              #Условие: если статус False, то возвращаем книгу, меняем статус и делаем доступной
        else:                                                   #Иначе нечего возвращать в библиотеку
            print("Книга уже в библиотеке, нечего возвращать")
                
#Создание объектов
#1 Объект
book_1 = Book(
    title = "Преступление и наказание",
    author = "Федор Достоевский",
    year = 1866,
    isbn = "978-5-17-090879-1",
    pages = 608
)

#2 Объект
book_2 = Book(
    title = "Мастер и Маргарита",
    author = "Михаил Булгаков",
    year = 1967,
    isbn = "978-5-389-06204-3",
    pages = 480
)

# Book.borrow_book(book_1)  #Метод выдачи книги 
# Book.display_info(book_1) #Метод вызова информации о книге

Book.return_book(book_2)    #Метод возврата книги
Book.display_info(book_2)   #Метод вывода информации о книге

