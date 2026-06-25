#include "studentmainwindow.h"
#include "loginwindow.h"
#include "gradeswindow.h"
#include "schedulewindow.h"
#include "averagewindow.h"
#include "quartergradeswindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFrame>
#include <QSqlQuery>
#include <QStatusBar>

// Конструктор
StudentMainWindow::StudentMainWindow(QWidget *parent)
    : QMainWindow(parent), m_userId(0)
{
    setWindowTitle("Журнал — Ученик");
    setMinimumSize(900, 580);
    setupUI();
    applyStyle();
    setupStatusBar(); // Вызов статус бара
}

// Деструктор
StudentMainWindow::~StudentMainWindow() {}


// Создание окна
void StudentMainWindow::setupUI()
{
    // Виджет
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    // Карточка
    QHBoxLayout *root = new QHBoxLayout(central);
    root->setContentsMargins(0, 0, 0, 0);
    root->setSpacing(0);

    // === Левая боковая панель ===
    QWidget *sidePanel = new QWidget();
    sidePanel->setObjectName("sidePanel");
    sidePanel->setFixedWidth(210);

    QVBoxLayout *side = new QVBoxLayout(sidePanel);
    side->setContentsMargins(16, 30, 16, 20);
    side->setSpacing(12);

    nameLabel = new QLabel("Ученик");
    nameLabel->setStyleSheet("color: white; font-size: 14px; font-weight: bold;");
    nameLabel->setAlignment(Qt::AlignCenter);

    classLabel = new QLabel("10 «А» класс");
    classLabel->setStyleSheet("color: #90CAF9; font-size: 12px;");
    classLabel->setAlignment(Qt::AlignCenter);

    side->addWidget(nameLabel);
    side->addWidget(classLabel);
    side->addSpacing(10);

    // Стиль кнопок бокового меню
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
        QPushButton:pressed { background-color: #0D47A1; }
    )";

    // Функция для создания кнопок
    auto makeBtn = [&](const QString &text, const char *slot) {
        QPushButton *btn = new QPushButton(text);
        btn->setStyleSheet(btnStyle);
        btn->setCursor(Qt::PointingHandCursor);
        connect(btn, SIGNAL(clicked()), this, slot);
        side->addWidget(btn);
    };

    makeBtn("📝 Оценки", SLOT(on_sideButton_clicked()));
    makeBtn("📅 Расписание", SLOT(on_btnSchedule_clicked()));
    makeBtn("📈 Средний балл", SLOT(on_btnAverage_clicked()));
    makeBtn("📋 Оценки за четверть", SLOT(on_btnQuarterGrades_clicked()));

    side->addStretch();

    // Кнопка "Выйти"
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
    btnLogout->setCursor(Qt::PointingHandCursor);
    connect(btnLogout, SIGNAL(clicked()), this, SLOT(on_btnLogout_clicked()));
    side->addWidget(btnLogout);

    root->addWidget(sidePanel);

    // === Правая панель ===
    QWidget *content = new QWidget();
    QVBoxLayout *contentLayout = new QVBoxLayout(content);
    contentLayout->setContentsMargins(30, 30, 30, 30);
    contentLayout->setSpacing(20);

    welcomeLabel = new QLabel("Добро пожаловать!");
    welcomeLabel->setStyleSheet("color: #1565C0; font-size: 22px; font-weight: bold;");
    contentLayout->addWidget(welcomeLabel);

    // Информационные карточки
    QHBoxLayout *cards = new QHBoxLayout();
    cards->setSpacing(16);

    auto makeCard = [&](const QString &value, const QString &label) {
        QFrame *card = new QFrame();
        card->setStyleSheet("QFrame { background-color: white; border-radius: 14px; }");

        QVBoxLayout *cl = new QVBoxLayout(card);
        cl->setContentsMargins(20, 20, 20, 20);

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

    makeCard("4.7", "📊 Средний балл");
    makeCard("6", "📚 Уроков сегодня");
    makeCard("3", "⭐️ Новых оценок");

    contentLayout->addLayout(cards);
    contentLayout->addStretch();
    root->addWidget(content, 1);
}

// Применение стилей
void StudentMainWindow::applyStyle()
{
    setStyleSheet(R"(
        QMainWindow { background-color: #E3F2FD; }
        QWidget#sidePanel { background-color: #1565C0; }
    )");
}



// Установка имени ученика
void StudentMainWindow::setStudentName(const QString &name)
{
    nameLabel->setText("👤 " + name);
    welcomeLabel->setText("✅ Добро пожаловать, " + name.split(" ").first() + "!");
}

// Загрузка информации об ученике
void StudentMainWindow::setUserId(int id)
{
    m_userId = id;

    QSqlQuery q;
    q.prepare(R"(
        SELECT c.name
        FROM classes c
        JOIN students s ON s.class_id = c.id
        WHERE s.user_id = ?
    )");
    q.addBindValue(id);
    q.exec();
    if (q.next())
        classLabel->setText(q.value(0).toString() + " класс");
}

// === Обработчики кнопок ===
//Кнопка Оценки
void StudentMainWindow::on_sideButton_clicked()
{
    statusTabLabel->setText("Оценки");
    GradesWindow *w = new GradesWindow(m_userId);
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
}

//Кнопка Расписание
void StudentMainWindow::on_btnSchedule_clicked()
{
    statusTabLabel->setText("Расписание");
    ScheduleWindow *w = new ScheduleWindow(m_userId);
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
}

//Кнопка Средний балл
void StudentMainWindow::on_btnAverage_clicked()
{
    statusTabLabel->setText("Средний балл");
    AverageWindow *w = new AverageWindow(m_userId);
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
}

//Кнопка Оценки за четверть
void StudentMainWindow::on_btnQuarterGrades_clicked()
{
    statusTabLabel->setText("Оценки за четверть");
    QuarterGradesWindow *w = new QuarterGradesWindow(m_userId);
    w->setAttribute(Qt::WA_DeleteOnClose);
    w->show();
}

//Кнопка Выход
void StudentMainWindow::on_btnLogout_clicked()
{
    LoginWindow *login = new LoginWindow();
    login->show();
    this->close();
}

// == Работа со статус баром ===
// Установка статус бара
void StudentMainWindow::setupStatusBar()
{
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
    connect(sessionTimer, &QTimer::timeout, this, &StudentMainWindow::updateSessionTime);
    sessionTimer->start(1000);
}

// Обновление времени сессии
void StudentMainWindow::updateSessionTime()
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