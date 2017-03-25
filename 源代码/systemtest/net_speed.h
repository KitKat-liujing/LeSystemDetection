/*
动态监控网速
*/
#ifndef NET_SPEED_H
#define NET_SPEED_H

#include <QWidget>
#include <QTextBrowser>
#include <QProcess>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStringList>
#include <QThread>
#include <QObject>
#include <QTimer>

class My_Obj_speed_test: public QObject
{
    Q_OBJECT
public:
    explicit My_Obj_speed_test();
protected:
    QProcess *proc;
    QString out;
    QTimer *timer;
signals:
    void set_info(QString str);
protected slots:
        void start_timer();
};

class Net_Speed : public QWidget
{
    Q_OBJECT
public:
    explicit Net_Speed(QWidget *parent = 0);

protected:
    QTextBrowser *show_user_msg;
    My_Obj_speed_test *My_Obj_speed_test_object;
    QThread *my_thread;

signals:

public slots:
    void set_text(QString str);

};

#endif // NET_SPEED_H
