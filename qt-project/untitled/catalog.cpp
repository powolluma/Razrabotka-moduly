#include "catalog.h"
#include "ui_catalog.h"

Catalog::Catalog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Catalog)
{
    ui->setupUi(this);
}

Catalog::~Catalog()
{
    delete ui;
}

void Catalog::on_btnOrder_clicked()
{
    this->close();  // просто закрываем каталог, возвращаемся на главную
}