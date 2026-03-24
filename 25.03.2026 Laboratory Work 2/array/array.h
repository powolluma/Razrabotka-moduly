#ifndef ARRAY_H
#define ARRAY_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class array;
}
QT_END_NAMESPACE

class array : public QMainWindow
{
    Q_OBJECT
    //Экземпляр класса
    QVector <QVector <int> > matrix;
    //Количество
    int strCount;

public:
    array(QWidget *parent = nullptr);
    ~array();

private slots:
    void on_pushButton_clicked();

private:
    Ui::array *ui;
};
#endif // ARRAY_H
