/*
系统检测项
*/
#ifndef MAIN_PAGE_SIX_H
#define MAIN_PAGE_SIX_H

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

class Main_Page_six : public QWidget
{
    Q_OBJECT
public:
    explicit Main_Page_six(QWidget *parent = 0);

protected:
/*列表窗口*/
    void init_list_widget();
    QListWidget *list;
    QStackedWidget *stack;
    /*密码*/
    Input_Pwd *input_pwd_widget;
    QProcess *pro;
    QString out;
    /*页面一*/
    void init_widget_1();
    QWidget *widget_1;
    QLabel *os_info;
    QPushButton *re_test_os;
    QLabel *line_label_1;
    QTextBrowser *wid_1_show_info;
    /*页面二*/
    void init_widget_2();
    QWidget *widget_2;
    QLabel *hardware_info;
    QPushButton *re_test_hard;
    QPushButton *more_detail_hard;
    QLabel *line_label_2;
    QTextBrowser *wid_2_show_info;
    /*页面三*/
    void init_widget_3();
    QWidget *widget_3;
    QLabel *os_run_info;
    QPushButton *re_test_os_run;
    QPushButton *more_detail_os_run;
    QLabel *line_label_3;
    QTextBrowser *wid_3_show_info;
protected:
    bool eventFilter(QObject *obj, QEvent *event);

signals:

protected slots:
    /*widget-1*/
    void re_test_os_slots();
    /*widget-2*/
    void re_test_hard_slots();
    void more_detail_hard_slots();
    /*widget-3*/
    void re_test_os_run_slots();
    void more_detail_os_run_slots();
    /*init_widget_bash*/
    void init_widget_bash(int n);
public slots:

};

#endif // MAIN_PAGE_SIX_H
