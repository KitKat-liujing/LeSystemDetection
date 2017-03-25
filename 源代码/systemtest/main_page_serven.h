/*
系统安全检测项
*/
#ifndef MAIN_PAGE_SERVEN_H
#define MAIN_PAGE_SERVEN_H

#include <QWidget>
#include <QStackedWidget>
#include <QListWidget>
#include <QTextBrowser>
#include <QProcess>
#include <QString>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include "input_pwd.h"
#include "common.h"

class main_page_serven : public QWidget
{
    Q_OBJECT
public:
    explicit main_page_serven(QWidget *parent = 0);
    ~main_page_serven();

signals:
private:
    QStackedWidget *stack;
    QWidget *widget_1,*widget_2,*widget_3,*widget_4,*widget_5,*widget_6;
    QListWidget *list;
    QTextBrowser *text_1,*edit_1,*edit_2,*edit_3 ,*broswer_1,*broswer_2;
    QString out;
    QProcess *pro;
    QPushButton *button_1,*button_2;
    QHBoxLayout *layout_1;
    QVBoxLayout *layout_2;
    QLabel *line_0,*line_1,*line_2,*line_3;
    Input_Pwd *input_pwd_widget ;
    void init_widget1(),init_widget2(),init_widget3(),init_widget4(),init_widget5(),init_widget6();
    void show_edit_1();
    //void user_show_1(),user_show_2();
    QTextBrowser *widget4_text,*widget5_text,*widget6_text;

public slots:
private slots:
    void dentry();
    void compare();
    void user_show_1();
    void user_show_2();
    void init_bash(int n);
    //void check_sysstat();
    //第4个界面
    void check1();
    void compare1();
    //void remove1();
    void check2();
    void compare2();
    void check3();
    void compare3();

protected:

    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // MAIN_PAGE_SERVEN_H
