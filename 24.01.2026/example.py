#Class pasport

class Passport:
    #Поля и свойства классов
    def __init__(self, surname, name, lastname, series, number, birth_date):
        self.surname = surname
        self.name = name
        self.lastname = lastname
        self.series = series
        self.number = number
        self.birth_date = birth_date

    #Метод вывода информации на экран
    def display_info(self):
        print(f"Паспортные данные: {self.surname} {self.name} {self.lastname}")
        print(f"Серия: {self.series}, Номер: {self.number}")
        print(f"Дата рождения: {self.birth_date}")
        print("*" * 30,"\n")

#Создание объектов
#1 Объект
passport1 = Passport(
    surname = None, #Фамилия отсуствует
    name = "Эдуард",
    lastname = "Аркадьевич",
    series = "7593",
    number = "857192",
    birth_date = "12.01.1990"
)

#2 Объект
passport2 = Passport(
    surname = "Цветаева",
    name = "Марина",
    lastname = "Ивановна",
    series = "1234",
    number = "123456",
    birth_date = "21.05.1985"
)

Passport.display_info(passport1)
Passport.display_info(passport2)



