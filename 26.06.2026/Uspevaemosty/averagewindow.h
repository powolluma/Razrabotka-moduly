#pragma once
#include <QWidget>
#include <QListWidget>
#include <QLabel>

class AverageWindow : public QWidget
{
    Q_OBJECT
public:
    explicit AverageWindow(int userId, QWidget *parent = nullptr);

private slots:
    void onSubjectSelected(int row);

private:
    void setupUI();
    void loadSubjects();
    QListWidget *subjectList;
    QLabel *avgLabel;
    QLabel *detailLabel;
    int m_userId;
};