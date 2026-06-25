#include "parentmainwindow.h"
#include "loginwindow.h"
#include "gradeswindow.h"
#include "schedulewindow.h"
#include "averagewindow.h"
#include "quartergradeswindow.h"
#include "parentmessageswindow.h"
#include "database.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFrame>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QStatusBar>

// Конструктор
ParentMainWindow::ParentMainWindow(QWidget *parent)
    : QMainWindow(parent), m_userId(0), m_studentId(0)
{
    setWindowTitle("Журнал — Родитель");
    setMinimumSize(900, 580);
    setupUI();
    applyStyle();
    setupStatusBar();
}

// Создание меню
void ParentMainWindow::setupUI()
{
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QHBoxLayout *root = new QHBoxLayout(centralWidget);
    root->setContentsMargins(0, 0, 0, 0);
    root->setSpacing(0);

    // === Левая панель ===
    // Layout
    QWidget *sidePanel = new QWidget();
    sidePanel->setObjectName("sidePanel");
    sidePanel->setFixedWidth(210);

    // Layout
    QVBoxLayout *side = new QVBoxLayout(sidePanel);
    side->setContentsMargins(16, 30, 16, 20);
    side->setSpacing(12);

    // Текст
    nameLabel = new QLabel("👩‍🦰 Родитель");
    nameLabel->setStyleSheet("color: white; font-size: 14px; font-weight: bold;");
    nameLabel->setAlignment(Qt::AlignCenter);

    // Текст
    classLabel = new QLabel("👩‍🦰 Родитель ученика");
    classLabel->setStyleSheet("color: #90CAF9; font-size: 12px;");
    classLabel->setAlignment(Qt::AlignCenter);

    side->addWidget(nameLabel);
    side->addWidget(classLabel);
    side->addSpacing(10);

    // Стили кнопок
    QString btnStyle = R"(
        QPushButton {
            background-color: #1976D2;
            color: white;
            border-radius: 12px;
            font-size: 14px;
            padding: 10px;
            text-align: left;
            border: none;
        }
        QPushButton:hover { background-color: #2196F3; }
        QPushButton:pressed { background-color: #0D47A1; } )";

    // Функция для создания кнопок с одним стилем
    auto makeBtn = [&](const QString &text, const char *slot) {
        QPushButton *btn = new QPushButton(text);
        btn->setStyleSheet(btnStyle);
        connect(btn, SIGNAL(clicked()), this, slot);
        side->addWidget(btn);
    };

    // Создание кнопок
    makeBtn("📝 Оценки", SLOT(on_btnGrades_clicked()));
    makeBtn("📅 Расписание", SLOT(on_btnSchedule_clicked()));
    makeBtn("📈 Средний балл", SLOT(on_btnAverage_clicked()));
    makeBtn("📋 Оценки за четверть", SLOT(on_btnQuarterGrades_clicked()));
    makeBtn("💬 Сообщения", SLOT(on_btnMessages_clicked()));
    side->addStretch();

    // Кнопка Выйти и стили
    QPushButton *btnLogout = new QPushButton("Выйти");
    btnLogout->setStyleSheet(R"(
        QPushButton {
            background-color: transparent;
            color: #EF9A9A;
            border-radius: 12px;
            font-size: 13px;
            padding: 8px;
            text-align: left;
            border: 1px solid #EF9A9A;
        }
        QPushButton:hover { background-color: #B71C1C; color: white; border-color: #B71C1C; }
    )");
    connect(btnLogout, SIGNAL(clicked()), this, SLOT(on_btnLogout_clicked()));
    side->addWidget(btnLogout);
    root->addWidget(sidePanel);

    // === Правая панель ===
    QWidget *content = new QWidget();
    QVBoxLayout *contentLayout = new QVBoxLayout(content);
    contentLayout->setContentsMargins(30, 30, 30, 30);
    contentLayout->setSpacing(20);

    // Строка с текстом
    welcomeLabel = new QLabel("👋 Добро пожаловать!");
    welcomeLabel->setStyleSheet("color: #1565C0; font-size: 22px; font-weight: bold;");
    contentLayout->addWidget(welcomeLabel);

    // Layout
    QHBoxLayout *cards = new QHBoxLayout();
    cards->setSpacing(16);

    // Функция для создания карточек
    auto makeCard = [&](const QString &value, const QString &label) {
        QFrame *card = new QFrame();
        card->setStyleSheet("QFrame { background-color: white; border-radius: 14px; }");

        QVBoxLayout *cl = new QVBoxLayout(card);
        QLabel *val = new QLabel(value);
        val->setStyleSheet("color: #1565C0; font-size: 26px; font-weight: bold;");
        val->setAlignment(Qt::AlignCenter);

        QLabel *lbl = new QLabel(label);
        lbl->setStyleSheet("color: #757575; font-size: 12px;");
        lbl->setAlignment(Qt::AlignCenter);

        cl->addWidget(val);
        cl->addWidget(lbl);
        cards->addWidget(card);
    };

    // Карточки
    makeCard("4.7", "📊 Средний балл");
    makeCard("6", "📚 Уроков сегодня");
    makeCard("3", "⭐️ Новых оценок");
    contentLayout->addLayout(cards);
    contentLayout->addStretch();
    root->addWidget(content, 1);
}

// Применение стилей
void ParentMainWindow::applyStyle()
{
    setStyleSheet(R"(
        QMainWindow { background-color: #E3F2FD; }
        QWidget#sidePanel { background-color: #1565C0; }
    )");
}

// Строка с текстом приветствия
void ParentMainWindow::setParentName(const QString &name)
{
    nameLabel->setText(name);
    welcomeLabel->setText("👋 Добро пожаловать, " + name.split(" ").first() + "!");
}

// Получение id родителя и его ребёнка
void ParentMainWindow::setUserId(int id)
{
    m_userId = id;
    QSqlQuery q(Database::getDB());
    q.prepare("SELECT student_id FROM parents WHERE user_id = ?");
    q.addBindValue(id);

    if (!q.exec()) {
        qDebug() << "Ошибка поиска ребёнка родителя:" << q.lastError().text();
        return;
    }

    if (q.next()) {
        m_studentId = q.value(0).toInt();
        qDebug() << "Найден ребёнок, student_id =" << m_studentId;
    } else {
        qDebug() << "Для user_id =" << id << "не найдена запись в таблице parents!";
    }
}

// Получение id ребенка
bool ParentMainWindow::resolveStudentUserId(int &outUserId)
{
    if (m_studentId <= 0) {
        QMessageBox::warning(this, "Ошибка",
                             "Не удалось определить вашего ребёнка. Обратитесь к администратору.");
        return false;
    }

    QSqlQuery q(Database::getDB());
    q.prepare("SELECT user_id FROM students WHERE id = ?");
    q.addBindValue(m_studentId);

    if (!q.exec()) {
        qDebug() << "Ошибка получения user_id ученика:" << q.lastError().text();
        return false;
    }

    if (!q.next()) {
        qDebug() << "Не найден ученик с id =" << m_studentId;
        return false;
    }

    outUserId = q.value(0).toInt();
    return true;
}

// === Обработчики кнопок ===
// Кнопка Оценки
void ParentMainWindow::on_btnGrades_clicked()
{
    statusTabLabel->setText("5️⃣ Оценки");
    int studentUserId;
    if (!resolveStudentUserId(studentUserId)) return;

    GradesWindow *w = new GradesWindow(studentUserId);
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
}

// Кнопка Расписание
void ParentMainWindow::on_btnSchedule_clicked()
{
    statusTabLabel->setText("🪧 Расписание");
    int studentUserId;
    if (!resolveStudentUserId(studentUserId)) return;

    ScheduleWindow *w = new ScheduleWindow(studentUserId);
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
}

//Кнопка Средний балл
void ParentMainWindow::on_btnAverage_clicked()
{
    statusTabLabel->setText("📈 Средний балл");
    int studentUserId;
    if (!resolveStudentUserId(studentUserId)) return;

    AverageWindow *w = new AverageWindow(studentUserId);
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
}

// Кнопка Оценки за четверть
void ParentMainWindow::on_btnQuarterGrades_clicked()
{
    statusTabLabel->setText("🧠 Оценки за четверть");
    int studentUserId;
    if (!resolveStudentUserId(studentUserId)) return;

    QuarterGradesWindow *w = new QuarterGradesWindow(studentUserId);
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
}

// Кнопка сообщения
void ParentMainWindow::on_btnMessages_clicked()
{
    statusTabLabel->setText("💬 Сообщения");
    ParentMessagesWindow *w = new ParentMessagesWindow(m_userId);
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
}

// Кнопка выйти
void ParentMainWindow::on_btnLogout_clicked()
{
    LoginWindow *login = new LoginWindow();
    login->show();
    this->close();
}

// === Работа с статус баром ===
// Установка статус бара
void ParentMainWindow::setupStatusBar()
{
    // Текст
    statusTabLabel = new QLabel("Главная");
    statusTabLabel->setStyleSheet("color: #1565C0; font-size: 12px; padding-left: 6px;");

    statusTimeLabel = new QLabel("00:00:00");
    statusTimeLabel->setStyleSheet("color: #1565C0; font-size: 12px; padding-right: 6px;");

    statusBar()->setStyleSheet(R"(
        QStatusBar {
            background-color: #E3F2FD;
            border-top: 1px solid #BBDEFB;
        }
    )");

    statusBar()->addWidget(statusTabLabel, 1);
    statusBar()->addPermanentWidget(statusTimeLabel);

    sessionElapsed.start();
    sessionTimer = new QTimer(this);
    connect(sessionTimer, &QTimer::timeout, this, &ParentMainWindow::updateSessionTime);
    sessionTimer->start(1000);
}

// Обновление сессии
void ParentMainWindow::updateSessionTime()
{
    qint64 secs = sessionElapsed.elapsed() / 1000;
    int h = secs / 3600;
    int m = (secs % 3600) / 60;
    int s = secs % 60;

    statusTimeLabel->setText(QString("%1:%2:%3")
                                 .arg(h, 2, 10, QChar('0'))
                                 .arg(m, 2, 10, QChar('0'))
                                 .arg(s, 2, 10, QChar('0')));
}