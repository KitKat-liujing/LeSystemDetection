/*******
系统检测界面 此界面用线程和进程实现

*********/

#include "sys_test_widget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDesktopWidget>
#include <QApplication>
#include <QPainter>
#include <QtTest/QtTest>
#include <QMovie>
#include "common.h"
#include "get_point.h"

My_Obj_get_score::My_Obj_get_score()
{
//    timer = new QTimer();
    proc = new QProcess();
    /*qlist一键测评要执行的脚本*/
    qlist<<"/usr/bin/sys_test/arp_secure.sh"<<"/usr/bin/sys_test/checkdisk.sh"<<"/usr/bin/sys_test/cpu_hyper.sh"<<"/usr/bin/sys_test/cpu_iowait.sh"
           <<"/usr/bin/sys_test/cpu_run_threads.sh"<<"/usr/bin/sys_test/cpu_sys_rate.sh"<<"/usr/bin/sys_test/cpu_user_rate.sh"<<"/usr/bin/sys_test/cpu_virtual.sh"
           <<"/usr/bin/sys_test/earntime.sh"<<"/usr/bin/sys_test/firefox_cookies.sh"<<"/usr/bin/sys_test/google_cookies.sh"<<"/usr/bin/sys_test/google_history.sh"
          <<"/usr/bin/sys_test/init_arp.sh"<<"/usr/bin/sys_test/io_await.sh"<<"/usr/bin/sys_test/io_reqnum.sh"<<"/usr/bin/sys_test/io_svctm.sh"<<"/usr/bin/sys_test/io_util.sh"
          <<"/usr/bin/sys_test/junk_files.sh"<<"/usr/bin/sys_test/mem_user.sh"<<"/usr/bin/sys_test/recent_used.sh";

    /*脚本执行完成需要输出*/
    list_finish<<"被ARP攻击的风险率:"<<"普通磁盘(不包括根分区):"<<"CPU是否支持超线程:"<<"CPU的IO等待占用率:"
                    <<"平均每个CPU可运行队列的线程数:"<<"CPU的系统占用率:"<<"CPU的用户占用率:"<<"CPU是否支持虚拟化:"
                    <<"开机启动时间:"<<"火狐跟踪cookies:"<<"谷歌跟踪cookies:"<<"谷歌URL历史跟踪记录:"
                    <<"ARP防护开机自启动:"<<"平均IO响应时间:"<<"IO队列中的请求数:"<<"平均每次设备IO操作的服务时间:"<<"一秒中有百分之多少的时间用于IO操作:"
                    <<"磁盘垃圾文件:"<<"应用程序可用内存占用率:"<<"最近使用文档跟踪记录:";



    /*脚本正在执行时输出提示信息*/
    list_unfinish<<"正在测评被ARP攻击的风险率..."<<"正在检测普通磁盘(不包括根分区)是否正常可用..."<<"正在检测CPU是否支持超线程..."<<"正在检测CPU:IO等待占用率..."
                         <<"正在检测平均每个CPU可运行队列的线程数..."<<"正在检测CPU:系统占用率..."<<"正在检测CPU:用户占用率..."<<"正在检测CPU是否支持虚拟化..."
                         <<"正在检测开机启动时间..."<<"正在检测是否有火狐跟踪cookies..."<<"正在检测是否有谷歌跟踪cookies..."<<"正在检测是否有谷歌URL历史跟踪记录..."
                         <<"正在检测ARP防护是否已开机自启动..."<<"正在测试平均IO响应时间..."<<"正在检测IO队列中的请求数..."<<"正在检测平均每次设备IO操作的服务时间..."<<"正在检测一秒中有百分之多少的时间用于IO操作..."
                         <<"正在检测磁盘垃圾文件是否过大..."<<"正在检测应用程序可用内存占用率..."<<"正在检测是否有最近使用文档跟踪记录...";


    /*传递给c语言脚本的第一个参数*/
    argus<<"netarp"<<"iocheck"<<"cpuhyper"<<"cpuiowait"
              <<"cputhreads"<<"cpusys"<<"cpuuser"<<"cpuvirtual"
              <<"starttime"<<"netfirefox"<<"netgoogle"<<"nethistory"
              <<"netinitarp"<<"ioresponse"<<"iorequest"<<"ioopt"<<"ioutil"
              <<"iojunk"<<"memuser"<<"recentused";

    score = 100;
    n = 0;
//    connect(timer, SIGNAL(timeout()), this, SLOT(start_get_score()));
//    timer->start(100);
}
void My_Obj_get_score::start_get_score()
{
//    if(timer->isActive())//停止定时器
//        timer->stop();

    if( n < qlist.size() )
        emit set_text_show(setout + list_unfinish.at(n));
    if( n >= qlist.size())//体检结束,发送信号终止线程
    {
        n = 0;
        emit please_stop(); //发送终止信号
        return;
    }
    proc = new QProcess();
    QStringList arguments;
    arguments<<qlist.at(n);
    proc->start("bash", arguments);
    while( true == proc->waitForFinished())
    {
        getout = proc->readAll().trimmed();
        QByteArray ag1 = argus.at(n).toLatin1();
        double ag2 = getout.toDouble();
        score -= get_point(ag1.data(), &ag2);//总分减去计算所得分数
        emit set_score(score);

    }
    /* ***/
    proc_ret = new QProcess();
    ret = "";
    QStringList arg_ret;
    arg_ret<<"/usr/bin/sys_test_result/show_result.sh"<<argus.at(n)<<getout;
    proc_ret->start("bash", arg_ret);
    while(true == proc_ret->waitForFinished())
    {
        ret = proc_ret->readAll();
    }

    /* ***/
    setout += (list_finish.at(n) + "    " + ret);
    setout += "\n";
    if( n == qlist.size()-1 )//设置文本输出
        emit set_text_show(setout);
    emit set_bar_value(n+1);//设置进度条值
    n++;
    if(n < qlist.size() )
    {
        this->start_get_score();
    }else{
        n = 0;
        score = 100;
        setout = "";
        return;
    }
}

