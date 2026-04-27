/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNewText;
    QAction *actionNewGraph;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSaveNew;
    QAction *actionPrint;
    QAction *actionClose;
    QAction *actionExit;
    QAction *actionNewTextTool;
    QAction *actionNewGraphTool;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuCreate;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        actionNewText = new QAction(MainWindow);
        actionNewText->setObjectName("actionNewText");
        actionNewGraph = new QAction(MainWindow);
        actionNewGraph->setObjectName("actionNewGraph");
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName("actionOpen");
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName("actionSave");
        actionSaveNew = new QAction(MainWindow);
        actionSaveNew->setObjectName("actionSaveNew");
        actionPrint = new QAction(MainWindow);
        actionPrint->setObjectName("actionPrint");
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName("actionClose");
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName("actionExit");
        actionNewTextTool = new QAction(MainWindow);
        actionNewTextTool->setObjectName("actionNewTextTool");
        actionNewGraphTool = new QAction(MainWindow);
        actionNewGraphTool->setObjectName("actionNewGraphTool");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");

        verticalLayout->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 24));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        menuCreate = new QMenu(menuFile);
        menuCreate->setObjectName("menuCreate");
        MainWindow->setMenuBar(menubar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(menuCreate->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSaveNew);
        menuFile->addSeparator();
        menuFile->addAction(actionPrint);
        menuFile->addSeparator();
        menuFile->addAction(actionClose);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuCreate->addAction(actionNewText);
        menuCreate->addAction(actionNewGraph);
        toolBar->addAction(actionNewTextTool);
        toolBar->addAction(actionNewGraphTool);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\264\320\260\320\272\321\202\320\276\321\200 \320\264\320\276\320\272\321\203\320\274\320\265\320\275\321\202\320\276\320\262 (Factory Method Pattern)", nullptr));
        actionNewText->setText(QCoreApplication::translate("MainWindow", "\320\242\320\265\320\272\321\201\321\202\320\276\320\262\321\213\320\271 \320\264\320\276\320\272\321\203\320\274\320\265\320\275\321\202", nullptr));
        actionNewGraph->setText(QCoreApplication::translate("MainWindow", "\320\223\321\200\320\260\321\204\320\270\321\207\320\265\321\201\320\272\320\270\320\271 \320\264\320\276\320\272\321\203\320\274\320\265\320\275\321\202 (\321\202\320\260\320\261\320\273\320\270\321\206\320\260)", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", nullptr));
        actionSave->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        actionSaveNew->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\272\320\260\320\272...", nullptr));
        actionPrint->setText(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\207\320\260\321\202\321\214", nullptr));
        actionClose->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264", nullptr));
        actionNewTextTool->setText(QCoreApplication::translate("MainWindow", "\320\235\320\276\320\262\321\213\320\271 \321\202\320\265\320\272\321\201\321\202", nullptr));
        actionNewGraphTool->setText(QCoreApplication::translate("MainWindow", "\320\235\320\276\320\262\320\260\321\217 \321\202\320\260\320\261\320\273\320\270\321\206\320\260", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273", nullptr));
        menuCreate->setTitle(QCoreApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
