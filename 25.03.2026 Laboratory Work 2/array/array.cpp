#include "array.h"
#include "./ui_array.h"

array::array(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::array)
{
    ui->setupUi(this);
}

array::~array()
{
    delete ui;
}

void array::on_pushButton_clicked()
{
    //Создание строк матрицы
    for(int i = 0; i < 5; i++){
        QVector<int> vec;
        for(int j = 0; j <= i; j++){
            vec.append(i*j);
        }
        matrix.append(vec);
    }
    //Количество строк
    strCount = 5;
    //Очистка перед выводом матрицы
    ui -> textEdit->clear();

    //Вывод матрицы
    for(int i = matrix.length() - 1; i >= 0; i--)
    {
        QString str = "";
        for(int j = 0; j < matrix[i].length(); j++)
        {
            str += QString::number(matrix[i][j]) + " | ";
        }
        ui->textEdit->append(str);
    }
}