Sys_Test_Widget::Sys_Test_Widget(QWidget *parent) :
    QDialog(parent)
{
    this->initLeft();
    this->initRightTop();
    this->initRightCenter();
    this->initRightBottom();
    this->initRight();

    progressBar->setRange(0,20);// 设置进度条上下限值(0-脚本长度)
/*线程*/
    obj_get_score = new My_Obj_get_score();
    thread_get_score = new QThread();
    thread_get_score->start();
    obj_get_score->moveToThread(thread_get_score);

    connect(obj_get_score, SIGNAL(set_bar_value(int)), this, SLOT(set_bar_value(int)));
    connect(obj_get_score, SIGNAL(set_text_show(QString)), this,SLOT(set_text_show(QString)));
//    connect(obj_get_score, SIGNAL(please_stop()), thread_get_score, SLOT(terminate()));
    connect(obj_get_score, SIGNAL(set_score(double)), this, SLOT(get_score(double)));
    connect(re_test, SIGNAL(clicked()), obj_get_score, SLOT(start_get_score()));

    main_splitter = new QSplitter();
    main_splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);//可自行增大和收缩
    main_splitter->setOrientation(Qt::Horizontal);//Qt::Vertical and Qt::Horizontal   qspliter的取向
    main_splitter->setHandleWidth(4); //设置分界线的宽度
    main_splitter->setStyleSheet("QSplitter::handle{background:lightgray;}");

    /* 右分屏的属性设置 */
    right_splitter->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    right_splitter->setOrientation(Qt::Vertical);
    right_splitter->setHandleWidth(1);
