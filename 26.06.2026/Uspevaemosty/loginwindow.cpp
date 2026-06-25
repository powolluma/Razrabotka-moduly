#include "loginwindow.h"
#include "forgotpasswordwindow.h"
#include "studentmainwindow.h"
#include "parentmainwindow.h"
#include "teachermainwindow.h"
#include "database.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

// Конструктор
LoginWindow::LoginWindow(QWidget *parent)
    : QWidget(parent), currentRole(0)
{
    setWindowTitle("Успеваемость — Вход");
    setFixedSize(480, 620);
    setupUI();
    applyStyles();
}

// Создание окна
void LoginWindow::setupUI()
{
    // Layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(40, 40, 40, 40);
    mainLayout->setSpacing(16);

    // Заголовок
    QLabel *titleLabel = new QLabel("👨🏻‍💻 Добро пожаловать в Журнал!");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setObjectName("titleLabel");
    mainLayout->addWidget(titleLabel);
    mainLayout->addSpacing(10);

    // Поля ввода
    loginEdit = new QLineEdit();
    loginEdit->setPlaceholderText("Логин:");
    loginEdit->setObjectName("inputField");
    loginEdit->setFixedHeight(42);
    mainLayout->addWidget(loginEdit);

    passwordEdit = new QLineEdit();
    passwordEdit->setPlaceholderText("Пароль:");
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setObjectName("inputField");
    passwordEdit->setFixedHeight(42);
    mainLayout->addWidget(passwordEdit);

    mainLayout->addSpacing(8);

    // Кнопка Войти
    loginButton = new QPushButton("Войти");
    loginButton->setObjectName("loginButton");
    loginButton->setFixedSize(160, 44);
    loginButton->setCursor(Qt::PointingHandCursor);
    mainLayout->addWidget(loginButton, 0, Qt::AlignCenter);
    mainLayout->addSpacing(16);

    // Выбор роли
    QHBoxLayout *roleLayout = new QHBoxLayout();
    roleLayout->setSpacing(12);

    // Кнопки ролей
    btnStudent = new QPushButton("Ученик");
    btnParent = new QPushButton("Родитель");
    btnTeacher = new QPushButton("Учитель");
    btnStudent->setObjectName("roleButton");
    btnParent->setObjectName("roleButton");
    btnTeacher->setObjectName("roleButton");

    // Возможность нажатия
    btnStudent->setCheckable(true);
    btnParent->setCheckable(true);
    btnTeacher->setCheckable(true);
    btnStudent->setChecked(true);

    // Применение ролей
    roleGroup = new QButtonGroup(this);
    roleGroup->addButton(btnStudent, 0);
    roleGroup->addButton(btnParent, 1);
    roleGroup->addButton(btnTeacher, 2);
    roleGroup->setExclusive(true);
    roleLayout->addWidget(btnStudent);
    roleLayout->addWidget(btnParent);
    roleLayout->addWidget(btnTeacher);
    mainLayout->addLayout(roleLayout);
    mainLayout->addSpacing(8);

    // Кнопка забыли пароль
    forgotButton = new QPushButton("Забыли пароль?");
    forgotButton->setObjectName("forgotButton");
    forgotButton->setCursor(Qt::PointingHandCursor);
    forgotButton->setFixedSize(180, 40);
    mainLayout->addWidget(forgotButton, 0, Qt::AlignCenter);
    mainLayout->addStretch();

    // Подключение сигналов
    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::onLoginClicked);
    connect(forgotButton, &QPushButton::clicked, this, &LoginWindow::onForgotPasswordClicked);
    connect(roleGroup, &QButtonGroup::idClicked, this, &LoginWindow::onRoleButtonClicked);
}

// Применение стилей
void LoginWindow::applyStyles()
{
    setStyleSheet(R"(
        QWidget { background-color: #2196F3; }
        QLabel#titleLabel {
            color: white;
            font-size: 20px;
            font-weight: bold;
        }
        QLineEdit#inputField {
            background-color: #1565C0;
            color: white;
            border: 2px solid #42A5F5;
            border-radius: 10px;
            padding: 4px 12px;
            font-size: 14px;
        }
        QLineEdit#inputField::placeholder {
            color: #90CAF9;
        }
        QPushButton#loginButton {
            background-color: #1976D2;
            color: white;
            border-radius: 12px;
            font-size: 15px;
            font-weight: bold;
        }
        QPushButton#loginButton:hover { background-color: #1565C0; }
        QPushButton#loginButton:pressed { background-color: #0D47A1; }
        QPushButton#roleButton {
            background-color: #1976D2;
            color: white;
            border-radius: 14px;
            padding: 8px 18px;
        }
        QPushButton#roleButton:checked {
            border: 2px solid white;
            background-color: #0D47A1;
        }
        QPushButton#forgotButton {
            background-color: #1976D2;
            color: white;
            border-radius: 12px;
            font-size: 13px;
        }
        QPushButton#forgotButton:hover { background-color: #1565C0; }
    )");
}

// === Обработка кнопок ===
// Кнопка Войти
void LoginWindow::onLoginClicked()
{
    QString login = loginEdit->text().trimmed();
    QString pass = passwordEdit->text();

    if (login.isEmpty() || pass.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите логин и пароль!");
        return;
    }

    QSqlQuery q(Database::getDB());

    q.prepare("SELECT id, full_name, role FROM users WHERE login = :login AND password = :pass");
    q.bindValue(":login", login);
    q.bindValue(":pass", pass);

    if (q.exec()) {
        if (q.next()) {
            int userId = q.value(0).toInt();
            QString name = q.value(1).toString();
            int role = q.value(2).toInt();

            // Проверка совпадения роли
            if (role != currentRole) {
                QString correctRoleName;
                switch (role) {
                case 0: correctRoleName = "Ученик"; break;
                case 1: correctRoleName = "Родитель"; break;
                case 2: correctRoleName = "Учитель"; break;
                default: correctRoleName = "Неизвестная роль"; break;
                }
                QMessageBox::warning(this, "Ошибка входа",
                                     QString("Выберите правильную роль и попробуйте снова.")
                                         .arg(correctRoleName));
                return;
            }

            QWidget *mainWin = nullptr;

            if (currentRole == 2) {
                TeacherMainWindow *w = new TeacherMainWindow();
                w->setUserId(userId);
                w->setTeacherName(name);
                mainWin = w;
            } else if (currentRole == 1) {
                ParentMainWindow *w = new ParentMainWindow();
                w->setUserId(userId);
                w->setParentName(name);
                mainWin = w;
            } else {
                StudentMainWindow *w = new StudentMainWindow();
                w->setUserId(userId);
                w->setStudentName(name);
                mainWin = w;
            }

            if (mainWin) {
                mainWin->show();
                this->close();
            }
        } else {
            QMessageBox::warning(this, "Ошибка входа", "Неверный логин или пароль!");
        }
    } else {
        QMessageBox::warning(this, "Ошибка", "Ошибка базы данных");
    }
}

// Кнопка Забыли Пароль
void LoginWindow::onForgotPasswordClicked()
{
    ForgotPasswordWindow *w = new ForgotPasswordWindow(this);
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
}

// Кнопки ролей
void LoginWindow::onRoleButtonClicked(int id)
{
    currentRole = id;
}