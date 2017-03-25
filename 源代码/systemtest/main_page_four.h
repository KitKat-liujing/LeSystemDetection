/*
磁盘检测项
*/
#ifndef MAIN_PAGE_FOUR_H
#define MAIN_PAGE_FOUR_H

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
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>
#include <QThread>
#include <QTimer>

/*thread object for disk test*/
class My_Obj_Disk_Test: public QObject
{
    Q_OBJECT
public:
    explicit My_Obj_Disk_Test();
protected:
    QProcess *proc;
    QString out;
    QTimer *timer;
signals:
    void set_wid_2_info_1(QString str);
    void exit();
public slots:
        void start_timer();
};
/*thread object for dd test*/
class My_Obj_Dd_Test: public QObject
{
    Q_OBJECT
public:
    explicit My_Obj_Dd_Test();
protected:
    QProcess *proc;
    QString out;
signals:
    void send_result_dd_test(QString str);
public slots:
    void start_test();

};

class Main_Page_four : public QWidget
{
    Q_OBJECT
public:
    explicit Main_Page_four(QWidget *parent = 0);

protected:
/*列表窗口*/
    void init_list_widget();
    QListWidget *list;
    QStackedWidget *stack;
    QProcess *pro;
    QString out;
    /*密码*/
    Input_Pwd *input_pwd_widget;

    /*页面一*/
    void init_widget_1();
    QWidget *widget_1;
    QLabel *disk_info;
    QPushButton *re_test_disk;
    QPushButton *more_detail;
    QLabel *line_label_1;
    QTextBrowser *wid_1_show_info;
    /*页面二*/
    void init_widget_2();
    QWidget *widget_2;
    QPushButton *re_test_disk_perf;
    QPushButton *start_button;
    QTextBrowser *wid_2_show_info_1;
    QTextBrowser *wid_2_show_info_2;
    QTextBrowser *wid_2_show_info_3;
    QLabel *widget_2_label_0;
    QLabel *widget_2_label_1;
    QLabel *tips_widget_2;
    QPushButton *install_widget_2;
    QPushButton *remove_widget_2;
    QPushButton *check_widget_2;
    int times;
    /*页面三*/
    void init_widget_3();
    QWidget *widget_3;
    QLabel *io_info;
    QPushButton *re_test_io;
    QLabel *line_label_3;
    QTextBrowser *wid_3_show_info;
    /*页面四*/
    void init_widget_4();
    QWidget *widget_4;
    QLabel *widget_4_line_label;//line
    QTextBrowser *wid_4_show_info;//title
    QLabel *tips_widget_4;//install??
    QPushButton *install_widget_4; //install_sysstat
    QPushButton *remove_widget_4;//remove_sysstat
    QPushButton *check_widget_4;//iostat_tool
/*线程object*/
    My_Obj_Disk_Test *thread_test_dd;
    QThread *my_thread;
    My_Obj_Dd_Test *My_Obj_Dd_Test_object;
    QThread *my_thread_2;
protected:

    bool eventFilter(QObject *obj, QEvent *event);

signals:

protected slots:
    /*widget-1*/
    void re_test_disk_slots();
    void more_detail_slots();
    /*widget-2*/
    void start_timer();
    void re_test_disk_perf_slots();
    void judge_hddtemp();
    void install_hddtemp();
    void remove_hddtemp();
    void check_hddtemp();
    void start_button_slots();
    /*widget-3*/
    void re_test_io_slots();
    /*获取页面切换信号  设置页面初始化信息*/
    void init_bash(int n);
    /*接受线程thread_dd_test的返回值*/
    void set_wid_2_info_1(QString str);
    void set_wid_2_info_3(QString str);
    /*widget-4*/
    void init_widget_4_bash();
    void install_sysstat();
    void remove_sysstat();
    void check_sysstat();
public slots:

};
#endif // MAIN_PAGE_FOUR_H
