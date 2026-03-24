/********************************************************************************
** Form generated from reading UI file 'array.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ARRAY_H
#define UI_ARRAY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_array
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QTextEdit *textEdit;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *array)
    {
        if (array->objectName().isEmpty())
            array->setObjectName("array");
        array->resize(800, 600);
        centralwidget = new QWidget(array);
        centralwidget->setObjectName("centralwidget");
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(260, 130, 258, 256));
        verticalLayout_3 = new QVBoxLayout(widget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(label);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");

        verticalLayout_2->addLayout(verticalLayout);


        verticalLayout_3->addLayout(verticalLayout_2);

        textEdit = new QTextEdit(widget);
        textEdit->setObjectName("textEdit");

        verticalLayout_3->addWidget(textEdit);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName("pushButton");

        verticalLayout_3->addWidget(pushButton);

        array->setCentralWidget(centralwidget);
        menubar = new QMenuBar(array);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        array->setMenuBar(menubar);
        statusbar = new QStatusBar(array);
        statusbar->setObjectName("statusbar");
        array->setStatusBar(statusbar);

        retranslateUi(array);

        QMetaObject::connectSlotsByName(array);
    } // setupUi

    void retranslateUi(QMainWindow *array)
    {
        array->setWindowTitle(QCoreApplication::translate("array", "array", nullptr));
        label->setText(QCoreApplication::translate("array", "\320\222\321\213\320\262\320\276\320\264 \320\274\320\260\321\201\321\201\320\270\320\262\320\260 \320\262 \320\276\320\261\321\200\320\260\321\202\320\275\320\276\320\274 \320\277\320\276\321\200\321\217\320\264\320\272\320\265", nullptr));
        pushButton->setText(QCoreApplication::translate("array", "\320\222\321\213\320\262\320\276\320\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class array: public Ui_array {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ARRAY_H
