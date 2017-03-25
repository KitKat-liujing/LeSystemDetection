/*
主窗口，用于构建所有窗口
*/
#ifndef MAIN_WIDGET_H
#define MAIN_WIDGET_H

#include <QMainWindow>
#include "drop_shadow_widget.h"
#include <QStackedWidget>
#include <QTimer>
#include <QDateTime>
#include <QAction>
#include <QMenu>
#include <QSystemTrayIcon>
#include "title_widget.h"
#include "boot_start_time.h"
#include "input_pwd.h"
#include "sys_test_widget.h"
#include "buttom_widget.h"
#include "main_page_one.h"
#include "main_page_two.h"
#include "main_page_three.h"
#include "main_page_four.h"
#include "main_page_five.h"
#include "main_page_six.h"
#include "main_page_serven.h"
//#include "main_page_eight.h"
#include "main_menu.h"

class main_widget : public DropShadowWidget
{
    Q_OBJECT

public:
    main_widget(QWidget *parent = 0);
    ~main_widget();

signals:

private slots:
    void turnPage(int current_page);
    void show_start_time();
    void hide_start_time();
    void show_input_pwd_widget();
    void change_skin(QString new_skin_name);
    void go_sys_test_page();
    void show_main_menu();
private:
    QTimer *tmr_show_start_time;
    QTimer *tmr_hide_start_time;
    QTimer *tmr_input_pwd;

    QStackedWidget *stacked_widget;
    TitleWidget *title_widget;
    Main_Page_One *one_widget;
    Main_Page_two *two_widget;
    Main_Page_three *three_widget;
    Main_Page_four *four_widget;
    Main_Page_five *five_widget;
    Main_Page_six *six_widget;
    main_page_serven *serven_widget;
    //main_page_eight *eight_widget;
    Boot_Start_Time *start_time_widget;
    Input_Pwd *input_pwd_widget;

    Sys_Test_Widget *sys_test_widget;
    Buttom_Widget *button_widget;
    QSystemTrayIcon *myTrayIcon;
    QAction *restoreWinAction,*quitAction;
    QMenu *myMenu;
    QString skin_name;//主窗口背景图片的名称
    Main_Menu *main_menu;
    void createMenu();
    void showNormal();
protected:
    virtual void paintEvent(QPaintEvent *event);
};

#endif // MAIN_WIDGET_H
