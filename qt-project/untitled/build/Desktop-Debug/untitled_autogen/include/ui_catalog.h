/********************************************************************************
** Form generated from reading UI file 'catalog.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CATALOG_H
#define UI_CATALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName("Form");
        label = new QLabel(Form);
        label->setObjectName("label");
        label->setGeometry(QRect(270, 100, 141, 19));
        label_2 = new QLabel(Form);
        label_2->setObjectName("label_2");
        label_2->setEnabled(true);
        label_2->setGeometry(QRect(90, 20, 501, 511));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(10);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setBaseSize(QSize(100, 100));
        label_2->setToolTipDuration(-1);
        label_2->setFrameShape(QFrame::Shape::Box);
        label_2->setPixmap(QPixmap(QString::fromUtf8("123.png")));
        pushButton = new QPushButton(Form);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(280, 270, 131, 27));

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        label->setText(QCoreApplication::translate("Form", "\320\235\320\276\321\203\321\202\320\261\321\203\320\272 ThinkPad", nullptr));
        label_2->setText(QString());
        pushButton->setText(QCoreApplication::translate("Form", "\320\236\321\204\320\276\321\200\320\274\320\270\321\202\321\214 \320\267\320\260\320\272\320\260\320\267", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CATALOG_H
