#ifndef NUMBERK_H
#define NUMBERK_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class numberK;
}
QT_END_NAMESPACE

class numberK : public QMainWindow
{
    Q_OBJECT

public:
    numberK(QWidget *parent = nullptr);
    ~numberK();

private slots:
    void on_pushButton_clicked();

private:
    Ui::numberK *ui;
    //Двухмерный массив
    QVector <QVector <int> > matrix;
    int m; //Строки
    int n; //Столбцы
};
#endif // NUMBERK_H
