#include "show_percent_page.h"
#include <QStringList>
#include <QString>
#include "common.h"

Thread_obj::Thread_obj()
{
    timer = new QTimer();
    pro = new QProcess();
    connect(timer, SIGNAL(timeout()), this, SLOT(process_start()));//超时刷新
    arguments_cpu<<"/usr/bin/flush_percent/cpu_rate.sh";
    arguments_mem<<"/usr/bin/flush_percent/mem_rate.sh";
    arguments_top<<"/usr/bin/flush_percent/cpu-mem.sh";
    /*设置定时器*/
    timer->start(2000);
}

void Thread_obj::process_start()
{
    pro->start("bash", arguments_cpu);
    while( true == pro->waitForFinished() )
    {
        out = pro->readAll().trimmed();
        emit change_value_cpu(out);
    }
    pro->start("bash", arguments_mem);
    while( true == pro->waitForFinished())
    {
        out = pro->readAll().trimmed();
        emit change_value_mem(out);
    }
    pro->start("bash", arguments_top);
    while( true == pro->waitForFinished())
    {
        out = pro->readAll().trimmed();
        emit change_top_show(out);
    }
}

show_percent_page::show_percent_page(QWidget *parent) :
    QWidget(parent)
{
    /*cpu/mem刷新进度条*/
    cpu_percent = new QProgressBar();
    mem_percent = new QProgressBar();
    cpu_percent->setFixedSize(120,20);
    mem_percent->setFixedSize(120,20);
    /*颜色*/
//    cpu_percent->setStyleSheet("QProgressBar::chunk {border-radius: 10px;width: 5px; }");
//    mem_percent->setStyleSheet("QProgressBar::chunk {border-radius: 10px;width: 5px;margin: 0.4px; }");
    cpu_percent->setValue(10);
    mem_percent->setValue(10);
    this->setStyleSheet("QProgressBar{ border: 2px solid grey;border-radius: 5px;}");
    this->setStyleSheet("QProgressBar::chunk{text-align: center;background-color: #1E90FF;width: 20px;}");
    /*cpu_rate.mem_rate.text_browser*/
    cpu_Label = new QLabel();
    mem_Label = new QLabel();
    suggest_Label = new QLabel();
    show_top_info = new QTextBrowser();
    show_top_info->setFixedHeight(300);
 /*字体*/
    QFont suggest_font = this->font();//返回默认应用程序字体
    suggest_font.setPointSize(12);//字体大小
    suggest_font.setBold(true);//加粗
    cpu_Label->setFont(suggest_font);
    mem_Label->setFont(suggest_font);
    suggest_Label->setFont(suggest_font);
    suggest_Label->setFixedWidth(100);
    suggest_font.setPixelSize(12);
    cpu_percent->setFont(suggest_font);
    mem_percent->setFont(suggest_font);
    suggest_font.setPointSize(8);
    show_top_info->setFont(suggest_font);
/*设置文字*/
    cpu_Label->setText(tr("cpu 占用率"));
    mem_Label->setText(tr("内存 占用率"));
    suggest_Label->setText(tr("cpu 内存 监测"));
/*线程*/
    my_thread_obj = new Thread_obj();
    QThread *mythread = new QThread();
    my_thread_obj->moveToThread(mythread);
    mythread->start();
    connect(my_thread_obj, SIGNAL(change_value_cpu(QString)), this, SLOT(chang_value_cpu(QString)));
    connect(my_thread_obj, SIGNAL(change_value_mem(QString)), this, SLOT(chang_value_mem(QString)));
    connect(my_thread_obj, SIGNAL(change_top_show(QString)), this, SLOT(chang_top_show(QString)));
/*布局*/
    QHBoxLayout *cpu_Layout = new QHBoxLayout();
    cpu_Layout->addWidget(cpu_percent);
    cpu_Layout->addStretch();
    cpu_Layout->addWidget(cpu_Label);
    cpu_Layout->setContentsMargins(0,5,5,0);

    QHBoxLayout *mem_Layout = new QHBoxLayout();
    mem_Layout->addWidget(mem_percent);
    mem_Layout->addStretch();
    mem_Layout->addWidget(mem_Label);
    mem_Layout->setContentsMargins(0,5,0,5);

    QVBoxLayout *top_Layout = new QVBoxLayout();
    top_Layout->addLayout(cpu_Layout);
    top_Layout->addSpacing(1);
    top_Layout->addLayout(mem_Layout);

    QVBoxLayout *v_Layout = new QVBoxLayout();
    v_Layout->addLayout(top_Layout);
    v_Layout->addSpacing(5);
    v_Layout->addWidget(suggest_Label,0,Qt::AlignCenter);
    v_Layout->addWidget(show_top_info,0,Qt::AlignCenter);
//    v_Layout->addStretch();
    v_Layout->setContentsMargins(0,0,5,0);

    setLayout(v_Layout);

}


void show_percent_page::chang_value_cpu(QString str)
{

    cpu_percent->setValue(str.toDouble());
}
void show_percent_page::chang_value_mem(QString str)
{
    mem_percent->setValue(str.toDouble());
}

void show_percent_page::chang_top_show(QString str)
{
    show_top_info->setText(str);
}
