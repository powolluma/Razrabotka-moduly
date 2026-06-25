#pragma once

#include <QWidget>

class ForgotPasswordWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ForgotPasswordWindow(QWidget *parent = nullptr);

private:
    void setupUI();
};