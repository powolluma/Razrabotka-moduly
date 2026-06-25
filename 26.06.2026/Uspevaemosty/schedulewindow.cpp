#include "schedulewindow.h"
#include "database.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QHeaderView>
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>
#include <QColor>
#include <QDebug>

// Конструктор
ScheduleWindow::ScheduleWindow(int userId, QWidget *parent)
    : QWidget(parent), m_userId(userId)
{
    setWindowTitle("Расписание");
    setMinimumSize(700, 480);
    setupUI();
    showToday();    // Расписание на сегодня
}

// Создание окна
void ScheduleWindow::setupUI()
{
    setStyleSheet("QWidget { background-color: #E3F2FD; }");

    // Layout
    QVBoxLayout *main = new QVBoxLayout(this);
    main->setContentsMargins(24, 24, 24, 24);
    main->setSpacing(16);

    // Заголовок
    QLabel *title = new QLabel("🪧 Расписание");
    title->setStyleSheet("color: #1565C0; font-size: 20px; font-weight: bold;");
    main->addWidget(title);

    // Кнопки переключения (Сегодня / За неделю)
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->setSpacing(10);

    btnToday = new QPushButton("Текущий день");
    btnWeek = new QPushButton("За неделю");

    QString btnStyle = R"(
        QPushButton {
            background-color: #1976D2;
            color: white;
            border-radius: 10px;
            font-size: 13px;
            padding: 8px 20px;
            border: none;
        }
        QPushButton:hover { background-color: #2196F3; }
        QPushButton:checked { background-color: #0D47A1; border: 2px solid white; }
    )";

    btnToday->setStyleSheet(btnStyle);
    btnWeek->setStyleSheet(btnStyle);
    btnToday->setCheckable(true);
    btnWeek->setCheckable(true);
    btnToday->setChecked(true);

    btnLayout->addWidget(btnToday);
    btnLayout->addWidget(btnWeek);
    btnLayout->addStretch();
    main->addLayout(btnLayout);

    // Таблица расписания
    table = new QTableWidget();
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setAlternatingRowColors(true);
    table->verticalHeader()->setVisible(false);

    // Стили таблицы
    table->setStyleSheet(R"(
    QTableWidget {
        background-color: white;
        border-radius: 12px;
    }
    QHeaderView::section {
        background-color: #1976D2;
        color: white;
        font-weight: bold;
    }
    QTableWidget::item {
        color: black;                    /* ← Главное: чёрный текст */
        padding: 6px;
    }
    QTableWidget::item:selected {
        background-color: #BBDEFB;       /* можно оставить или убрать */
        color: black;                    /* чёрный текст при выделении */
    }
)");

    main->addWidget(table);

    // Подключение кнопок
    connect(btnToday, &QPushButton::clicked, this, &ScheduleWindow::showToday);
    connect(btnWeek, &QPushButton::clicked, this, &ScheduleWindow::showWeek);
}

// Кнопка На сегодня
void ScheduleWindow::showToday()
{
    btnToday->setChecked(true);
    btnWeek->setChecked(false);
    loadSchedule("today");
}

// Кнопка На неделю
void ScheduleWindow::showWeek()
{
    btnWeek->setChecked(true);
    btnToday->setChecked(false);
    loadSchedule("week");
}

// Загрузка расписания
void ScheduleWindow::loadSchedule(const QString &filter)
{
    table->clear();
    table->setRowCount(0);

    static const QStringList dayNames =
        {
            "",
            "Понедельник",
            "Вторник",
            "Среда",
            "Четверг",
            "Пятница"
        };

    if (filter == "today")
    {
        int today = QDate::currentDate().dayOfWeek();

        table->setColumnCount(4);
        table->setHorizontalHeaderLabels(
            {"№", "Предмет", "Учитель", "Время"});
        table->horizontalHeader()
            ->setSectionResizeMode(QHeaderView::Stretch);

        QSqlQuery q(Database::getDB());

        q.prepare(R"(
            SELECT
                sc.lesson_number,
                su.name,
                u.full_name,
                sc.start_time,
                sc.end_time
            FROM schedule sc
            JOIN subjects su
                ON su.id = sc.subject_id
            JOIN teachers t
                ON t.id = sc.teacher_id
            JOIN users u
                ON u.id = t.user_id
            JOIN students st
                ON st.class_id = sc.class_id
            WHERE st.user_id = ?
              AND sc.day_of_week = ?
            ORDER BY sc.lesson_number
        )");

        q.addBindValue(m_userId);
        q.addBindValue(today);

        if (!q.exec())
        {
            qDebug() << "Ошибка расписания:";
            qDebug() << q.lastError().text();
            return;
        }

        int row = 0;

        // Перебор запроса
        while (q.next())
        {
            table->insertRow(row);

            table->setItem(row, 0,
                           new QTableWidgetItem(
                               q.value(0).toString()));

            table->setItem(row, 1,
                           new QTableWidgetItem(
                               q.value(1).toString()));

            table->setItem(row, 2,
                           new QTableWidgetItem(
                               q.value(2).toString()));

            table->setItem(row, 3,
                           new QTableWidgetItem(
                               q.value(3).toString()
                               + " - "
                               + q.value(4).toString()));

            row++;
        }

        // Проверка наличия уровов
        if (row == 0)
        {
            table->insertRow(0);
            auto *empty = new QTableWidgetItem("Нет уроков на сегодня");
            empty->setTextAlignment(Qt::AlignCenter);
            table->setSpan(0, 0, 1, 4);
            table->setItem(0, 0, empty);
        }
    }
    else
    {
        table->setColumnCount(5);

        table->setHorizontalHeaderLabels(
            {"День", "№", "Предмет", "Учитель", "Время"});

        table->horizontalHeader()
            ->setSectionResizeMode(QHeaderView::Stretch);

        QSqlQuery q(Database::getDB());

        q.prepare(R"(
            SELECT
                sc.day_of_week,
                sc.lesson_number,
                su.name,
                u.full_name,
                sc.start_time,
                sc.end_time
            FROM schedule sc
            JOIN subjects su
                ON su.id = sc.subject_id
            JOIN teachers t
                ON t.id = sc.teacher_id
            JOIN users u
                ON u.id = t.user_id
            JOIN students st
                ON st.class_id = sc.class_id
            WHERE st.user_id = ?
            ORDER BY
                sc.day_of_week,
                sc.lesson_number
        )");

        q.addBindValue(m_userId);

        if (!q.exec())
        {
            qDebug() << "Ошибка расписания:";
            qDebug() << q.lastError().text();
            return;
        }

        int row = 0;

        while (q.next())
        {
            table->insertRow(row);

            int day = q.value(0).toInt();

            table->setItem(row, 0,
                           new QTableWidgetItem(dayNames.value(day)));

            table->setItem(row, 1,
                           new QTableWidgetItem(
                               q.value(1).toString()));

            table->setItem(row, 2,
                           new QTableWidgetItem(
                               q.value(2).toString()));

            table->setItem(row, 3,
                           new QTableWidgetItem(
                               q.value(3).toString()));

            table->setItem(row, 4,
                           new QTableWidgetItem(
                               q.value(4).toString()
                               + " - "
                               + q.value(5).toString()));

            row++;
        }

        // Проверка наличия расписания
        if (row == 0)
        {
            table->insertRow(0);
            auto *empty = new QTableWidgetItem("Расписание не найдено");
            empty->setTextAlignment(Qt::AlignCenter);
            table->setSpan(0, 0, 1, 5);
            table->setItem(0, 0, empty);
        }
    }
}