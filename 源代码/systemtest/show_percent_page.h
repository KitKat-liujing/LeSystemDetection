/*
cpu 内存检测项，动态刷新
*/
#ifndef SHOW_PERCENT_PAGE_H
#define SHOW_PERCENT_PAGE_H

#include <QWidget>
#include <QProcess>
#include <QGridLayout>
#include <QLabel>
#include <QTimer>
#include <QProgressBar>
#include <QTextBrowser>
#include <QStringList>
#include <QThread>

/*定义object  for thread*/
class Thread_obj: public QObject
{
    Q_OBJECT
public:
    explicit Thread_obj();
protected:
    QProcess *pro;
    QString out;
    QTimer *timer;
    QStringList arguments_cpu;
    QStringList arguments_mem;
    QStringList arguments_top;
signals:
    void change_value_cpu(QString str);//cpu
    void change_value_mem(QString str);//mem
    void change_top_show(QString str);//top 10
protected slots:
    void process_start();
};

class show_percent_page : public QWidget
{
    Q_OBJECT
public:
    explicit show_percent_page(QWidget *parent = 0);

signals:

public slots:

protected slots:
//    void set_percent_value();//定时器超时函数
    /*槽--接收线程的信号用来刷新*/
    void chang_value_cpu(QString str);
    void chang_value_mem(QString str);
    void chang_top_show(QString str);

protected:
    QProgressBar *cpu_percent;
    QProgressBar *mem_percent;
    QLabel *cpu_Label;
    QLabel *mem_Label;
    QLabel *suggest_Label;
    QTextBrowser *show_top_info;
    Thread_obj *my_thread_obj;
};

#endif // SHOW_PERCENT_PAGE_H
