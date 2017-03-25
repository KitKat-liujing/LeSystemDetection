/*
 cpu检测项
*/
#ifndef MAIN_PAGE_TWO_H
#define MAIN_PAGE_TWO_H

#include <QWidget>
#include <QToolButton>
#include <QListWidget>
#include <QStackedWidget>
#include <QTextBrowser>
#include "qprocess.h"
#include "common.h"
#include "input_pwd.h"
#include <QLabel>
#include <QPushButton>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <QThread>
/*thread object for flush cpu msg*/
class My_Obj_Flush_Cpu:public QObject
{
    Q_OBJECT
public:
    explicit My_Obj_Flush_Cpu();

protected:
    QProcess *proc;
    QString out;
    QTimer *timer;
signals:
    void send_cpu_info(QString str);
protected slots:
    void Flush_cpu_info();
};
/*thread object for test cpu*/
class My_Obj_Test_Cpu: public QObject
{
    Q_OBJECT
public:
    explicit My_Obj_Test_Cpu();
protected:
    QProcess *proc;
    QString out;
    QTimer *timer;
signals:
    void send_cpu_info(QString str);
protected slots:
    void start_test_cpu();
};

class Main_Page_two : public QWidget
{
    Q_OBJECT
public:
    explicit Main_Page_two(QWidget *parent = 0);

protected:
    /*列表窗口*/
    void init_list_widget();
    QListWidget *list;
    QStackedWidget *stack;
    QProcess *pro;
    QString out;
    /*密码*/
    Input_Pwd *input_pwd_widget;

    /*页面1*/
    void init_widget_1();
    QWidget *widget_1;
    QLabel *cpu_info_1;
    QPushButton *re_test_cpu_1;
    QLabel *line_label_1;
    QTextBrowser *wid_1_show_info;
    /*页面2*/
    void init_widget_2();
    QWidget *widget_2;
    QLabel *cpu_info_2_1;
    QLabel *cpu_info_2_2;
    QPushButton *re_test_cpu_2;
    QLabel *line_label_2_1;
    QLabel *line_label_2_2;
    QTextBrowser *wid_2_show_info_1;
    QTextBrowser *wid_2_show_info_2;
    /**/
    My_Obj_Flush_Cpu *My_Obj_Flush_Cpu_object;
    QThread *thread_flush_cpu;
    My_Obj_Test_Cpu *My_Obj_Test_Cpu_object;
    QThread *thread_test_cpu;

protected:

    bool eventFilter(QObject *obj, QEvent *event);

protected slots:
    /*widget_1*/
    void re_test_cpu_1_slots();
    /*widget_2*/
//    void re_test_cpu_2_slots();
    void Flush_Cpu_Rate(QString str);//动态刷新cpu信息
    void Set_Test_cpu(QString str);//cpu 刷新检测信息
    /*init_widget_bash*/
    void init_bash(int n);
};

#endif // MAIN_PAGE_TWO_H
