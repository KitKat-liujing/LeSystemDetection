/*
网络检测项
*/
#ifndef MAIN_PAGE_FIVE_H
#define MAIN_PAGE_FIVE_H

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
/*测网object*/
class My_Obj_Netspeed: public QObject
{
    Q_OBJECT
public:
    explicit My_Obj_Netspeed();

protected:
    QProcess *proc;
    QString out;
    QTimer *timer;
signals:
    void send_Netspeed(QString str);
protected slots:
    void start_timer();
};
/*udp_tcp object*/
class My_Obj_udp_tcp: public QObject
{
    Q_OBJECT
public:
    explicit My_Obj_udp_tcp();
protected:
    QProcess *proc;
    QString out;
    QTimer *timer;
signals:
    void send_udp_tcp(QString str);
protected slots:
        void start_timer();
};

class My_Obj_Net_Flow: public QObject
{
    Q_OBJECT
public:
    explicit My_Obj_Net_Flow();
protected:
    QProcess *proc;
    QString out;
signals:
    void send_Net_Flow(int n, QString str);
public slots:
    void Net_Flow_wire(QString arg);
    void Net_Flow_wireless(QString arg);
//    void start_timer1(int arg);
//    void start_timer2(int arg);
};

class Main_Page_five : public QWidget
{
    Q_OBJECT
public:
    explicit Main_Page_five(QWidget *parent = 0);

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
    QLabel *net_info;
    QPushButton *re_test_net;
    QPushButton *more_detail_for_net;
    QLabel *line_label_1;
    QTextBrowser *wid_1_show_info;
    /*页面二*/
    void init_widget_2();
    QWidget *widget_2;
    QPushButton *test_1,*test_2,*test_3;
    QTextBrowser *text_broswer,*net_broswer_1,*net_broswer_2,*tcp_broswer;
    QLabel *net_label,*average_label,*line_1,*line_2,*line_3,*label_2_1,*label_2_2,*label_3;
    QLineEdit *edit_1,*edit_2;
    My_Obj_Netspeed *My_Obj_Netspeed_object;//netspeed
    QThread *thread_1;//netspeed
    My_Obj_udp_tcp *My_Obj_udp_tcp_object;//tcp_udp
    QThread *thread_2;//tcp_udp
    My_Obj_Net_Flow *My_Obj_Net_Flow_object;
    QThread *thread_3;
    /*页面三*/
    void init_widget_3();
    QWidget *widget_3;
    QLabel *net_safe_info;
    QPushButton *re_test_safe;
    QPushButton *more_detail_for_safe;
    QLabel *line_label_3;
    QTextBrowser *wid_3_show_info;
    /*页面四*/
    void init_widget_4();
    QWidget *widget_4;
    QLabel *net_info_flow;
    QPushButton *re_test_wired;
    QPushButton *re_test_wireless;
    QLabel *line_label_4;
    QTextBrowser *wid_4_show_wired;
    QTextBrowser *wid_4_show_wireless;

protected:

    bool eventFilter(QObject *obj, QEvent *event);

signals:

protected slots:
/*widget-1*/
    void re_test_net_slots();
    void more_detail_for_net_slots();

/*widget-2*/
    void get_Netspeed(QString str);
    void get_udp_tcp(QString str);
    void test_network();
    void test_1_clicked();
    void test_2_clicked();
    void set_wid_2_text_show(int n, QString str);

/*widget-3*/
    void re_test_safe_slots();
    void more_detail_for_safe_slots();
    void init_bash(int n);

/*widget-4*/
    void show_wire_msg();
    void show_wireless_msg();
public slots:

};

#endif // MAIN_PAGE_FIVE_H
