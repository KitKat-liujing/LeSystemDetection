/*
标题栏
*/
#ifndef TITLE_WIDGET_H
#define TITLE_WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSignalMapper>
#include "tool_button.h"
#include "push_button.h"

class TitleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TitleWidget(QWidget *parent = 0);
    ~TitleWidget();

signals:
    void turnPage(int current_page);//页码 标号
    void change_skin(QString new_skin_name);//皮肤
    void close_window();//关闭程序
    void hide_window();//(隐藏)最小化
    void show_main_menu();//显示主菜单

public slots:
    void turnPage(QString current_page);
    void change_skin();

private:
    QLabel *version_title; //标题
    PushButton *skin_button; //换肤
    PushButton *main_menu_button; //主菜单
    PushButton *min_button; //最小化
    PushButton *close_button; //关闭

    QLabel *sys_test_logo;  //logo
    QLabel *sys_team;//team name
    QLabel *sys_test;  //系统检测

    QList<ToolButton *> button_list;//QList 设置按钮
};

#endif // TITLE_WIDGET_H
