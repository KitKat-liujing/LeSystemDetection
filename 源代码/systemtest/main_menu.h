/*
主菜单
*/
#ifndef MAIN_MENU_H
#define MAIN_MENU_H
#include <QAction>
#include <QWidget>
#include <QMenu>
#include <QUrl>
#include <QLabel>
#include "about_us.h"

class Main_Menu : public QMenu
{
    Q_OBJECT
public:
    explicit Main_Menu(QWidget *parent = 0);
    ~Main_Menu();

signals:
private:
    About_Us *about_us_widget;
    QAction *action_about_us,*action_help_online;
    //void create_menu();
public slots:
private slots:
    void online_consultation();
    void showAboutUs();
};

#endif // MAIN_MENU_H
