#include "main_menu.h"
#include <QDesktopServices>
#include <QVBoxLayout>
#include <QNetworkProxy>
#include <QMenu>
#include <QAction>

Main_Menu::Main_Menu(QWidget *parent) : QMenu(parent)
{
    this->setObjectName("menu");
    about_us_widget = new About_Us;

    action_help_online = new QAction(this);
    action_help_online->setText("网上咨询");
    action_about_us = new QAction(this);
    action_about_us->setText("关于我们");

//    this->addSeparator();
    this->addAction(action_help_online);
    this->addSeparator();
    this->addAction(action_about_us);

//    connect(action_setting,SIGNAL(triggered()),this,SLOT(system_tips()));
    connect(action_help_online,SIGNAL(triggered()),this,SLOT(online_consultation()));
    connect(action_about_us,SIGNAL(triggered()),this,SLOT(showAboutUs()));

}

Main_Menu::~Main_Menu()
{

}
void Main_Menu::online_consultation()
{
    QString page;
     page = QString("http://linux.cn/article-3684-1.html");
     QUrl url(page);
     QDesktopServices::openUrl(url);
}
void Main_Menu::showAboutUs()
{
    about_us_widget->show();
}
