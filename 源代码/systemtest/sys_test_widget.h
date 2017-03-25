/*******
系统检测界面 此界面用线程和进程实现

*********/

#ifndef SYS_TEST_WIDGET_H
#define SYS_TEST_WIDGET_H

#include <QDialog>
#include <QThread>
#include <QPushButton>
#include <QSplitter>
#include <QLabel>
#include <QTextBrowser>
#include <QProgressBar>
#include <QProcess>
#include <QTimer>
#include <QStringList>
#include <show_percent_page.h>
#include "net_speed.h"
/* 一键测试评分object  供线程使用 */
class My_Obj_get_score: public QObject
{
    Q_OBJECT
public:
    explicit My_Obj_get_score();

protected:
    QProcess *proc;
    QProcess *proc_ret;
    QString ret;
    QTimer *timer;
    QStringList qlist;//脚本
    QStringList list_finish;//脚本执行完成需要输出
    QStringList list_unfinish;//脚本正在执行时输出提示信息
    QStringList argus;//c语言脚本第一个参数
    QString setout;
    QString getout;
    double score;
    int n;
signals:
    void set_score(double scores);//发送分值信号
    void set_text_show(QString str);//    发送输出信号
    void set_bar_value(int n);//设置进度条值
    void please_stop();
public slots:
    void start_get_score();//
};

class Sys_Test_Widget: public QDialog
{
    Q_OBJECT

public:
    explicit Sys_Test_Widget(QWidget *parent = 0);
    ~Sys_Test_Widget();

protected:

    QSplitter *main_splitter;
    /*左侧窗口*/
    QWidget *left_widget;

    QProgressBar *progressBar;
    QTextBrowser *text_show;
    QString getout;
    QProcess *proc;
    QPushButton *re_test;

    QSplitter *right_splitter;

    QWidget *right_top_widget;
    QLabel *score_label;

    show_percent_page *right_center_widget;

    Net_Speed *right_bottom_widget;

    My_Obj_get_score *obj_get_score;
    QThread *thread_get_score;

private:
    void initLeft();
    void initRightTop();
    void initRightCenter();
    void initRightBottom();
    void initRight();


protected slots:
//    void set_score(double scores);//发送分值信号
    void set_text_show(QString str);//    发送输出信号
    void set_bar_value(int n);//设置进度条值
    void get_score(double score);
public slots:
    void start_timer();

};


#endif // SYS_TEST_WIDGET_H
