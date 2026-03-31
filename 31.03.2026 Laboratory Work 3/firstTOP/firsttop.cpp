#include "firsttop.h"
#include "./ui_firsttop.h"

firstTOP::firstTOP(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::firstTOP)
{
    ui->setupUi(this);

    //Случайные
    srand(time(nullptr));

        //Создание списка и выводx
        for(int i = 0; i < 10; i++){
        int randomNumber = rand() %100 +1;
            list.append(randomNumber);
            ui->textEdit->append(QString::number(list.at(i)) + " ");
        }
}

firstTOP::~firstTOP()
{
    delete ui;
}

void firstTOP::on_pushButton_clicked()
{


    //Условия для выбора
    //При выборе добавления элемента
    if(ui->radioButton->isChecked()){
        int randomNumber_1 = rand() %100 +1;
        list.push_back(randomNumber_1);
    }
    //При выборе удаления элемента
    else if(ui->radioButton_2->isChecked()){
        list.removeLast();
    }

    //Очистка списка
    ui->textEdit->clear();

    QList<int>::iterator it = list.begin();
    while(it != list.end()){
        ui->textEdit->append(QString::number(*it) + " ");
        it++;
    }
}

