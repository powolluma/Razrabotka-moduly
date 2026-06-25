#include "averagewindow.h"
#include "database.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSqlQuery>
#include <QSqlError>
#include <QFrame>
#include <QListWidget>
#include <QDebug>

// Конструктор
AverageWindow::AverageWindow(int userId, QWidget *parent)
    : QWidget(parent), m_userId(userId)
{
    setWindowTitle("📈 Средний балл");
    setMinimumSize(600, 440);
    setupUI();
    loadSubjects(); // Загрузка списка предметов
}

// Создание окна
void AverageWindow::setupUI()
{
    // Фон
    setStyleSheet("QWidget { background-color: #E3F2FD; }");

    // Горизонтальный layout
    QHBoxLayout *main = new QHBoxLayout(this);
    main->setContentsMargins(24, 24, 24, 24);
    main->setSpacing(20);

    // Левая панель - список предметов
    QVBoxLayout *left = new QVBoxLayout();
    QLabel *listTitle = new QLabel("📔 Предметы");
    listTitle->setStyleSheet("color: #1565C0; font-size: 16px; font-weight: bold;");
    left->addWidget(listTitle);

    // Список предметов со стилями
    subjectList = new QListWidget();
    subjectList->setStyleSheet(R"(
    QListWidget {
        background-color: white;
        border-radius: 12px;
        padding: 8px;
    }
    QListWidget::item {
        padding: 10px 14px;
        border-radius: 8px;
        color: black;
    }
    QListWidget::item:selected {
        background-color: transparent;
        color: black;
    }
    QListWidget::item:hover {
        background-color: #E3F2FD;
    })");

    // Виджет
    left->addWidget(subjectList);

    // Левая панель в layout
    main->addLayout(left, 1);


    // Правая панель - карточка со средним баллом
    QVBoxLayout *right = new QVBoxLayout();
    right->setAlignment(Qt::AlignCenter);

    // Создание карточки
    QFrame *card = new QFrame();
    card->setStyleSheet("QFrame { background-color: white; border-radius: 18px; }");

    // Layout в карточке
    QVBoxLayout *cardLayout = new QVBoxLayout(card);
    cardLayout->setContentsMargins(30, 40, 30, 40);
    cardLayout->setSpacing(12);

    // Label
    avgLabel = new QLabel("-");
    avgLabel->setStyleSheet("color: #1565C0; font-size: 56px; font-weight: bold;");
    avgLabel->setAlignment(Qt::AlignCenter);

    // Label
    detailLabel = new QLabel("❓ Выберите предмет\nсправа");
    detailLabel->setStyleSheet("color: #90A4AE; font-size: 14px;");
    detailLabel->setAlignment(Qt::AlignCenter);

    // Карточка в правой панели
    cardLayout->addWidget(avgLabel);
    cardLayout->addWidget(detailLabel);
    right->addWidget(card);

    main->addLayout(right, 1);

    // Пересчет среднего балла при выборе строки
    connect(subjectList, &QListWidget::currentRowChanged,
            this, &AverageWindow::onSubjectSelected);
}

// Загрузка предметов
void AverageWindow::loadSubjects()
{
    subjectList->clear();

    // Создание запроса в sql с параметрами
    QSqlQuery q(Database::getDB());
    q.prepare(R"(
        SELECT DISTINCT s.id, s.name
        FROM subjects s
        JOIN grades g ON g.subject_id = s.id
        JOIN students st ON st.id = g.student_id
        WHERE st.user_id = ?
        ORDER BY s.name
    )");
    q.addBindValue(m_userId); // userid в запрос

    // Проверка ошибки базы данных
    if (!q.exec()) {
        qDebug() << "Ошибка загрузки предметов:" << q.lastError().text();
        return;
    }

    // Перебор всех строк запроса
    while (q.next()) {
        auto *item = new QListWidgetItem(q.value(1).toString());    // Создание названия предмета
        item->setData(Qt::UserRole, q.value(0).toInt());    // Сохранение id предмета
        subjectList->addItem(item); // Добавление в список
    }
}

// Расчет среднего балла предмета
void AverageWindow::onSubjectSelected(int row)
{
    // Пропуск пустых строк
    if (row < 0) return;

    // Получение id предмета
    int subjectId = subjectList->item(row)->data(Qt::UserRole).toInt();

    // Запрос в sql с параметрами
    QSqlQuery q(Database::getDB());
    q.prepare(R"(
        SELECT AVG(g.grade), COUNT(g.grade), MAX(g.grade), MIN(g.grade)
        FROM grades g
        JOIN students st ON st.id = g.student_id
        WHERE st.user_id = ? AND g.subject_id = ?
    )");
    // id пользователя и предмета
    q.addBindValue(m_userId);
    q.addBindValue(subjectId);

    // Проверка ошибки базы данных
    if (!q.exec()) {
        qDebug() << "Ошибка расчёта среднего балла:" << q.lastError().text();
        return;
    }

    // Проверка наличия результата
    if (q.next()) {
        double avg = q.value(0).toDouble();
        int count = q.value(1).toInt();
        int maxG = q.value(2).toInt();
        int minG = q.value(3).toInt();
        // Вывод
        avgLabel->setText(QString::number(avg, 'f', 2));

        // Цвет балла от оценки
        QString color = "#2E7D32";
        if (avg < 3.5) color = "#C62828";
        else if (avg < 4.5) color = "#F57F17";

        avgLabel->setStyleSheet(QString("color: %1; font-size: 56px; font-weight: bold;").arg(color));

        detailLabel->setText(QString("Оценок: %1\nМакс: %2 | Мин: %3")
                                 .arg(count).arg(maxG).arg(minG));
    }
}