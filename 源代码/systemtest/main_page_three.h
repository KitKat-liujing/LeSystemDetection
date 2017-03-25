/*
 内存检测项
 */
#ifndef MAIN_PAGE_THREE_H
#define MAIN_PAGE_THREE_H

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

class Main_Page_three : public QWidget
{
    Q_OBJECT
public:
    explicit Main_Page_three(QWidget *parent = 0);

protected:
/*列表窗口*/
    QListWidget *list;
    QStackedWidget *stack;
/*布局窗口*/
    QWidget *work_window;
    QPushButton *re_test;
    QLabel *test_options;
    QLabel *line_label;
    QTextBrowser *show_msg;
/*密码弹窗*/
    Input_Pwd *Input_Pwd_Widget;

    /*进程*/
    QProcess *pro;
    QString out;
    int current_bash;//标志位(当前页面)

protected:

    bool eventFilter(QObject *obj, QEvent *event);

signals:

protected slots:
    void change_widget_cfg(int n);
    void show_msg_to_browser();
    void flush_msg();
public slots:

};

#endif // MAIN_PAGE_THREE_H
