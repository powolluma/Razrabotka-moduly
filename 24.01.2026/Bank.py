#Class BankAccount
class BankAccount:
    #Поля и свойства классов
    def __init__(self, name, surname, age, money, credit):
        self.name = name
        self.surname = surname
        self.age = age
        self.money = money
        self.credit = credit

    #Метод вывода информации на экран
    def display_info(self):
        print(f"\n\nИНФОРМАЦИЯ О КЛИЕНТЕ БАНКА")
        print(f"Имя: {self.name}")
        print(f"Фамилия: {self.surname}")
        print(f"Возраст: {self.age}")
        print(f"Счет: {self.money}")
        print(f"Наличие кредитов: {self.credit}")

    #Метод пополнения счета
    def money_in(self):
        print("ПОПОЛНЕНИЕ СЧЕТА")
        sum = int(input(f"Какую сумму вы хотите пополнить на ваш счет?\nОтвет: "))  
        self.money += sum
        print(f"Операция завершена!\nВаш счет: {self.money}")

    #Метод снятия денег со счета
    def money_out(self):
        print(f"СНЯТИЕ ДЕНЕГ СО СЧЕТА")
        sum = int(input(f"Какую сумму желаете снять?\nОтвет: "))
        
        if sum < self.money:
            self.money -= sum
            print(f"Операция завершена!\n Ваш счет: {self.money}")  #Условие: если сумма для снятия < счета, то снимаем
        else:                                                       #Иначе ошибка из за недостатка средств
            print(f"Ошибка! Недостаточно средств")

#Создание объектов
#1 Объект
user_1 = BankAccount(
    name = "Иван",
    surname = "Петров",
    age = 21,
    money = 100000,
    credit = "Отсуствует"
)

#2 Объект
user_2 = BankAccount(
    name = "Мария",
    surname = "Смирнова",
    age = 32,
    money = 20000,
    credit = "Имеется, погашен"
)

#BankAccount.money_in(user_1)      #Метод взноса денег 
#BankAccount.display_info(user_1)  #Метод вывода информации о клиенте банка

BankAccount.money_out(user_2)      #Метод снятия денег 
BankAccount.display_info(user_2)   #Метод вывода информации о клиенте банка
