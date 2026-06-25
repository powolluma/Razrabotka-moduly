#ifndef TEACHERMAINWINDOW_H
#define TEACHERMAINWINDOW_H
#include <QMainWindow>
#include <QComboBox>
#include <QDateEdit>
#include <QSpinBox>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QElapsedTimer>
class TeacherMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit TeacherMainWindow(QWidget *parent = nullptr);
    void setTeacherName(const QString &name);
    void setUserId(int id);
private slots:
    void onClassChanged(int index);
    void on_btnSetGrade_clicked();
    void on_btnSendMessage_clicked();
    void on_btnLogout_clicked();
    void updateSessionTime();
private:
    void setupUI();
    void applyStyle();
    void setupStatusBar();
    void loadSubjectName();
    void loadClasses();
    void loadStudents();
    int m_userId = 0;
    int m_teacherId = 0;
    QLabel *nameLabel = nullptr;
    QLabel *subjectLabel = nullptr;
    QLabel *welcomeLabel = nullptr;
    QLabel *statusLabel = nullptr;
    QLabel *statusTabLabel = nullptr;
    QLabel *statusTimeLabel = nullptr;
    QComboBox *classCombo = nullptr;
    QComboBox *studentCombo = nullptr;
    QComboBox *quarterCombo = nullptr;
    QDateEdit *dateEdit = nullptr;
    QSpinBox *gradeSpin = nullptr;
    QTextEdit *messageEdit = nullptr;
    QTimer *sessionTimer = nullptr;
    QElapsedTimer sessionElapsed;
};
#endif // TEACHERMAINWINDOW_H