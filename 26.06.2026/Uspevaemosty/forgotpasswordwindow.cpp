#include "forgotpasswordwindow.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

//Конструктор
ForgotPasswordWindow::ForgotPasswordWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Восстановление пароля");
    setFixedSize(420, 300);

    // Диалоговое окно
    setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
    setAttribute(Qt::WA_TranslucentBackground, false);
    setAutoFillBackground(true);
    setupUI();
}

// Создание окна
void ForgotPasswordWindow::setupUI()
{
    // Вертикальный layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(40, 40, 40, 40);
    layout->setSpacing(20);

    // Строка с лого
    QLabel *iconLabel = new QLabel("☎️");
    iconLabel->setAlignment(Qt::AlignCenter);
    iconLabel->setStyleSheet("font-size: 48px; background: transparent;");
    layout->addWidget(iconLabel);

    // Информационный текст
    QLabel *textLabel = new QLabel(
        "Для восстановления пароля\n"
        "обратитесь в учебную часть:\n\n"
        "+7 (999) 123-45-67"
        );
    textLabel->setAlignment(Qt::AlignCenter);
    textLabel->setObjectName("infoLabel");
    layout->addWidget(textLabel);

    // Кнопка закрытия
    QPushButton *closeBtn = new QPushButton("Закрыть");
    closeBtn->setObjectName("closeButton");
    closeBtn->setFixedSize(140, 40);
    closeBtn->setCursor(Qt::PointingHandCursor);
    layout->addWidget(closeBtn, 0, Qt::AlignCenter);

    // Подключение закрытия окна по кнопке
    connect(closeBtn, &QPushButton::clicked, this, &ForgotPasswordWindow::close);

    // Стили окна
    setStyleSheet(R"(
        QWidget {
            background-color: white;
        }
        QLabel#infoLabel {
            color: #1565C0;
            font-size: 16px;
            font-family: Arial;
            font-weight: bold;
        }
        QPushButton#closeButton {
            background-color: #2196F3;
            color: white;
            border-radius: 12px;
            font-size: 14px;
            font-family: Arial;
            border: none;
        }
        QPushButton#closeButton:hover {
            background-color: #1565C0;
        }
    )");
}