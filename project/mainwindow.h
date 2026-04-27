#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "editor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow* ui;
    QStackedWidget* centralWidget;
    Document* currentDocument;
    Editor* currentEditor;

    void updateDocument(Document* doc);

private slots:
    void onNewTextDocument();      //Унаследованные классы - Текстовый редактор
    void onNewGraphDocument();     //Унаследованные классы - Графический редактор
    void onOpen();                 //Открыть
    void onSave();                 //Сохранить
    void onSaveNewName();          //Сохранить как...
    void onPrint();                //Печать
    void onClose();                //Закрыть

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
};

#endif // MAINWINDOW_H
