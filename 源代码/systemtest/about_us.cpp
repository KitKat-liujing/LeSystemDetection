#include "about_us.h"
#include "push_button.h"
#include "common.h"
#include <QFont>
#include <QVBoxLayout>

About_Us::About_Us(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(520,290);
    this->setGeometry(400,400,400,400);
    this->setWindowTitle("关于Le测评");
    //this->setContentsMargins(170,170,170,170);
    QVBoxLayout *layout = new QVBoxLayout();

    QFont ft;
    ft.setPointSize(18);
    ft.setBold(true);
    content = new QLabel("LE乐测评系统监测");
    content->setFont(ft);

    QFont ft1;
    ft1.setPointSize(11);
    ft1.setBold(true);
    //content = new QLabel("Linux evaluation 软件是一款集中测试，评估于一体的系统性能测试软件，快来感受一下吧！");
    lastly = new QLabel("lastly:2014-1-8");
    lastly->setFont(ft1);



    version = new QLabel("version:1.0.0.0");
    version->setFont(ft1);

    chmod = new QLabel("copyright Linux Evaluation.All rights Reserved.");
    chmod->setFont(ft1);


    layout->addWidget(content);
    layout->addWidget(lastly);
    layout->addWidget(version);
    layout->addWidget(chmod);
    layout->addStretch();
    layout->setContentsMargins(10,0,5,0);
    setLayout(layout);
}

About_Us::~About_Us()
{

}
