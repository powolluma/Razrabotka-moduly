/********************************************************************************
** Form generated from reading UI file 'numberk.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NUMBERK_H
#define UI_NUMBERK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_numberK
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout_3;
    QTextEdit *textEdit;
    QVBoxLayout *verticalLayout_2;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit;
    QLabel *label;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *numberK)
    {
        if (numberK->objectName().isEmpty())
            numberK->setObjectName("numberK");
        numberK->resize(800, 600);
        centralwidget = new QWidget(numberK);
        centralwidget->setObjectName("centralwidget");
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(260, 130, 258, 282));
        verticalLayout_3 = new QVBoxLayout(widget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        textEdit = new QTextEdit(widget);
        textEdit->setObjectName("textEdit");

        verticalLayout_3->addWidget(textEdit);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        comboBox = new QComboBox(widget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");

        verticalLayout_2->addWidget(comboBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName("lineEdit");

        verticalLayout->addWidget(lineEdit);

        label = new QLabel(widget);
        label->setObjectName("label");

        verticalLayout->addWidget(label);


        horizontalLayout->addLayout(verticalLayout);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName("pushButton");

        horizontalLayout->addWidget(pushButton);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout_3->addLayout(verticalLayout_2);

        numberK->setCentralWidget(centralwidget);
        menubar = new QMenuBar(numberK);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        numberK->setMenuBar(menubar);
        statusbar = new QStatusBar(numberK);
        statusbar->setObjectName("statusbar");
        numberK->setStatusBar(statusbar);

        retranslateUi(numberK);

        QMetaObject::connectSlotsByName(numberK);
    } // setupUi

    void retranslateUi(QMainWindow *numberK)
    {
        numberK->setWindowTitle(QCoreApplication::translate("numberK", "numberK", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("numberK", "\320\241\321\203\320\274\320\274\320\260", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("numberK", "\320\237\321\200\320\276\320\270\320\267\320\262\320\265\320\264\320\265\320\275\320\270\320\265", nullptr));

        label->setText(QCoreApplication::translate("numberK", "\320\237\320\276\320\273\320\265 \320\264\320\273\321\217 \320\262\320\262\320\276\320\264\320\260", nullptr));
        pushButton->setText(QCoreApplication::translate("numberK", "\320\227\320\260\320\277\321\203\321\201\320\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class numberK: public Ui_numberK {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NUMBERK_H