/*   加载widget  */
    right_top_widget->setFixedSize(250, 80);
    right_center_widget->setFixedSize(250, 340);
    right_bottom_widget->setFixedSize(250, 50);
    right_splitter->addWidget(right_top_widget);
    right_splitter->addWidget(right_center_widget);
    right_splitter->addWidget(right_bottom_widget);

    main_splitter->addWidget(left_widget);
    main_splitter->addWidget(right_splitter);

    //禁止拖动
    for(int i = 0; i<right_splitter->count();i++)
    {
        QSplitterHandle *handle = right_splitter->handle(i);
        handle->setEnabled(false);
    }

    for(int i = 0; i<main_splitter->count();i++)
    {
        QSplitterHandle *handle = main_splitter->handle(i);
        handle->setEnabled(false);
    }

    QHBoxLayout *V_Layout = new QHBoxLayout();
    V_Layout->addWidget(main_splitter);
    V_Layout->setSpacing(0);//空隙
    V_Layout->setContentsMargins(0, 0, 0, 0);/*这是设置一个元素所有外边距的宽度，
                                                                                    或者设置各边上外边距的宽度 */

    this->setLayout(V_Layout);//将V_Layout设置为当前widget的布局

    this->setStyleSheet("QTextBrowser{background-color: #eaeaea; border:1px solid grey; border-radius: 8px;}");
    this->setAutoFillBackground(true);

}

Sys_Test_Widget::~Sys_Test_Widget()
{
}

void Sys_Test_Widget::initLeft()
{
    left_widget = new QWidget();
    left_widget->resize(650, 500);
/*一键检测*/
    progressBar = new QProgressBar();
    progressBar->setFixedSize(520,40);
    progressBar->setStyleSheet("QProgressBar::chunk {border-radius:20px;background-color: #1E90FF;width: 5px;margin: 0.4px; }");
    text_show = new QTextBrowser();
    text_show->setFixedSize(630,400);
    re_test = new QPushButton();
    re_test->setFixedSize(80, 40);
    re_test->setText(tr("重新检测"));
//    getout = "";
//    setout = "";
    QHBoxLayout *H_Layout = new QHBoxLayout();
    H_Layout->addWidget(progressBar);
    H_Layout->addStretch();
    H_Layout->addWidget(re_test);
    H_Layout->setContentsMargins(5, 0, 5, 0);
    QVBoxLayout *V_Layout = new QVBoxLayout();
    V_Layout->addLayout(H_Layout);
    V_Layout->addSpacing(10);
    V_Layout->addWidget(text_show, 0, Qt::AlignCenter);
    V_Layout->setContentsMargins(10, 20, 10, 5);
    V_Layout->addStretch();

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addLayout(V_Layout);
    main_layout->setContentsMargins(0,0,0,0);

    left_widget->setLayout(main_layout);

}

void Sys_Test_Widget::initRight()
{
    right_splitter = new QSplitter();
}

void Sys_Test_Widget::initRightTop()
{
    right_top_widget = new QWidget();
    QLabel *image = new QLabel();
//    image->setFixedSize(50,50);
//    QMovie *score_image = new QMovie(":/page1/score.gif");
//    image->setMovie(score_image);
//    score_image->start();
    image->setPixmap(QPixmap(":/page1/score.png"));

    QFont ft;
    ft.setBold(true);
    ft.setPointSize(50);

    score_label = new QLabel();
    score_label->setFont(ft);
    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addWidget(image);
    main_layout->addWidget(score_label);
    right_top_widget->setLayout(main_layout);

}
void Sys_Test_Widget::initRightCenter()
{
//    right_center_widget = new QWidget();
    right_center_widget = new show_percent_page();
}

void Sys_Test_Widget::initRightBottom()
{
    right_bottom_widget = new Net_Speed();
}

void Sys_Test_Widget::set_bar_value(int n)
{
    progressBar->setValue(n);
}
void Sys_Test_Widget::set_text_show(QString str)
{
    text_show->setText(str);
}

/*这个槽供主页面调用,切换到这个页面时,开始线程体检*/
void Sys_Test_Widget::start_timer()
{
//    thread_get_score->start();
    obj_get_score->start_get_score();
}
void Sys_Test_Widget::get_score(double score)
{
    QString str = QString::number(score,'f',0);
    score_label->setText(str);
}
