#pragma once
#include <QFileInfo>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QStringList>

class Database
{
public:
    // Получение единственного экземпляра базы данных
    static Database& instance()
    {
        static Database db;
        return db;
    }

    // Инициализация базы данных
    bool init(const QString& path = "school.db")
    {
        // Если соединение уже существует,
        // повторно создавать его не нужно
        if (QSqlDatabase::contains("JOURNAL_DB"))
            return true;

        // Создаём соединение SQLite
        QSqlDatabase db =
            QSqlDatabase::addDatabase(
                "QSQLITE",
                "JOURNAL_DB"
                );

        db.setDatabaseName(path);

        // Проверяем успешность открытия
        if (!db.open())
        {
            qDebug()
            << "Ошибка открытия БД:"
            << db.lastError().text();

            return false;
        }
        // Создаём таблицы (без тестовых INSERT-ов внутри)
        createTables();

        // Заполняем тестовыми данными (один раз)
        seedData();
        return true;
    }

    // Получение активного соединения
    static QSqlDatabase getDB()
    {
        return QSqlDatabase::database("JOURNAL_DB");
    }

private:

    Database() = default;

    // Выполнение SQL-запроса с выводом ошибок
    bool execQuery(
        QSqlQuery& q,
        const QString& sql)
    {
        if (!q.exec(sql))
        {
            qDebug() << "SQL ERROR:";
            qDebug() << sql;
            qDebug() << q.lastError().text();

            return false;
        }

        return true;
    }

    // Создание таблиц базы данных
    void createTables()
    {
        QSqlQuery q(getDB());

        // Таблица пользователей
        execQuery(q, R"(
            CREATE TABLE IF NOT EXISTS users(
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                login TEXT UNIQUE NOT NULL,
                password TEXT NOT NULL,
                role INTEGER NOT NULL,
                full_name TEXT NOT NULL
            )
        )");

        // Таблица классов
        execQuery(q, R"(
            CREATE TABLE IF NOT EXISTS classes(
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                name TEXT NOT NULL
            )
        )");

        // Таблица учеников
        execQuery(q, R"(
            CREATE TABLE IF NOT EXISTS students(
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                user_id INTEGER NOT NULL,
                class_id INTEGER NOT NULL,

                FOREIGN KEY(user_id)
                    REFERENCES users(id),

                FOREIGN KEY(class_id)
                    REFERENCES classes(id)
            )
        )");

        // Таблица учителей
        execQuery(q, R"(
            CREATE TABLE IF NOT EXISTS teachers(
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                user_id INTEGER NOT NULL,

                FOREIGN KEY(user_id)
                    REFERENCES users(id)
            )
        )");

        // Таблица родителей
        execQuery(q, R"(
            CREATE TABLE IF NOT EXISTS parents(
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                user_id INTEGER NOT NULL,
                student_id INTEGER NOT NULL,

                FOREIGN KEY(user_id)
                    REFERENCES users(id),

                FOREIGN KEY(student_id)
                    REFERENCES students(id)
            )
        )");

        // Таблица предметов
        execQuery(q, R"(
            CREATE TABLE IF NOT EXISTS subjects(
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                name TEXT NOT NULL
            )
        )");

        // Связь учителей, предметов и классов
        execQuery(q, R"(
            CREATE TABLE IF NOT EXISTS teacher_subjects(
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                teacher_id INTEGER NOT NULL,
                subject_id INTEGER NOT NULL,
                class_id INTEGER NOT NULL,

                FOREIGN KEY(teacher_id)
                    REFERENCES teachers(id),

                FOREIGN KEY(subject_id)
                    REFERENCES subjects(id),

                FOREIGN KEY(class_id)
                    REFERENCES classes(id)
            )
        )");

        // Таблица расписания
        execQuery(q, R"(
            CREATE TABLE IF NOT EXISTS schedule(
                id INTEGER PRIMARY KEY AUTOINCREMENT,

                class_id INTEGER NOT NULL,
                subject_id INTEGER NOT NULL,
                teacher_id INTEGER NOT NULL,

                day_of_week INTEGER NOT NULL,
                lesson_number INTEGER NOT NULL,

                start_time TEXT NOT NULL,
                end_time TEXT NOT NULL,

                FOREIGN KEY(class_id) REFERENCES classes(id),
                FOREIGN KEY(subject_id) REFERENCES subjects(id),
                FOREIGN KEY(teacher_id) REFERENCES teachers(id)
            )
        )");

        // Таблица оценок
        execQuery(q, R"(
            CREATE TABLE IF NOT EXISTS grades(
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                student_id INTEGER NOT NULL,
                subject_id INTEGER NOT NULL,
                grade INTEGER NOT NULL,
                date TEXT NOT NULL,
                quarter INTEGER NOT NULL,

                FOREIGN KEY(student_id) REFERENCES students(id),
                FOREIGN KEY(subject_id) REFERENCES subjects(id)
            )
        )");

        // Таблица сообщений (родителям)
        execQuery(q, R"(
            CREATE TABLE IF NOT EXISTS messages(
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                from_user_id INTEGER NOT NULL,
                to_user_id INTEGER NOT NULL,
                text TEXT NOT NULL,
                date TEXT NOT NULL,

                FOREIGN KEY(from_user_id) REFERENCES users(id),
                FOREIGN KEY(to_user_id) REFERENCES users(id)
            )
        )");
    }

