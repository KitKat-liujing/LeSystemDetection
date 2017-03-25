/*
显示开机时间项
*/

#ifndef BOOT_START_TIME_H
#define BOOT_START_TIME_H

#include "drop_shadow_widget.h"
#include <QLabel>
#include <QString>
#include <QProcess>
#include <QTextBrowser>

class Boot_Start_Time : public DropShadowWidget
{
    Q_OBJECT

public:
    explicit Boot_Start_Time(QWidget *parent = 0);
    ~Boot_Start_Time();

protected:
    QPushButton *close_button;
    QTextBrowser *show_msg;
    QString skin_name;
    QProcess *pro;
    QString out;

     virtual void paintEvent(QPaintEvent *event);

public slots:
//    void close_myself();
};


#endif // BOOT_START_TIME_H
