#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QButtonGroup>

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);

private slots:
    void onLoginClicked();
    void onForgotPasswordClicked();
    void onRoleButtonClicked(int id);

private:
    void setupUI();
    void applyStyles();

    QLineEdit *loginEdit;
    QLineEdit *passwordEdit;
    QPushButton *loginButton;
    QPushButton *forgotButton;
    QPushButton *btnStudent;
    QPushButton *btnParent;
    QPushButton *btnTeacher;
    QButtonGroup *roleGroup;

    int currentRole; // 0=Student, 1=Parent, 2=Teacher
};