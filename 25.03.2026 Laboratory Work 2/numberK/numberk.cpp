#include "numberk.h"
#include "./ui_numberk.h"
#include <QMessageBox>


numberK::numberK(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::numberK)
{
    ui->setupUi(this);

    //Размер матрицы
    m = 5;
    n = 4;

    //Матрица со случайными числами
    srand(time(0));
    for (int i = 0; i < m; i++) {
        QVector<int> line;
        for (int j = 0; j < n; j++) {
            line.append(rand() % 100 + 100);
        }
        matrix.append(line);
    }

    //Вывод матрицы
    QString str;
    for (int i = 0; i < matrix.length(); i++) {
        for (int j = 0; j < matrix[i].length(); j++) {
            str += QString::number(matrix[i][j]) + " ";
        }
        str += "\n";
    }
    ui->textEdit->setText(str);
}

numberK::~numberK()
{
    delete ui;
}

void numberK::on_pushButton_clicked()
{
    //Преобразование в число
    int k = ui->lineEdit->text().toInt();

    //Проверка диапазона
    if (k <= 0 || k >= 11) {
        QMessageBox::information(this, "Ошибка", "Номер столбца должен быть от 1 до 10!");
        return;
    }

    //Проверка наличия столбца
    if (k > n) {
        QMessageBox::information(this, "Ошибка", "Столбца с таким номером нет!");
        return;
    }

    //Индекс столбца
    int columnIndex = k - 1;

    //Выбор операции
    int operation = ui->comboBox->currentIndex();

    //Сумма
    if (operation == 0) {
        int sum = 0;
        for (int i = 0; i < matrix.length(); i++) {
            sum += matrix[i][columnIndex];
        }
        ui->textEdit->append("Сумма: " + QString::number(k) + ": " + QString::number(sum));
    }
    //Произведение
    else {
        int product = 1;
        for (int i = 0; i < matrix.length(); i++) {
            product *= matrix[i][columnIndex];
        }
        ui->textEdit->append("Произведение: " + QString::number(k) + ": " + QString::number(product));
    }

}