    // Заполнение базы данными
    void seedData()
    {
        QSqlQuery q(getDB());

        q.exec("SELECT COUNT(*) FROM users");

        if (q.next() && q.value(0).toInt() > 0)
        {
            return;
        }

        // КЛАССЫ
        q.exec("INSERT INTO classes(name) VALUES('10 А')");
        q.exec("INSERT INTO classes(name) VALUES('4 Я')");

        // ПРЕДМЕТЫ
        QStringList subjects =
            {
                "Математика",        // 1
                "Физика",            // 2
                "История",           // 3
                "Русский язык",      // 4
                "Химия",             // 5
                "Биология",          // 6
                "Английский язык",   // 7
                "Литература"         // 8
            };

        for (const QString& subject : subjects)
        {
            QSqlQuery ins(getDB());
            ins.prepare("INSERT INTO subjects(name) VALUES(?)");
            ins.addBindValue(subject);
            ins.exec();
        }

        // ПОЛЬЗОВАТЕЛИ
        // Учителя
        q.exec(
            "INSERT INTO users(login,password,role,full_name)"
            " VALUES('смирнов','123',2,'Смирнов Сергей Сергеевич')"
            );
        q.exec(
            "INSERT INTO users(login,password,role,full_name)"
            " VALUES('петров','123',2,'Петров Алексей Викторович')"
            );

        // Ученики
        q.exec(
            "INSERT INTO users(login,password,role,full_name)"
            " VALUES('иванов','123',0,'Иванов Иван')"
            );
        q.exec(
            "INSERT INTO users(login,password,role,full_name)"
            " VALUES('сидоров','123',0,'Сидоров Максим')"
            );

        // Родители
        q.exec(
            "INSERT INTO users(login,password,role,full_name)"
            " VALUES('мария','123',1,'Иванова Мария')"
            );
        q.exec(
            "INSERT INTO users(login,password,role,full_name)"
            " VALUES('ольга','123',1,'Сидорова Ольга')"
            );

        // Ученики
        q.exec("INSERT INTO students(user_id,class_id) VALUES(3,1)");
        q.exec("INSERT INTO students(user_id,class_id) VALUES(4,2)");

        // Учителя
        q.exec("INSERT INTO teachers(user_id) VALUES(1)");
        q.exec("INSERT INTO teachers(user_id) VALUES(2)");

        // Родители
        q.exec("INSERT INTO parents(user_id,student_id) VALUES(5,1)");
        q.exec("INSERT INTO parents(user_id,student_id) VALUES(6,2)");

        // СВЯЗИ УЧИТЕЛЕЙ С ПРЕДМЕТАМИ И КЛАССАМИ
        // Смирнов Математика в 10А и 4Я
        q.exec(
            "INSERT INTO teacher_subjects(teacher_id,subject_id,class_id)"
            " VALUES(1,1,1)"
            );
        q.exec(
            "INSERT INTO teacher_subjects(teacher_id,subject_id,class_id)"
            " VALUES(1,1,2)"
            );

        // Петров Физика в 10А
        q.exec(
            "INSERT INTO teacher_subjects(teacher_id,subject_id,class_id)"
            " VALUES(2,2,1)"
            );

        // РАСПИСАНИЕ 10 А
        q.exec(R"(
            INSERT INTO schedule
            (class_id, subject_id, teacher_id, day_of_week, lesson_number, start_time, end_time)
            VALUES
            (1, 1, 1, 1, 1, '08:00', '08:45'),
            (1, 2, 2, 1, 2, '08:55', '09:40'),
            (1, 3, 1, 1, 3, '09:50', '10:35'),
            (1, 4, 1, 1, 4, '10:55', '11:40'),

            (1, 4, 1, 2, 1, '08:00', '08:45'),
            (1, 5, 1, 2, 2, '08:55', '09:40'),
            (1, 1, 1, 2, 3, '09:50', '10:35'),
            (1, 6, 1, 2, 4, '10:55', '11:40'),

            (1, 2, 2, 3, 1, '08:00', '08:45'),
            (1, 1, 1, 3, 2, '08:55', '09:40'),
            (1, 8, 1, 3, 3, '09:50', '10:35'),

            (1, 1, 1, 4, 1, '08:00', '08:45'),
            (1, 7, 1, 4, 2, '08:55', '09:40'),
            (1, 4, 1, 4, 3, '09:50', '10:35'),

            (1, 6, 1, 5, 1, '08:00', '08:45'),
            (1, 2, 2, 5, 2, '08:55', '09:40'),
            (1, 1, 1, 5, 3, '09:50', '10:35')
        )");

        // РАСПИСАНИЕ
        q.exec(R"(
            INSERT INTO schedule
            (class_id, subject_id, teacher_id, day_of_week, lesson_number, start_time, end_time)
            VALUES
            (2, 1, 1, 1, 1, '08:00', '08:45'),
            (2, 6, 1, 1, 2, '08:55', '09:40'),

            (2, 7, 1, 2, 1, '08:00', '08:45'),
            (2, 8, 1, 2, 2, '08:55', '09:40'),

            (2, 1, 1, 3, 1, '08:00', '08:45'),
            (2, 4, 1, 3, 2, '08:55', '09:40')
        )");

        // ОЦЕНКИ (grades)
        q.exec(R"(
            INSERT INTO grades
            (student_id, subject_id, grade, date, quarter)
            VALUES
            (1, 1, 5, '2026-01-10', 1),
            (1, 1, 4, '2026-01-12', 1),
            (1, 2, 5, '2026-01-13', 1),
            (1, 3, 3, '2026-01-14', 1),
            (1, 4, 4, '2026-01-15', 1),

            (2, 1, 4, '2026-01-10', 1),
            (2, 2, 3, '2026-01-11', 1),
            (2, 3, 5, '2026-01-12', 1),
            (2, 4, 4, '2026-01-13', 1),
            (2, 5, 5, '2026-01-14', 1),

            (1, 5, 5, '2026-02-01', 2),
            (1, 6, 4, '2026-02-02', 2),
            (1, 7, 3, '2026-02-03', 2),

            (2, 6, 5, '2026-02-01', 2),
            (2, 7, 4, '2026-02-02', 2),
            (2, 8, 5, '2026-02-03', 2)
        )");

        // СООБЩЕНИЯ РОДИТЕЛЯМ
        q.exec(R"(
            INSERT INTO messages
            (from_user_id, to_user_id, text, date)
            VALUES
            (1, 5, 'Не нравится С++', '2026-01-15'),
            (2, 6, 'Нормально ввел', '2026-02-03')
        )");
    }
};