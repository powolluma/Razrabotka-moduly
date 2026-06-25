#include "gradeswindow.h"
#include "database.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QHeaderView>
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>
#include <QFont>
#include <QDebug>

GradesWindow::GradesWindow(int userId, QWidget *parent)
    : QWidget(parent), m_userId(userId)
{
    setWindowTitle("Оценки");
    setMinimumSize(700, 480);
    setupUI();
    showWeek(); // Оценки за неделю
}

// Создание окна
void GradesWindow::setupUI()
{
    setStyleSheet("QWidget { background-color: #E3F2FD; }");

    // Layout
    QVBoxLayout *main = new QVBoxLayout(this);
    main->setContentsMargins(24, 24, 24, 24);
    main->setSpacing(16);

    // Строка с текстом
    QLabel *title = new QLabel("5️⃣ Оценки");
    title->setStyleSheet("color: #1565C0; font-size: 20px; font-weight: bold;");
    main->addWidget(title);

    // Layout
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->setSpacing(10);
    // Кнопки
    btnToday = new QPushButton("Текущий день");
    btnWeek = new QPushButton("За неделю");

    // Стили кнопок
    QString btnStyle = R"(
    QPushButton {
        background-color: #1976D2;
        color: white;
        border-radius: 10px;
        font-size: 13px;
        padding: 8px 20px;
        border: none;
    }
    QPushButton:hover {
        background-color: #2196F3;
        color: white;
    }
    QPushButton:checked {
        background-color: #0D47A1;
        border: 2px solid white;
    })";


    btnToday->setStyleSheet(btnStyle);  //Применение стилей
    btnWeek->setStyleSheet(btnStyle);
    btnToday->setCheckable(true);   // Переключаемые кнопки
    btnWeek->setCheckable(true);
    btnWeek->setChecked(true);  // Значение кнопки по умолчанию

    // Кнопки в layout
    btnLayout->addWidget(btnToday);
    btnLayout->addWidget(btnWeek);
    btnLayout->addStretch();
    main->addLayout(btnLayout);

    // Таблица
    table = new QTableWidget();
    table->setColumnCount(4);
    table->setHorizontalHeaderLabels({"Предмет", "Оценка", "Дата", "Четверть"});
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setAlternatingRowColors(true);
    table->verticalHeader()->setVisible(false);

    // Стили таблицы
    table->setStyleSheet(R"(
    QTableWidget {
        background-color: white;
        border-radius: 12px;
        selection-background-color: transparent;
        selection-color: black;
    }
    QHeaderView::section {
        background-color: #1976D2;
        color: white;
        font-weight: bold;
    }
    QTableWidget::item {
        color: black;
    }
    QTableWidget::item:selected {
        background-color: transparent;
    }
)");
    main->addWidget(table);
    // Сигналы кнопок
    connect(btnToday, &QPushButton::clicked, this, &GradesWindow::showToday);
    connect(btnWeek, &QPushButton::clicked, this, &GradesWindow::showWeek);
}

// "За сегодня"
void GradesWindow::showToday()
{
    btnToday->setChecked(true);
    btnWeek->setChecked(false);
    loadGrades("today");
}

// "За неделю"
void GradesWindow::showWeek()
{
    btnWeek->setChecked(true);
    btnToday->setChecked(false);
    loadGrades("week");
}

// Загрузка оценок
void GradesWindow::loadGrades(const QString &filter)
{
    table->setRowCount(0);

    // Фильтры для запроса
    QString dateFilter = (filter == "today")
                             ? "AND g.date = :currentDate"
                             : "AND g.date >= :fromDate";

    // Запрос в sql с параметрами
    QSqlQuery q(Database::getDB());
    q.prepare(QString(R"(
        SELECT s.name, g.grade, g.date, g.quarter
        FROM grades g
        JOIN subjects s ON s.id = g.subject_id
        JOIN students st ON st.id = g.student_id
        WHERE st.user_id = :userId %1
        ORDER BY g.date DESC, g.quarter DESC
    )").arg(dateFilter));
    q.bindValue(":userId", m_userId); // Привязывание userid

    //Условия для поика по фильтру
    QString usedDate;
    if (filter == "today") {
        usedDate = QDate::currentDate().toString("yyyy-MM-dd");
        q.bindValue(":currentDate", usedDate);
    } else {
        QDate from = QDate::currentDate().addDays(-7);
        usedDate = from.toString("yyyy-MM-dd");
        q.bindValue(":fromDate", usedDate);
    }

    // Проверка ошибки
    if (!q.exec()) {
        return;
    }

    // Перебор записей
    int row = 0;
    while (q.next()) {
        table->insertRow(row);  // Новая строка

        QString subject = q.value(0).toString();
        int grade       = q.value(1).toInt();
        QString date    = q.value(2).toString();
        int quarter     = q.value(3).toInt();

        auto *itemSubj  = new QTableWidgetItem(subject);
        auto *itemGrade = new QTableWidgetItem(QString::number(grade));
        auto *itemDate  = new QTableWidgetItem(date);
        auto *itemQ     = new QTableWidgetItem(QString::number(quarter));

        // Центрирование
        itemSubj->setTextAlignment(Qt::AlignCenter);
        itemGrade->setTextAlignment(Qt::AlignCenter);
        itemDate->setTextAlignment(Qt::AlignCenter);
        itemQ->setTextAlignment(Qt::AlignCenter);

        // Шрифт
        QFont f; f.setBold(true);
        itemGrade->setFont(f);

        // Добавление строк
        table->setItem(row, 0, itemSubj);
        table->setItem(row, 1, itemGrade);
        table->setItem(row, 2, itemDate);
        table->setItem(row, 3, itemQ);

        row++;
    }

    // Проверка на пустые строки
    if (row == 0) {
        table->insertRow(0);
        auto *empty = new QTableWidgetItem("❗️ Нет оценок за этот период");
        empty->setTextAlignment(Qt::AlignCenter);
        empty->setForeground(QColor("#9E9E9E"));
        table->setSpan(0, 0, 1, 4);
        table->setItem(0, 0, empty);
    }
}