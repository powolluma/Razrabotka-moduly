#pragma once
#include <QWidget>
#include <QTableWidget>
#include <QPushButton>

class GradesWindow : public QWidget
{
    Q_OBJECT
public:
    explicit GradesWindow(int userId, QWidget *parent = nullptr);

private slots:
    void showToday();
    void showWeek();

private:
    void setupUI();
    void loadGrades(const QString &filter);
    QTableWidget *table;
    QPushButton *btnToday;
    QPushButton *btnWeek;
    int m_userId;
};