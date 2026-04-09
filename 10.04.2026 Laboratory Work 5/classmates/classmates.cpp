#include "classmates.h"
#include "./ui_classmates.h"
#include <QString>

classmates::classmates(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::classmates)
{
    ui->setupUi(this);

    filldata();
    updateDisplay();
}

classmates::~classmates()
{
    delete ui;
}

//Заполнение класса
void classmates::filldata(){
    QSet<QString> AnnaGuest;                //экземпляр Анна
    AnnaGuest << "Виктор" << "Анастасия";   //Заполнение посетителей
    classMates["Анна"] = AnnaGuest;         //Добавляем в список учеников

    QSet<QString> AnastasyaGuest;               //экземпляр Анастасия
    AnastasyaGuest << "Анна" << "Виктор";       //Заполнение посетителей
    classMates["Анастасия"] = AnastasyaGuest;   //Добавляем в список учеников

    QSet<QString> ViktorGuest;          //экземпляр Виктор
    ViktorGuest << "Анна";              //Заполнение посетителей
    classMates["Виктор"] = ViktorGuest; //Добавляем в список учеников
}

//Отображение класса
void classmates::updateDisplay(){
    ui->textEdit->clear();  //Очистка текстового поля

    for(auto it = classMates.begin(); it != classMates.end(); ++it){
        QString student = it.key();
        QSet<QString> guests = it.value();

        ui->textEdit->append("Ученик: " + student);
        ui->textEdit->append("Был в гостях у: ");

        for(QString guestName : guests){
            ui->textEdit->append(guestName);
        }
        ui->textEdit->append(" ");
    }
}


void classmates::on_pushButton_clicked()
{
    //Проверка наличия списка учеников
    if(classMates.isEmpty()) {
        ui->lineEdit->setText("Список пуст");
        return;
    }

    //Получаем первое множество
    auto it = classMates.begin();
    QSet<QString> commonGuests = it.value();

    //Применение метода пересечения
    for(; it != classMates.end(); ++it) {
        commonGuests.intersect(it.value());
    }

    //Вывод результата
    if(commonGuests.isEmpty()) {
        ui->lineEdit->setText("Нет человека");
    }
    else {
        QString result;
        for(QString person : commonGuests) {
            result += person + " ";
        }
        ui->lineEdit->setText(result);
    }
}

