/*
首页
*/
#ifndef MAIN_PAGE_ONE_H
#define MAIN_PAGE_ONE_H

#include <QWidget>
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
#include "user_msg.h"
#include "net_speed.h"

class Main_Page_One : public QDialog
{
    Q_OBJECT
public:
    explicit Main_Page_One(QWidget *parent = 0);
    ~Main_Page_One();

protected:

    QSplitter *main_splitter;
    /*左侧窗口*/
    QWidget *left_widget;
    QLabel *label;
    QLabel *time_label;
//    QLabel *system_safe_label;
    QPushButton *sys_test_button; //立即体检按钮
    QProcess *pro;
    QString out;
    void home_btime();
    QSplitter *right_splitter;

    User_Msg *right_top_widget;

    show_percent_page *right_center_widget;

    Net_Speed *right_bottom_widget;

private:
    void initLeft();
    void initRightTop();
    void initRightCenter();
    void initRightBottom();
    void initRight();


signals:
        void go_sys_test_page();
public slots:

};

#endif // MAIN_PAGE_ONE_H
