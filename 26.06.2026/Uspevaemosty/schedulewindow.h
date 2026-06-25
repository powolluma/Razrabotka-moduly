#pragma once
#include <QWidget>
#include <QTableWidget>
#include <QPushButton>

class ScheduleWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ScheduleWindow(int userId, QWidget *parent = nullptr);

private slots:
    void showToday();
    void showWeek();

private:
    void setupUI();
    void loadSchedule(const QString &filter);
    QTableWidget *table;
    QPushButton *btnToday;
    QPushButton *btnWeek;
    int m_userId;
};