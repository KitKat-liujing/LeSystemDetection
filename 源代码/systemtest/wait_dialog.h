#ifndef WAIT_DIALOG_H
#define WAIT_DIALOG_H
#include <QDialog>
#include <QProgressBar>
#include <QTimer>

class Waiting_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Waiting_Dialog(QWidget *parent = 0);
    ~Waiting_Dialog();

private:
    int m_CurrentValue;
    int m_UpdateInterval;
    int m_MaxValue;
    QTimer *m_Timer;
    QProgressBar *m_ProgressBar;

public:
    void Start(int interval, int maxValue);
    void Stop();

private slots:
    void UpdateSlot();
};


#endif // WAIT_DIALOG_H
