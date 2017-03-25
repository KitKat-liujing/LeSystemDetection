/*
显示用户名信息
*/
#ifndef USER_MSG_H
#define USER_MSG_H

#include <QWidget>
#include <QTextBrowser>
#include <QProcess>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStringList>

class User_Msg : public QWidget
{
    Q_OBJECT
public:
    explicit User_Msg(QWidget *parent = 0);

protected:
    QTextBrowser *show_user_msg;//msg textbrowser
    QProcess *pro;//process
    QString out;//get msg from StandardOutput

signals:

public slots:

};

#endif // USER_MSG_H
