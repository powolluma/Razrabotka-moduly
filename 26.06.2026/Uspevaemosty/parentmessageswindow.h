#pragma once
#include <QWidget>
#include <QTableWidget>

class ParentMessagesWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ParentMessagesWindow(int userId, QWidget *parent = nullptr);
private:
    void setupUI();
    void loadMessages();
    QTableWidget *table;
    int m_userId;
};