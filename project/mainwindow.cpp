#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentDocument(nullptr)
    , currentEditor(nullptr)
{
    ui->setupUi(this);

    setWindowTitle("Редактор документов (Factory Method Pattern)");
    resize(800, 600);
    centralWidget = ui->stackedWidget;

    //Сигналы от действий из ui файла
    connect(ui->actionNewText, &QAction::triggered, this, &MainWindow::onNewTextDocument);
    connect(ui->actionNewGraph, &QAction::triggered, this, &MainWindow::onNewGraphDocument);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::onOpen);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::onSave);
    connect(ui->actionSaveNew, &QAction::triggered, this, &MainWindow::onSaveNewName);
    connect(ui->actionPrint, &QAction::triggered, this, &MainWindow::onPrint);
    connect(ui->actionClose, &QAction::triggered, this, &MainWindow::onClose);
    connect(ui->actionExit, &QAction::triggered, this, &QMainWindow::close);

    //Cигналы от кнопок на панели инструментов
    connect(ui->actionNewTextTool, &QAction::triggered, this, &MainWindow::onNewTextDocument);
    connect(ui->actionNewGraphTool, &QAction::triggered, this, &MainWindow::onNewGraphDocument);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete currentDocument;
    delete currentEditor;
}

void MainWindow::updateDocument(Document* doc)
{
    if (currentDocument) {
        int index = centralWidget->indexOf(currentDocument->getWidget());
        if (index != -1) {
            centralWidget->removeWidget(currentDocument->getWidget());
        }
        delete currentDocument;
    }

    currentDocument = doc;

    if (doc) {
        centralWidget->addWidget(doc->getWidget());
        centralWidget->setCurrentWidget(doc->getWidget());
        QString title = QString("%1 - Документ (%2)")
                            .arg(currentEditor->getName())
                            .arg(doc->getType() == "text" ? "Текстовый" : "Графический");
        setWindowTitle(title);
    }
}

//Унаследованные классы
//Текстовый редактор
void MainWindow::onNewTextDocument()
{
    delete currentEditor;
    currentEditor = new TextEditor();
    Document* newDoc = currentEditor->createDoc();
    newDoc->create();
    updateDocument(newDoc);
}

//Графический редактор
void MainWindow::onNewGraphDocument()
{
    delete currentEditor;
    currentEditor = new GraphEditor();
    Document* newDoc = currentEditor->createDoc();
    newDoc->create();
    updateDocument(newDoc);
}

//Открыть
void MainWindow::onOpen()
{
    QMessageBox::StandardButton choice = QMessageBox::question(this, "Выбор типа",
                                                               "Какой документ вы хотите открыть?\n\n"
                                                               "Да - Текстовый документ (*.txt)\n"
                                                               "Нет - Графический документ (таблица *.csv)",
                                                               QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

    if (choice == QMessageBox::Cancel) return;

    if (choice == QMessageBox::Yes) {
        delete currentEditor;
        currentEditor = new TextEditor();
    } else {
        delete currentEditor;
        currentEditor = new GraphEditor();
    }

    Document* newDoc = currentEditor->createDoc();
    newDoc->open();
    updateDocument(newDoc);
}

//Сохранить
void MainWindow::onSave()
{
    if (currentDocument) {
        currentDocument->save();
    } else {
        QMessageBox::warning(this, "Нет документа", "Сначала создайте или откройте документ");
    }
}

//Сохранить как...
void MainWindow::onSaveNewName()
{
    if (currentDocument) {
        currentDocument->saveNewName();
    } else {
        QMessageBox::warning(this, "Нет документа", "Сначала создайте или откройте документ");
    }
}

//Печать
void MainWindow::onPrint()
{
    if (currentDocument) {
        currentDocument->print();
    } else {
        QMessageBox::warning(this, "Нет документа", "Сначала создайте или откройте документ");
    }
}

//Закрыть
void MainWindow::onClose()
{
    if (currentDocument) {
        currentDocument->close();
        updateDocument(nullptr);
        setWindowTitle("Редактор документов (Factory Method Pattern)");
    } else {
        QMessageBox::information(this, "Нет документа", "Нет открытого документа для закрытия");
    }
}
