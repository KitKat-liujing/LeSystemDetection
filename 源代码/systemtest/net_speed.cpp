#include "net_speed.h"

My_Obj_speed_test::My_Obj_speed_test()
{
        out = "";
        proc = new QProcess();
        timer = new QTimer();
        connect(timer, SIGNAL(timeout()), this, SLOT(start_timer()));
        timer->start(500);
}

void My_Obj_speed_test::start_timer()
{
    QString program = "bash";
    QStringList arguments_1,arguments_2;
    out = "";
    arguments_1<<"/usr/bin/home_info/ethnetspeedhome.sh";
    arguments_2<<"/usr/bin/home_info/wlannetspeedhome.sh";
    proc->start(program, arguments_1);
    if(!proc->waitForStarted())
    {
        return;
    }
    while(!proc->waitForFinished(0))
    {
            out += proc->readAll();
    }
    proc->start(program, arguments_2);
    if(!proc->waitForStarted())
    {
        return;
    }
    while(!proc->waitForFinished(0))
    {
            out += proc->readAll();
    }
    emit set_info(out);
}

Net_Speed::Net_Speed(QWidget *parent) :
    QWidget(parent)
{
    show_user_msg = new QTextBrowser();
    QFont ft = this->font();
    ft.setPointSize(9);
    show_user_msg->setFont(ft);
    show_user_msg->setStyleSheet("border-color:white");

    QHBoxLayout main_layout;
    main_layout.addWidget(show_user_msg);
    main_layout.setContentsMargins(1,1,1,1);
    this->setLayout(&main_layout);

    My_Obj_speed_test_object = new My_Obj_speed_test();
    my_thread = new QThread();
    My_Obj_speed_test_object->moveToThread(my_thread);
    connect(My_Obj_speed_test_object, SIGNAL(set_info(QString)), this, SLOT(set_text(QString)));
    my_thread->start();

}

void Net_Speed::set_text(QString str)
{
    show_user_msg->setText(str);
}
