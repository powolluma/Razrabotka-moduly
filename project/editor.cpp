#include "editor.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QGridLayout>
#include <QHeaderView>

//Текстовый документ
TextDocument::TextDocument(QWidget* parent) : Document(parent)
{
    textEdit = new QTextEdit(this);
    textEdit->setPlaceholderText("Введите текст...");
    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(textEdit, 0, 0);
    setLayout(layout);
}

//Создать
void TextDocument::create()
{
    textEdit->clear();
    currentFile = "";
    name = "Новый документ";
    qDebug() << "Создан новый текстовый документ";
}

//Открыть
void TextDocument::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть текстовый файл",
                                                    "", "Текстовые файлы (*.txt);;Все файлы (*.*)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл");
        return;
    }

    QTextStream in(&file);
    textEdit->setPlainText(in.readAll());
    file.close();

    currentFile = fileName;
    name = QFileInfo(fileName).fileName();
    qDebug() << "Открыт файл:" << fileName;
}

//Сохранить
void TextDocument::save()
{
    if (currentFile.isEmpty()) {
        saveNewName();
    } else {
        QFile file(currentFile);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Ошибка", "Не удалось сохранить файл");
            return;
        }
        QTextStream out(&file);
        out << textEdit->toPlainText();
        file.close();
        qDebug() << "Сохранен файл:" << currentFile;
    }
}

//Сохранить с новым именем
void TextDocument::saveNewName()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить файл",
                                                    "", "Текстовые файлы (*.txt);;Все файлы (*.*)");
    if (fileName.isEmpty()) return;

    currentFile = fileName;
    save();
}

//Печать
void TextDocument::print()
{
    QMessageBox::information(this, "Печать", "Документ отправлен на печать");
}

//Закрыть
void TextDocument::close()
{
    textEdit->clear();
    currentFile = "";
    qDebug() << "Документ закрыт";
}

//
void TextDocument::setContent(const QString& content)
{
    textEdit->setPlainText(content);
}

QString TextDocument::getContent()
{
    return textEdit->toPlainText();
}

//Графический документ
GraphDocument::GraphDocument(QWidget* parent) : Document(parent)
{
    tableWidget = new QTableWidget(5, 3, this);
    QStringList headers;
    headers << "1" << "2" << "3";
    tableWidget->setHorizontalHeaderLabels(headers);

    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(tableWidget, 0, 0);
    setLayout(layout);
}

//Создать
void GraphDocument::create()
{
    tableWidget->clearContents();
    tableWidget->setRowCount(5);
    currentFile = "";
    name = "Новая таблица";
    qDebug() << "Создана новая графическая таблица";
}

//Открыть
void GraphDocument::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть таблицу",
                                                    "", "CSV файлы (*.csv);;Все файлы (*.*)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл");
        return;
    }

    QTextStream in(&file);
    int row = 0;
    while (!in.atEnd() && row < 100) {
        QString line = in.readLine();
        QStringList cells = line.split(',');

        if (row >= tableWidget->rowCount()) {
            tableWidget->setRowCount(row + 1);
        }

        for (int col = 0; col < cells.size() && col < tableWidget->columnCount(); col++) {
            QTableWidgetItem* item = new QTableWidgetItem(cells[col]);
            tableWidget->setItem(row, col, item);
        }
        row++;
    }
    file.close();

    currentFile = fileName;
    name = QFileInfo(fileName).fileName();
    qDebug() << "Открыт файл таблицы:" << fileName;
}

//Сохранить
void GraphDocument::save()
{
    if (currentFile.isEmpty()) {
        saveNewName();
    } else {
        QFile file(currentFile);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Ошибка", "Не удалось сохранить файл");
            return;
        }

        QTextStream out(&file);
        for (int row = 0; row < tableWidget->rowCount(); row++) {
            QStringList rowData;
            for (int col = 0; col < tableWidget->columnCount(); col++) {
                QTableWidgetItem* item = tableWidget->item(row, col);
                rowData << (item ? item->text() : "");
            }
            out << rowData.join(",") << "\n";
        }
        file.close();
        qDebug() << "Сохранен файл таблицы:" << currentFile;
    }
}

//Сохранить с новым именем
void GraphDocument::saveNewName()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить таблицу",
                                                    "", "CSV файлы (*.csv);;Все файлы (*.*)");
    if (fileName.isEmpty()) return;

    currentFile = fileName;
    save();
}

//Печать
void GraphDocument::print()
{
    QMessageBox::information(this, "Печать", "Таблица отправлена на печать");
}

//Закрыть
void GraphDocument::close()
{
    tableWidget->clearContents();
    tableWidget->setRowCount(5);
    currentFile = "";
    qDebug() << "Таблица закрыта";
}

QString GraphDocument::getData()
{
    QStringList allData;
    for (int row = 0; row < tableWidget->rowCount(); row++) {
        QStringList rowData;
        for (int col = 0; col < tableWidget->columnCount(); col++) {
            QTableWidgetItem* item = tableWidget->item(row, col);
            rowData << (item ? item->text() : "");
        }
        allData << rowData.join(",");
    }
    return allData.join("\n");
}

//Текстовый редактор
Document* TextEditor::createDoc()
{
    return new TextDocument();
}

//Графический редактор
Document* GraphEditor::createDoc()
{
    return new GraphDocument();
}
