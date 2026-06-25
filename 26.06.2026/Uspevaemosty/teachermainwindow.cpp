#include "teachermainwindow.h"
#include "loginwindow.h"
#include "database.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFrame>
#include <QScrollArea>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDate>
#include <QDebug>
#include <QPushButton>
#include <QOverload>
#include <QStatusBar>

// Конструктор
TeacherMainWindow::TeacherMainWindow(QWidget *parent)
    : QMainWindow(parent), m_userId(0), m_teacherId(0)
{
    setWindowTitle("Журнал — Учитель");
    setMinimumSize(950, 620);
    setupUI();
    applyStyle();
    setupStatusBar();
}

// Создание окна
void TeacherMainWindow::setupUI()
{
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    QHBoxLayout *root = new QHBoxLayout(central);
    root->setContentsMargins(0, 0, 0, 0);
    root->setSpacing(0);

    // === Левая панель ===
    QWidget *sidePanel = new QWidget();
    sidePanel->setObjectName("sidePanel");
    sidePanel->setFixedWidth(210);

    QVBoxLayout *side = new QVBoxLayout(sidePanel);
    side->setContentsMargins(16, 30, 16, 20);
    side->setSpacing(12);

    nameLabel = new QLabel("🎓 Учитель");
    nameLabel->setStyleSheet("color: white; font-size: 14px; font-weight: bold;");
    nameLabel->setAlignment(Qt::AlignCenter);
    nameLabel->setWordWrap(true);

    subjectLabel = new QLabel("📘 Предмет");
    subjectLabel->setStyleSheet("color: #90CAF9; font-size: 12px;");
    subjectLabel->setAlignment(Qt::AlignCenter);

    side->addWidget(nameLabel);
    side->addWidget(subjectLabel);
    side->addSpacing(10);
    side->addStretch();

    // Кнопка Выйти
    QPushButton *btnLogout = new QPushButton("🚪 Выйти");
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
    connect(btnLogout, &QPushButton::clicked, this, &TeacherMainWindow::on_btnLogout_clicked);
    side->addWidget(btnLogout);

    root->addWidget(sidePanel);

    // === Правая панель ===
    QWidget *content = new QWidget();
    content->setObjectName("contentArea");

    QVBoxLayout *contentLayout = new QVBoxLayout(content);
    contentLayout->setContentsMargins(30, 30, 30, 30);
    contentLayout->setSpacing(20);

    welcomeLabel = new QLabel("👋 Добро пожаловать!");
    welcomeLabel->setStyleSheet("color: #1565C0; font-size: 22px; font-weight: bold;");
    contentLayout->addWidget(welcomeLabel);

    QString labelStyle = "color: #1565C0; font-size: 13px; font-weight: bold; font-family: Arial;";
    QString comboStyle = R"(
        QComboBox {
            background-color: white;
            color: black;
            border-radius: 10px;
            font-size: 13px;
            padding: 6px 12px;
            border: 1px solid #BBDEFB;
            min-width: 220px;
        }
        QComboBox::drop-down { border: none; }
        QComboBox QAbstractItemView {
            background-color: white;
            color: black;
            selection-background-color: #BBDEFB;
        }
    )";

    // === Блок выбора класса ===
    QFrame *cardClass = new QFrame();
    cardClass->setStyleSheet("QFrame { background-color: white; border-radius: 14px; }");
    QVBoxLayout *clLayout = new QVBoxLayout(cardClass);
    clLayout->setContentsMargins(20, 16, 20, 16);
    clLayout->setSpacing(10);

    QLabel *lbClass = new QLabel("🏫 Выберите класс:");
    lbClass->setStyleSheet(labelStyle);
    classCombo = new QComboBox();
    classCombo->setStyleSheet(comboStyle);

    clLayout->addWidget(lbClass);
    clLayout->addWidget(classCombo);
    contentLayout->addWidget(cardClass);

    connect(classCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &TeacherMainWindow::onClassChanged);

    // === Блок выбора даты ===
    QFrame *cardDate = new QFrame();
    cardDate->setStyleSheet("QFrame { background-color: white; border-radius: 14px; }");
    QVBoxLayout *dtLayout = new QVBoxLayout(cardDate);
    dtLayout->setContentsMargins(20, 16, 20, 16);
    dtLayout->setSpacing(10);

    QLabel *lbDate = new QLabel("📅 Дата урока:");
    lbDate->setStyleSheet(labelStyle);
    dateEdit = new QDateEdit(QDate::currentDate());
    dateEdit->setCalendarPopup(true);
    dateEdit->setDisplayFormat("dd.MM.yyyy");
    dateEdit->setStyleSheet(R"(
        QDateEdit {
            background-color: white;
            color: black;
            border-radius: 10px;
            padding: 6px 12px;
            border: 1px solid #BBDEFB;
        }
    )");
    dtLayout->addWidget(lbDate);
    dtLayout->addWidget(dateEdit);
    contentLayout->addWidget(cardDate);

    // === Блок выставления оценки ===
    QFrame *cardGrade = new QFrame();
    cardGrade->setStyleSheet("QFrame { background-color: white; border-radius: 14px; }");
    QVBoxLayout *grLayout = new QVBoxLayout(cardGrade);
    grLayout->setContentsMargins(20, 16, 20, 16);
    grLayout->setSpacing(10);

    QLabel *lbStudent = new QLabel("👤 Выберите ученика:");
    lbStudent->setStyleSheet(labelStyle);
    studentCombo = new QComboBox();
    studentCombo->setStyleSheet(comboStyle);

    QLabel *lbGrade = new QLabel("📝 Оценка (1-5):");
    lbGrade->setStyleSheet(labelStyle);
    gradeSpin = new QSpinBox();
    gradeSpin->setRange(1, 5);
    gradeSpin->setValue(5);
    gradeSpin->setStyleSheet(R"(
        QSpinBox {
            background-color: white;
            color: black;
            border-radius: 10px;
            padding: 6px 12px;
            border: 1px solid #BBDEFB;
        }
    )");

    QLabel *lbQuarter = new QLabel("📆 Четверть:");
    lbQuarter->setStyleSheet(labelStyle);
    quarterCombo = new QComboBox();
    quarterCombo->addItem("1 четверть", 1);
    quarterCombo->addItem("2 четверть", 2);
    quarterCombo->addItem("3 четверть", 3);
    quarterCombo->addItem("4 четверть", 4);
    quarterCombo->setCurrentIndex(0);
    quarterCombo->setStyleSheet(comboStyle);

    QPushButton *btnSetGrade = new QPushButton("✅ Выставить оценку");
    btnSetGrade->setStyleSheet(R"(
        QPushButton {
            background-color: #1976D2;
            color: white;
            border-radius: 10px;
            font-size: 13px;
            padding: 8px 20px;
        }
        QPushButton:hover { background-color: #2196F3; }
    )");
    connect(btnSetGrade, &QPushButton::clicked, this, &TeacherMainWindow::on_btnSetGrade_clicked);

    grLayout->addWidget(lbStudent);
    grLayout->addWidget(studentCombo);
    grLayout->addWidget(lbGrade);
    grLayout->addWidget(gradeSpin);
    grLayout->addWidget(lbQuarter);
    grLayout->addWidget(quarterCombo);
    grLayout->addWidget(btnSetGrade);
    contentLayout->addWidget(cardGrade);

    // === Блок отправки сообщения ===
    QFrame *cardMsg = new QFrame();
    cardMsg->setStyleSheet("QFrame { background-color: white; border-radius: 14px; }");
    QVBoxLayout *msgLayout = new QVBoxLayout(cardMsg);
    msgLayout->setContentsMargins(20, 16, 20, 16);
    msgLayout->setSpacing(10);

    QLabel *lbMsg = new QLabel("💬 Сообщение родителям выбранного ученика:");
    lbMsg->setStyleSheet(labelStyle);
    messageEdit = new QTextEdit();
    messageEdit->setPlaceholderText("Введите сообщение...");
    messageEdit->setFixedHeight(80);
    messageEdit->setStyleSheet(R"(
        QTextEdit {
            background-color: #F5F9FF;
            color: black;
            border-radius: 10px;
            padding: 8px;
            border: 1px solid #BBDEFB;
        }
    )");

    QPushButton *btnSendMsg = new QPushButton("💬 Отправить сообщение");
    btnSendMsg->setStyleSheet(R"(
        QPushButton {
            background-color: #388E3C;
            color: white;
            border-radius: 10px;
            padding: 8px 20px;
        }
        QPushButton:hover { background-color: #43A047; }
    )");
    connect(btnSendMsg, &QPushButton::clicked, this, &TeacherMainWindow::on_btnSendMessage_clicked);

    msgLayout->addWidget(lbMsg);
    msgLayout->addWidget(messageEdit);
    msgLayout->addWidget(btnSendMsg);
    contentLayout->addWidget(cardMsg);

    statusLabel = new QLabel("");
    statusLabel->setStyleSheet("color: #2E7D32; font-size: 13px;");
    statusLabel->setAlignment(Qt::AlignCenter);
    contentLayout->addWidget(statusLabel);
    contentLayout->addStretch();

    // Скролл оборачивает уже полностью готовый content
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidget(content);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setStyleSheet("QScrollArea { background-color: transparent; } QWidget#contentArea { background-color: #E3F2FD; }");

    root->addWidget(scrollArea, 1);
}

// Применение стилей
void TeacherMainWindow::applyStyle()
{
    setStyleSheet(R"(
        QMainWindow { background-color: #E3F2FD; }
        QWidget#sidePanel { background-color: #1565C0; }
    )");
}

// Получение имени Учителя
void TeacherMainWindow::setTeacherName(const QString &name)
{
    if (nameLabel) nameLabel->setText("🎓 " + name);
    if (welcomeLabel) welcomeLabel->setText("👋 Добро пожаловать, " + name.split(" ").first() + "!");
}

void TeacherMainWindow::setUserId(int id)
{
    m_userId = id;

    QSqlQuery q(Database::getDB());
    q.prepare("SELECT id FROM teachers WHERE user_id = ?");
    q.addBindValue(id);
    if (q.exec() && q.next()) {
        m_teacherId = q.value(0).toInt();
    } else {
        return;
    }

    loadSubjectName();
    loadClasses();

    if (classCombo && classCombo->count() > 0) {
        classCombo->setCurrentIndex(0);
        loadStudents();
    }
}

// Загрузка Предмета Учителя
void TeacherMainWindow::loadSubjectName()
{
    QSqlQuery q(Database::getDB());
    q.prepare(R"(
        SELECT s.name FROM subjects s
        JOIN teacher_subjects ts ON ts.subject_id = s.id
        WHERE ts.teacher_id = ?
        LIMIT 1
    )");
    q.addBindValue(m_teacherId);
    if (q.exec() && q.next()) {
        subjectLabel->setText("📘 " + q.value(0).toString());
    } else {
    }
}

// Загрузка классов
void TeacherMainWindow::loadClasses()
{
    if (!classCombo) return;
    classCombo->blockSignals(true);
    classCombo->clear();

    QSqlQuery q(Database::getDB());
    q.prepare(R"(
        SELECT DISTINCT c.id, c.name FROM classes c
        JOIN teacher_subjects ts ON ts.class_id = c.id
        WHERE ts.teacher_id = ?
        ORDER BY c.name
    )");
    q.addBindValue(m_teacherId);

    if (!q.exec()) {
        qDebug() << "Ошибка загрузки классов:" << q.lastError().text();
        classCombo->blockSignals(false);
        return;
    }

    while (q.next()) {
        classCombo->addItem(q.value(1).toString(), q.value(0).toInt());
    }

    classCombo->blockSignals(false);
}

// Загрузка ученика
void TeacherMainWindow::loadStudents()
{
    if (!studentCombo) return;
    studentCombo->clear();

    if (!classCombo || classCombo->count() == 0) {
        return;
    }

    int classId = classCombo->currentData().toInt();
    if (classId <= 0) {
        return;
    }

    QSqlQuery q(Database::getDB());
    q.prepare(R"(
        SELECT st.id, u.full_name FROM students st
        JOIN users u ON u.id = st.user_id
        WHERE st.class_id = ?
        ORDER BY u.full_name
    )");
    q.addBindValue(classId);

    if (!q.exec()) {
        return;
    }

    while (q.next()) {
        studentCombo->addItem(q.value(1).toString(), q.value(0).toInt());
    }
}

// Смена класса
void TeacherMainWindow::onClassChanged(int index)
{
    if (index < 0) return;
    loadStudents();
}

// === Обработчики кнопок ===
// Кнопка Выставление оценки
void TeacherMainWindow::on_btnSetGrade_clicked()
{
    statusTabLabel->setText("Выставление оценки");
    if (!studentCombo || studentCombo->count() == 0) {
        QMessageBox::warning(this, "Ошибка", "Сначала выберите класс и ученика!");
        return;
    }
    int studentId = studentCombo->currentData().toInt();
    int classId   = classCombo->currentData().toInt();
    int grade     = gradeSpin->value();
    int quarter   = quarterCombo->currentData().toInt();
    QString date  = dateEdit->date().toString("yyyy-MM-dd");
    QSqlQuery subQ(Database::getDB());
    subQ.prepare(R"(
        SELECT subject_id FROM teacher_subjects
        WHERE teacher_id = ? AND class_id = ?
        LIMIT 1
    )");
    subQ.addBindValue(m_teacherId);
    subQ.addBindValue(classId);
    if (!subQ.exec() || !subQ.next()) {
        QMessageBox::warning(this, "Ошибка", "Не удалось определить предмет для этого класса.");
        return;
    }
    int subjectId = subQ.value(0).toInt();
    QSqlQuery q(Database::getDB());
    q.prepare(R"(
        INSERT INTO grades (student_id, subject_id, grade, date, quarter)
        VALUES (?, ?, ?, ?, ?)
    )");
    q.addBindValue(studentId);
    q.addBindValue(subjectId);
    q.addBindValue(grade);
    q.addBindValue(date);
    q.addBindValue(quarter);
    if (!q.exec()) {
        QMessageBox::warning(this, "Ошибка", "Не удалось сохранить оценку.");
        return;
    }

    statusLabel->setStyleSheet("color: #2E7D32; font-size: 13px;");
    statusLabel->setText(QString("✅ Оценка %1 выставлена ученику %2")
                             .arg(grade)
                             .arg(studentCombo->currentText()));
}

// Кнопка Отправить сообщение
void TeacherMainWindow::on_btnSendMessage_clicked()
{
    statusTabLabel->setText("Отправка сообщения");
    if (!studentCombo || studentCombo->count() == 0) {
        QMessageBox::warning(this, "Ошибка", "Сначала выберите класс и ученика!");
        return;
    }

    QString text = messageEdit->toPlainText().trimmed();
    if (text.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите текст сообщения!");
        return;
    }

    int studentId = studentCombo->currentData().toInt();

    QSqlQuery parentQ(Database::getDB());
    parentQ.prepare("SELECT user_id FROM parents WHERE student_id = ?");
    parentQ.addBindValue(studentId);

    if (!parentQ.exec() || !parentQ.next()) {
        QMessageBox::warning(this, "Ошибка", "У этого ученика не найден родитель в системе.");
        return;
    }

    int parentUserId = parentQ.value(0).toInt();

    QSqlQuery q(Database::getDB());
    q.prepare(R"(
        INSERT INTO messages (from_user_id, to_user_id, text, date)
        VALUES (?, ?, ?, ?)
    )");
    q.addBindValue(m_userId);
    q.addBindValue(parentUserId);
    q.addBindValue(text);
    q.addBindValue(QDate::currentDate().toString("yyyy-MM-dd"));

    if (!q.exec()) {
        QMessageBox::warning(this, "Ошибка", "Не удалось отправить сообщение.");
        return;
    }

    statusLabel->setStyleSheet("color: #2E7D32; font-size: 13px;");
    statusLabel->setText("✅ Сообщение отправлено родителям.");
    messageEdit->clear();
}

// Кнопка Выход
void TeacherMainWindow::on_btnLogout_clicked()
{
    LoginWindow *login = new LoginWindow();
    login->show();
    this->close();
}

// === Работа со статус баром ===
// Установка статус бара
void TeacherMainWindow::setupStatusBar()
{
    statusTabLabel = new QLabel("Главная панель");
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
    connect(sessionTimer, &QTimer::timeout, this, &TeacherMainWindow::updateSessionTime);
    sessionTimer->start(1000);
}

// Обновление времени сессии
void TeacherMainWindow::updateSessionTime()
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