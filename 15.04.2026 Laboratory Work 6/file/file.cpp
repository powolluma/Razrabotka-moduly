#include "file.h"
#include "./ui_file.h"
#include <QFile>
#include <QMessageBox>
#include <cmath>

file::file(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::file)
{
    ui->setupUi(this);
}

file::~file()
{
    delete ui;
}

void file::on_pushButton_2_clicked()
{
    QFile myFile("/home/watr1x/Документы/Coding/Qt/f"); //путь к файлу

    if(!myFile.exists()){
        QMessageBox::warning(this, "Ошибка!", "Файл не открывается");   //проверка существования файла
        return;
    }

    if(!myFile.open(QIODevice::ReadOnly)){
        QMessageBox::warning(this, "Ошибка!", "Файл недоступен для чтения"); //проверка доступности файла
        return;
    }

    QTextStream stream(&myFile);    //объект класса и передача ссылки на файл

    QString buffer = stream.readAll(); //считывание файла

    ui->textEdit_2->setText(buffer); //вывод в текст

    myFile.close(); //закрытие файла
}




void file::on_pushButton_clicked()
{

    QStringList numbers = ui->textEdit_2->toPlainText().split(" ", Qt::SkipEmptyParts); //получение текста

    QList<double> values;   //массив для чисел

    for(int i = 0; i < numbers.length(); i++){
        double val = numbers[i].toDouble(); //преобразование в число
        values.append(val); //добавление в массив
    }

    int n = values.size();
    QString result;

    //наибольшее
    double maxVal = values[0];
    for(int i = 0; i < n; i++){
        if(values[i] > maxVal){
            maxVal = values[i];
        }
    }

    //наименьшее с четным номером
    double minEven = 0;
    bool hasEven = false;

    for(int i = 0; i < n; i++){
        if((i + 1) % 2 == 0){
            if(!hasEven || values[i] < minEven){
                minEven = values[i];
                hasEven = true;
            }
        }
    }

    //наибольшее с нечетным номером
    double maxOdd = 0;

    for (int i = 0; i < n; i += 2) {
        double absVal = fabs(values[i]);
        if (absVal > maxOdd) {
            maxOdd = absVal;
        }
    }

    //разность
    double diffenent = values[0] - values[n-1];

    //Запись результата
    result = "Вычисления\n";
    result += "Наибольшее: " + QString::number(maxVal) + "\n";
    result += "Наииеньшее с четным индексом: " + QString::number(minEven) + "\n";
    result += "Наибольшее с нечетным номером: " + QString::number(maxOdd) + "\n";
    result += "Разность между первым и последним: " + QString::number(diffenent) + "\n";

    //вывод
    ui->textEdit->setText(result);
}

