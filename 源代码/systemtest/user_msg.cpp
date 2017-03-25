#include "user_msg.h"
#include <QFont>
#include <QPushButton>
User_Msg::User_Msg(QWidget *parent) :
    QWidget(parent)
{
    show_user_msg = new QTextBrowser();
    QFont ft = this->font();
    ft.setPointSize(16);
    show_user_msg->setFont(ft);
    show_user_msg->setStyleSheet("border-color:white");
    QVBoxLayout main_layout;
    main_layout.addWidget(show_user_msg);
    main_layout.setContentsMargins(1,1,1,1);
    this->setLayout(&main_layout);
    pro = new QProcess();
    out = "";
    QString program = "bash";
    QStringList arguments;
    arguments<<"/usr/bin/home_info/homeinfousr.sh";
    pro->start(program, arguments);
    while(pro->waitForReadyRead())
    {
        out += pro->readAll();
    }
    show_user_msg->setText(out);

}
