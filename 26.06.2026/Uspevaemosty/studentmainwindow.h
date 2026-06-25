#pragma once
#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include <QElapsedTimer>
class StudentMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit StudentMainWindow(QWidget *parent = nullptr);
    ~StudentMainWindow();
    void setStudentName(const QString &name);
    void setUserId(int id);
private slots:
    void on_sideButton_clicked();
    void on_btnSchedule_clicked();
    void on_btnAverage_clicked();
    void on_btnQuarterGrades_clicked();
    void on_btnLogout_clicked();
    void updateSessionTime();
private:
    void setupUI();
    void applyStyle();
    void setupStatusBar();
    int m_userId;
    QLabel *nameLabel;
    QLabel *classLabel;
    QLabel *welcomeLabel;
    QLabel *statusTabLabel;
    QLabel *statusTimeLabel;
    QTimer *sessionTimer;
    QElapsedTimer sessionElapsed;
};