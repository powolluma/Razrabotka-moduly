#include "quartergradeswindow.h"
#include "database.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QHeaderView>
#include <QSqlQuery>
#include <QSqlError>
#include <QFont>
#include <QComboBox>
#include <QColor>
#include <QDebug>

// Конструктор
QuarterGradesWindow::QuarterGradesWindow(int userId, QWidget *parent)
    : QWidget(parent), m_userId(userId)
{
    setWindowTitle("Оценки за четверть");
    setMinimumSize(700, 480);
    setupUI();
    loadGrades(1);
}

// Создание окна
void QuarterGradesWindow::setupUI()
{
    setStyleSheet("QWidget { background-color: #E3F2FD; }");

    // Layout
    QVBoxLayout *main = new QVBoxLayout(this);
    main->setContentsMargins(24, 24, 24, 24);
    main->setSpacing(16);

    // Заголовок
    QLabel *title = new QLabel("Оценки за четверть");
    title->setStyleSheet("color: #1565C0; font-size: 20px; font-weight: bold;");
    main->addWidget(title);

    // Выбор четверти
    QHBoxLayout *topLayout = new QHBoxLayout();
    QLabel *comboLabel = new QLabel("Четверть:");
    comboLabel->setStyleSheet("color: #1565C0; font-size: 14px; font-weight: bold;");

    // Комбо-бокс
    quarterCombo = new QComboBox();
    quarterCombo->addItem("1 четверть", 1);
    quarterCombo->addItem("2 четверть", 2);
    quarterCombo->addItem("3 четверть", 3);
    quarterCombo->addItem("4 четверть", 4);
    quarterCombo->setCursor(Qt::PointingHandCursor);

    // Стиль комбобокса
    quarterCombo->setStyleSheet(R"(
        QComboBox {
            background-color: #1976D2;
            color: white;
            border-radius: 10px;
            padding: 6px 16px;
            min-width: 140px;
        }
        QComboBox QAbstractItemView {
            background-color: white;
            color: #1565C0;
            selection-background-color: #1976D2;
        })");
    topLayout->addWidget(comboLabel);
    topLayout->addWidget(quarterCombo);
    topLayout->addStretch();
    main->addLayout(topLayout);

    // Таблица оценок
    table = new QTableWidget();
    table->setColumnCount(3);
    table->setHorizontalHeaderLabels({"Предмет", "Оценки", "Среднее"});
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
    }
    QHeaderView::section {
        background-color: #1976D2;
        color: white;
        font-weight: bold;
    }
    QTableWidget::item {
        color: black;                    /* Чёрный текст во всех ячейках */
        padding: 6px;
    }
    QTableWidget::item:selected {
        background-color: transparent;   /* Убираем выделение */
        color: black;
    })");
    main->addWidget(table);

    // Подключение смены четверти
    connect(quarterCombo, &QComboBox::currentIndexChanged,
            this, &QuarterGradesWindow::onQuarterChanged);
}

// Смена четверти
void QuarterGradesWindow::onQuarterChanged(int index)
{
    int quarter = quarterCombo->itemData(index).toInt();
    loadGrades(quarter);
}

// Загрузка оценок за выбранную четверть
void QuarterGradesWindow::loadGrades(int quarter)
{
    table->setRowCount(0);

    QSqlQuery q(Database::getDB());
    q.prepare(R"(
        SELECT s.name,
               GROUP_CONCAT(g.grade, ', '),
               AVG(g.grade)
        FROM grades g
        JOIN subjects s ON s.id = g.subject_id
        JOIN students st ON st.id = g.student_id
        WHERE st.user_id = ? AND g.quarter = ?
        GROUP BY s.id
        ORDER BY s.name
    )");
    q.addBindValue(m_userId);
    q.addBindValue(quarter);

    if (!q.exec()) {
        qDebug() << "Ошибка загрузки оценок за четверть:" << q.lastError().text();
        return;
    }

    int row = 0;
    while (q.next()) {
        table->insertRow(row);

        QString subject = q.value(0).toString();
        QString grades  = q.value(1).toString();
        double avg      = q.value(2).toDouble();

        auto *itemSubj   = new QTableWidgetItem(subject);
        auto *itemGrades = new QTableWidgetItem(grades);
        auto *itemAvg    = new QTableWidgetItem(QString::number(avg, 'f', 2));

        itemSubj->setTextAlignment(Qt::AlignCenter);
        itemGrades->setTextAlignment(Qt::AlignCenter);
        itemAvg->setTextAlignment(Qt::AlignCenter);

        // Применение шрифта
        QFont f; f.setBold(true);
        itemAvg->setFont(f);
        table->setItem(row, 0, itemSubj);
        table->setItem(row, 1, itemGrades);
        table->setItem(row, 2, itemAvg);

        row++;
    }

    // Проверка наличия оценок
    if (row == 0) {
        table->insertRow(0);
        auto *empty = new QTableWidgetItem("Нет оценок за эту четверть");
        empty->setTextAlignment(Qt::AlignCenter);
        empty->setForeground(QColor("#9E9E9E"));
        table->setSpan(0, 0, 1, 3);
        table->setItem(0, 0, empty);
    }
}