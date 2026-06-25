#include <QApplication>
#include <QFont>
#include "loginwindow.h"
#include "database.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Применение шрифта
    //QFont font("Arial", 10);
    //a.setFont(font);

    //Инициализация базы данных
    Database::instance().init();

    //Запуск окна для входа
    LoginWindow w;
    w.show();

    return a.exec();
}