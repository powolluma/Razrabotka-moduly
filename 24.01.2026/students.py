#Class Students
class Students:
    #Поля и свойства классов
    def __init__(self, name, age, course, gpa, student_id):
        self.name = name
        self.age = age
        self.course = course
        self.gpa = gpa
        self.student_id = student_id

    #Метод вывода информации на экран
    def display_info(self):
        print(f"\n\nИНФОРМАЦИЯ О СТУДЕНТЕ")
        print(f"Имя и Фамилия: {self.name}")
        print(f"Возраст: {self.age}")
        print(f"Курс: {self.course}")
        print(f"Средний балл: {self.gpa}")
        print(f"Номер студентческого билета: {self.student_id}")

    #Метод увеличения курса студента на 1
    def increase_course(self):
        print(f"Студент {self.name} на {self.course} курсе")
        new_course = int(input(f"На какой курс перенести студента?\nОтвет: "))  #Получаем номер курса, на который поменять

        if new_course == 1 or new_course == 2 or new_course == 3 or new_course == 4 or new_course == 5: #Условие: если меняющийся курс не больше 5, то меняем
            self.course = new_course                                                                    #Инача ошибка
            print(f"Стунент перенесен на {self.course} курс")
        else:
            print(f"Ошибка!")

    #Метод проверки среднего балла студента
    def update_gpa(self):
        print(f"Текущий средний балл студента {self.name}: {self.gpa}")
        print(f"Начинаем перепроверку среднего балла")

        if self.gpa % 1 >= 0.5: 
            new_gpa = round(self.gpa)  
            print(f"Средний балл с {self.gpa} на {new_gpa}")    #Условие: если средний балл имеет плавающее значение 5 или больше, то обновляем средний балл
            self.gpa = new_gpa                                  #Иначе не округляем
        else:
            print(f"Средний балл {self.gpa} не требует округления")

#Создание объектов
#1 Объект
student_1 = Students(
    name = "Иван Петров",
    age = "19",
    course = 1,
    gpa = 4.2,
    student_id = "ST001"
)

#2 Объект
student_2 = Students(
    name = "Мария Сидорова",
    age = "20",
    course = 2,
    gpa = 4.7,
    student_id = "ST002"
)

#Students.increase_course(student_1)  #Метод увеличения курса
#Students.display_info(student_2)     #Метод вывода информации о студенте

Students.update_gpa(student_2)        #Метод проверки среднего балла
Students.display_info(student_2)      #Метод вывода информации о студенте