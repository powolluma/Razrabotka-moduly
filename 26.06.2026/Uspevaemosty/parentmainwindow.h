#pragma once
#include <QMainWindow>
#include <QTimer>
#include <QElapsedTimer>
class ParentMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit ParentMainWindow(QWidget *parent = nullptr);
    void setParentName(const QString &name);
    void setUserId(int id);
private slots:
    void on_btnGrades_clicked();
    void on_btnSchedule_clicked();
    void on_btnAverage_clicked();
    void on_btnQuarterGrades_clicked();
    void on_btnMessages_clicked();
    void on_btnLogout_clicked();
    void updateSessionTime();
private:
    void setupUI();
    void applyStyle();
    void setupStatusBar();
    bool resolveStudentUserId(int &outUserId);
    int m_userId;
    int m_studentId;
    QWidget *centralWidget;
    class QLabel *nameLabel;
    class QLabel *classLabel;
    class QLabel *welcomeLabel;
    class QLabel *statusTabLabel;
    class QLabel *statusTimeLabel;
    QTimer *sessionTimer;
    QElapsedTimer sessionElapsed;
};