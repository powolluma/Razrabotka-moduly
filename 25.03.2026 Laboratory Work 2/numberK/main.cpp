#include "numberk.h"
#include <QMessageBox>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    numberK w;
    w.show();
    return a.exec();
}
