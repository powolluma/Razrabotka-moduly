#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <cmath>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

////////////////////////////////////////Цифры
void MainWindow::on_pushButton_clicked()
{
    ui->lineEdit->insert("1");
}
void MainWindow::on_pushButton_2_clicked()
{
    ui->lineEdit->insert("2");
}
void MainWindow::on_pushButton_3_clicked()
{
    ui->lineEdit->insert("3");
}
void MainWindow::on_pushButton_6_clicked()
{
    ui->lineEdit->insert("4");
}
void MainWindow::on_pushButton_7_clicked()
{
    ui->lineEdit->insert("5");
}
void MainWindow::on_pushButton_8_clicked()
{
    ui->lineEdit->insert("6");
}
void MainWindow::on_pushButton_11_clicked()
{
    ui->lineEdit->insert("7");
}
void MainWindow::on_pushButton_12_clicked()
{
    ui->lineEdit->insert("8");
}
void MainWindow::on_pushButton_13_clicked()
{
    ui->lineEdit->insert("9");
}
void MainWindow::on_pushButton_18_clicked()
{
    ui->lineEdit->insert("0");
}

//////////////////////////////////////////Арифметичесие операции
void MainWindow::on_pushButton_4_clicked()
{
    firstNumber = ui->lineEdit->text().toDouble();
    operation = "+";
    ui->lineEdit->clear();
    ui->lineEdit_2->setText(QString::number(firstNumber) + " +");
}

void MainWindow::on_pushButton_5_clicked()
{
    firstNumber = ui->lineEdit->text().toDouble();
    operation = "-";
    ui->lineEdit->clear();
    ui->lineEdit_2->setText(QString::number(firstNumber) + " -");
}
void MainWindow::on_pushButton_9_clicked()
{
    firstNumber = ui->lineEdit->text().toDouble();
    operation = "*";
    ui->lineEdit->clear();
    ui->lineEdit_2->setText(QString::number(firstNumber) + " *");
}
void MainWindow::on_pushButton_10_clicked()
{
    firstNumber = ui->lineEdit->text().toDouble();
    operation = "/";
    ui->lineEdit->clear();
    ui->lineEdit_2->setText(QString::number(firstNumber) + " /");
}

////////////////////////////Функция калькулятора
void MainWindow::calculate()
{
    //Проверка наличия операции
    if (operation.isEmpty()) return;

    //Второе число
    double secondNumber = ui->lineEdit->text().toDouble();
    double result = 0;

    //Вычисление
    if (operation == "+") {
        result = firstNumber + secondNumber;
    }
    else if (operation == "-") {
        result = firstNumber - secondNumber;
    }
    else if (operation == "*") {
        result = firstNumber * secondNumber;
    }
    else if (operation == "/") {
        if (secondNumber == 0) {
            ui->lineEdit->setText("Ошибка!");
            return;
        }
        result = firstNumber / secondNumber;
    }

    //Вывод
    ui->lineEdit->setText(QString::number(result));
    ui->lineEdit_2->setText(QString::number(firstNumber) + " " + operation + " " + QString::number(secondNumber) + " =");

    //Очистка операции
    operation = "";
}

///////////////////////////////////////////Вывод результата
void MainWindow::on_pushButton_15_clicked()
{
    calculate();
}

///////////////////////////////////////////Очистка строки
void MainWindow::on_pushButton_16_clicked()
{
    ui->lineEdit->setText("0");
    ui->lineEdit_2->clear();
    firstNumber = 0;
    operation = "";
}

///////////////////////////////////////////Смена знака числа
void MainWindow::on_pushButton_14_clicked()
{
    double numbers = ui->lineEdit->text().toDouble();
    numbers = -numbers;
    ui->lineEdit->setText(QString::number(numbers));
}

///////////////////////////////////////////Точка
void MainWindow::on_pushButton_17_clicked()
{
    //Если точка есть
    if(ui->lineEdit->text().contains('.')){
        return;
    }

    //Если поле пустое
    if(ui->lineEdit->text().isEmpty()){
        ui->lineEdit->setText("0.");
    }

    else{
        ui->lineEdit->setText(ui->lineEdit->text() + ".");
    }
}

///////////////////////////////////////////tg
void MainWindow::on_pushButton_19_clicked()
{
    double numbers = ui->lineEdit->text().toDouble();
    double result = tan(numbers);
    ui->lineEdit->setText(QString::number(result));
    ui->lineEdit_2->setText("tg(" + QString::number(numbers) + ") =");
}

///////////////////////////////////////////10^x
void MainWindow::on_pushButton_20_clicked()
{
    double numbers = ui->lineEdit->text().toDouble();
    double result = pow(10.0, numbers);
    ui->lineEdit->setText(QString::number(result));
    ui->lineEdit_2->setText("10^(" + QString::number(numbers) + ") =");
}

///////////////////////////////////////////x^3
void MainWindow::on_pushButton_21_clicked()
{
    double numbers = ui->lineEdit->text().toDouble();
    double result = numbers * numbers * numbers;
    ui->lineEdit->setText(QString::number(result));
    ui->lineEdit_2->setText("(" + QString::number(numbers) + ")^3 =");
}



///////////////////////////////////////////x!
void MainWindow::on_pushButton_22_clicked()
{
    double numbers = ui->lineEdit->text().toDouble();
    int n = (int)numbers;

    if(n < 0 || numbers != n){
        ui->lineEdit->setText("Error!");
        return;
    }

    double result = 1;
    for(int i = 2; i <=n; i++){
        result *= i;
    }

    ui->lineEdit->setText(QString::number(result, 'f', 0));
    ui->lineEdit_2->setText(QString::number(n) + "! = ");
}

