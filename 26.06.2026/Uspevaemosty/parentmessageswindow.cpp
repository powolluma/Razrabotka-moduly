#include "parentmessageswindow.h"
#include "database.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QHeaderView>
#include <QSqlQuery>
#include <QSqlError>
#include <QTableWidget>
#include <QColor>
#include <QDebug>

// Конструктор
ParentMessagesWindow::ParentMessagesWindow(int userId, QWidget *parent)
    : QWidget(parent), m_userId(userId)
{
    setWindowTitle("Сообщения");
    setMinimumSize(700, 480);
    setupUI();
    loadMessages(); // Загрузка сообщений
}

// Создание окна
void ParentMessagesWindow::setupUI()
{
    setStyleSheet("QWidget { background-color: #E3F2FD; }");
    QVBoxLayout *main = new QVBoxLayout(this);
    main->setContentsMargins(24, 24, 24, 24);
    main->setSpacing(16);

    // Заголовок окна
    QLabel *title = new QLabel("💬 Сообщения");
    title->setStyleSheet("color: #1565C0; font-size: 20px; font-weight: bold; font-family: Arial;");
    main->addWidget(title);

    // Таблица сообщений
    table = new QTableWidget();
    table->setColumnCount(3);
    table->setHorizontalHeaderLabels({"От кого", "Сообщение", "Дата"});
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);     // Запрет редактирования
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setAlternatingRowColors(true);
    table->verticalHeader()->setVisible(false);

    // Стили таблицы
    table->setStyleSheet(R"(
        QTableWidget {
            background-color: white;
            border-radius: 12px;
            border: none;
            font-size: 13px;
        }
        QHeaderView::section {
            background-color: #1976D2;
            color: white;
            font-weight: bold;
            padding: 8px;
        }
        QTableWidget::item {
            color: black;
        }
        QTableWidget::item:selected {
            background-color: #BBDEFB;
            color: black;
        }
    )");
    main->addWidget(table);
}

// Загрузка всех сообщений для текущего родителя
void ParentMessagesWindow::loadMessages()
{
    table->setRowCount(0);
    QSqlQuery q(Database::getDB());
    q.prepare(R"(
        SELECT u.full_name, m.text, m.date
        FROM messages m
        JOIN users u ON u.id = m.from_user_id
        WHERE m.to_user_id = ?
        ORDER BY m.date DESC
    )");
    q.addBindValue(m_userId);

    if (!q.exec()) {
        qDebug() << "Ошибка загрузки сообщений:" << q.lastError().text();
        return;
    }

    int row = 0;
    while (q.next()) {
        table->insertRow(row);
        auto *itemFrom = new QTableWidgetItem(q.value(0).toString());  // От кого
        auto *itemText = new QTableWidgetItem(q.value(1).toString());  // Текст сообщения
        auto *itemDate = new QTableWidgetItem(q.value(2).toString());  // Дата
        itemFrom->setTextAlignment(Qt::AlignCenter);
        itemText->setTextAlignment(Qt::AlignCenter);
        itemDate->setTextAlignment(Qt::AlignCenter);
        table->setItem(row, 0, itemFrom);
        table->setItem(row, 1, itemText);
        table->setItem(row, 2, itemDate);
        row++;
    }
    // Проверка на наличие сообщений
    if (row == 0) {
        table->insertRow(0);
        auto *empty = new QTableWidgetItem("Нет сообщений");
        empty->setTextAlignment(Qt::AlignCenter);
        empty->setForeground(QColor("#9E9E9E"));
        table->setSpan(0, 0, 1, 3);
        table->setItem(0, 0, empty);
    }
}