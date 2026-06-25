#pragma once
#include <QWidget>
#include <QTableWidget>
#include <QComboBox>

class QuarterGradesWindow : public QWidget
{
    Q_OBJECT
public:
    explicit QuarterGradesWindow(int userId, QWidget *parent = nullptr);

private slots:
    void onQuarterChanged(int index);

private:
    void setupUI();
    void loadGrades(int quarter);
    QTableWidget *table;
    QComboBox *quarterCombo;
    int m_userId;
};