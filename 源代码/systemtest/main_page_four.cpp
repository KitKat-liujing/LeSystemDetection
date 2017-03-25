#include "main_page_four.h"
#include <QByteArray>

My_Obj_Disk_Test::My_Obj_Disk_Test()
{
        out = "";
        proc = new QProcess();
}

void My_Obj_Disk_Test::start_timer()
{
    emit set_wid_2_info_1("正在检测，请耐心等待");
    QString program = "bash";
    QStringList arguments;
    arguments<<"/usr/bin/disk/disktool/disk_hdparm.sh"<<PWD;
    proc->start(program, arguments);
    if(!proc->waitForStarted())
    {
        return;
    }
    while(proc->waitForFinished())
    {
            out = proc->readAll();
            emit set_wid_2_info_1(out);
    }
}

My_Obj_Dd_Test::My_Obj_Dd_Test()
{
    out = "";
    proc = new QProcess();
}
void My_Obj_Dd_Test::start_test()
{
    emit send_result_dd_test("正在检测，请耐心等待");
    QString program = "bash";
    QStringList arguments;
    arguments<<"/usr/bin/disk/disktool/dd_test.sh"<<PWD;
    proc->start(program, arguments);
    if(!proc->waitForStarted())
    {
        return;
    }
    while(!proc->waitForFinished(0))
    {
            out += proc->readAll();
    }
    emit send_result_dd_test(out);
}

Main_Page_four::Main_Page_four(QWidget *parent) :
    QWidget(parent)
{
/*初始化窗口*/
    init_list_widget();
    init_widget_1();
    init_widget_2();
    init_widget_3();
    init_widget_4();
/*设置堆栈窗口*/
    stack = new QStackedWidget();
    stack->addWidget(widget_1);
    stack->addWidget(widget_2);
    stack->addWidget(widget_3);
    stack->addWidget(widget_4);
/*密码弹窗*/
    input_pwd_widget = new Input_Pwd();
    times = 0;
    /*线程*/
    thread_test_dd = new My_Obj_Disk_Test();
    my_thread = new QThread();
    my_thread->start();
    thread_test_dd->moveToThread(my_thread);
    My_Obj_Dd_Test_object = new My_Obj_Dd_Test();
    my_thread_2 = new QThread();
    my_thread_2->start();
    My_Obj_Dd_Test_object->moveToThread(my_thread_2);
    connect(thread_test_dd, SIGNAL(set_wid_2_info_1(QString)), this, SLOT(set_wid_2_info_1(QString)));
    connect(My_Obj_Dd_Test_object, SIGNAL(send_result_dd_test(QString)), this, SLOT(set_wid_2_info_3(QString)));
    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addWidget(list);
    main_layout->addWidget(stack);
    main_layout->setStretchFactor(list, 1);
    main_layout->setStretchFactor(stack, 4);
    main_layout->setContentsMargins(0,0,0,0);
    setLayout(main_layout);

    pro = new QProcess();
    connect(list, SIGNAL(currentRowChanged(int)), stack, SLOT(setCurrentIndex(int)));//页面切换
    connect(list, SIGNAL(currentRowChanged(int)), this, SLOT(init_bash(int)));//获取页面切换信号  设置页面初始化信息
    connect(re_test_disk, SIGNAL(clicked()), this, SLOT(re_test_disk_slots()));//页面一重新检测按钮
    connect(more_detail, SIGNAL(clicked()), this, SLOT(more_detail_slots()));//页面一更多信息按钮
    connect(re_test_io, SIGNAL(clicked()), this, SLOT(re_test_io_slots()));//io_test
//    connect(re_test_disk_perf, SIGNAL(clicked()),this, SLOT(re_test_disk_perf_slots()));//start_test
    connect(re_test_disk_perf, SIGNAL(clicked()), this, SLOT(re_test_disk_perf_slots()));

    connect(install_widget_4, SIGNAL(clicked()), this, SLOT(install_sysstat()));//点击安装sysstat工具
    connect(remove_widget_4, SIGNAL(clicked()), this, SLOT(remove_sysstat()));//点击卸载sysstat工具
    connect(check_widget_4, SIGNAL(clicked()), this, SLOT(check_sysstat()));
    connect(check_widget_2, SIGNAL(clicked()), this, SLOT(check_hddtemp()));
    connect(install_widget_2, SIGNAL(clicked()), this, SLOT(install_hddtemp()));
    connect(remove_widget_2, SIGNAL(clicked()),this, SLOT(remove_hddtemp()));
    connect(start_button, SIGNAL(clicked()), this, SLOT(start_button_slots()));
    this->setAutoFillBackground(true);
    list->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;background-color:#eaeaea");
    this->setStyleSheet("QTextBrowser{background-color: #eaeaea; border:0px solid grey; border-radius: 8px;}");

    this->re_test_disk_slots();
}

void Main_Page_four::init_list_widget()
{
    list = new QListWidget();
        /*listwidget按钮设置*/
    QListWidgetItem *Item_0 = new QListWidgetItem(tr("磁盘基本信息"));
    Item_0->setIcon(QIcon(":/disk/disk1"));
    Item_0->setTextAlignment(Qt::AlignLeft);
    Item_0->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    QListWidgetItem *Item_1 = new QListWidgetItem(tr("磁盘性能检测"));
    Item_1->setIcon(QIcon(":/disk/disk2"));
    Item_1->setTextAlignment(Qt::AlignLeft);
    Item_1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    QListWidgetItem *Item_2 = new QListWidgetItem(tr("I/O性能检测"));
    Item_2->setIcon(QIcon(":/disk/disk3"));
    Item_2->setTextAlignment(Qt::AlignLeft);
    Item_2->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    QListWidgetItem *Item_3 = new QListWidgetItem(tr("I/O工具检测"));
    Item_3->setIcon(QIcon(":/disk/disk4"));
    Item_3->setTextAlignment(Qt::AlignLeft);
    Item_3->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    list->insertItem(0,Item_0);
    list->insertItem(1,Item_1);
    list->insertItem(2,Item_2);
    list->insertItem(3,Item_3);

    //标签字体大小
    QFont font;
    font.setPointSize(14);
    font.setUnderline(1);
    list->setFont(font);
}

void Main_Page_four::init_widget_1()
{
    widget_1 = new QWidget();
    disk_info = new QLabel();
    re_test_disk = new QPushButton();
    more_detail = new QPushButton();
    line_label_1 = new QLabel();
    line_label_1->setFixedHeight(10);
    line_label_1->installEventFilter(this);
    wid_1_show_info = new QTextBrowser();

//    disk_info->setFixedSize(150,40);
//    re_test_disk->setFixedSize(100,40);
//    more_detail->setFixedSize(100,40);
    wid_1_show_info->setFixedSize(680,400);

    /*字体*/
    QFont font;
    font.setPointSize(15);
    //this->setFont(font);
    disk_info->setFont(font);
    QFont font1;
    font1.setPointSize(13);
    //this->setFont(font1);
    re_test_disk->setFont(font1);
    more_detail->setFont(font1);
/**/
    disk_info->setText(tr("磁盘基本信息概要"));
    re_test_disk->setText(tr("重新检测"));
    more_detail->setText(tr("更多信息"));
/*布局*/
    QHBoxLayout *widget_1_H_layout = new QHBoxLayout();
    widget_1_H_layout->addWidget(disk_info, 0, Qt::AlignCenter);
    widget_1_H_layout->addStretch();
    widget_1_H_layout->addWidget(re_test_disk, 0, Qt::AlignCenter);
    widget_1_H_layout->addWidget(more_detail, 0, Qt::AlignCenter);
    widget_1_H_layout->setContentsMargins(20, 5, 20, 5);
    QVBoxLayout *widget_1_V_layout = new QVBoxLayout();
    widget_1_V_layout->addLayout(widget_1_H_layout);
    widget_1_V_layout->addWidget(line_label_1);
    widget_1_V_layout->addWidget(wid_1_show_info, 0, Qt::AlignCenter);
    widget_1_V_layout->setContentsMargins(0, 0, 5, 5);
    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addLayout(widget_1_V_layout);
    main_layout->setContentsMargins(0,0,0,0);

    widget_1->setLayout(main_layout);
}

void Main_Page_four::re_test_disk_slots()
{
    wid_1_show_info->setText(" ");
    out = "";
    QString program = "bash";
    QStringList arguments;
    arguments<<"/usr/bin/disk/diskinfo.sh";
    pro->start(program, arguments);
    while(pro->waitForReadyRead())
    {
    out += pro->readAll();
    wid_1_show_info->setText(out);
    }
}

void Main_Page_four::more_detail_slots()
{
    wid_1_show_info->setText("");
    out = "";
    if( Flag_Read_Pwd == 0 )
    {
        input_pwd_widget->exec();
        if( Flag_Cancel == 1 )
            return;
        more_detail_slots();
    }
    else if( Flag_Read_Pwd == 1)
    {
        QString program = "bash";
        QStringList arguments;
        arguments<<"/usr/bin/disk/diskinfosu.sh"<<PWD;
//        pro->setStandardOutputFile("aa.txt");
        pro->start(program, arguments);
        while(pro->waitForReadyRead())
        {
            out += pro->readAllStandardOutput();
            wid_1_show_info->setText(out);
        }
    }
}

void Main_Page_four::init_widget_2()
{
        widget_2 = new QWidget();
        wid_2_show_info_1 = new QTextBrowser();
        wid_2_show_info_1->setFixedSize(680, 85);
        wid_2_show_info_2 = new QTextBrowser();
        wid_2_show_info_2->setFixedSize(680, 45);
        wid_2_show_info_3 = new QTextBrowser();
        wid_2_show_info_3->setFixedSize(680,180);
        wid_2_show_info_3->setText(tr("该检测项测试磁盘读写速度，会消耗大量系统资源，如检测此项，请您耐心等待!"));
        QFont ft;
        ft.setPointSize(15);
        //ft.setBold(true);
        //widget_2_label_1->setFont(ft);
        QLabel *label_1 = new QLabel(tr("磁盘性能检测"));
        //label_1->setFixedHeight(30);
        label_1->setFont(ft);
        re_test_disk_perf = new QPushButton();
        re_test_disk_perf->setText(tr("一键检测"));
//        QFont ft1;
//        ft1.setPointSize(13);
//        re_test_disk_perf->setFont(13);
        //re_test_disk_perf->setFixedSize(100,30);
        QHBoxLayout *h_layout_0 = new QHBoxLayout();
        h_layout_0->addWidget(label_1);
        h_layout_0->addStretch();
        h_layout_0->addWidget(re_test_disk_perf);
        h_layout_0->setContentsMargins(0,0,100,0);
     /********* widget_2_layout_0  **************/
        widget_2_label_0 = new QLabel();
        widget_2_label_0 ->setFixedSize(680,10);
        widget_2_label_0->installEventFilter(this);

        QFont ft1;
        ft1.setPointSize(15);
        //ft1.setBold(true);
        QLabel *speed = new QLabel(tr("磁盘读写速度检测"));
        speed->setFont(ft1);
        start_button = new QPushButton(tr("开始检测"));
        start_button->setFixedSize(80,30);

        QHBoxLayout *h_layout_1 = new QHBoxLayout();
        h_layout_1->addWidget(speed);
        h_layout_1->addStretch();
        h_layout_1->addWidget(start_button);
        h_layout_1->setContentsMargins(0,0,100,5);

     /********* widget_2_layout_1  **************/
       QFont ft2;
       ft2.setPointSize(15);
       //ft2.setBold(true);
       QLabel *tools = new QLabel(tr("磁盘温度检测工具"));
       tools->setFont(ft2);
       //tools->setFixedHeight(30);
       widget_2_label_1 =new QLabel();
       widget_2_label_1 ->setFixedSize(680,10);
       widget_2_label_1->installEventFilter(this);
       tips_widget_2 = new QLabel(tr("hdparm install?")); //工具是否安装
       install_widget_2 = new QPushButton(tr("一键安装"));
       install_widget_2->setFixedSize(80,30);
       remove_widget_2 = new QPushButton(tr("一键卸载"));
       remove_widget_2->setFixedSize(80,30);
       check_widget_2 = new QPushButton(tr("温度检测"));
       check_widget_2->setFixedSize(80,30);

       QHBoxLayout *h_layout_2 = new QHBoxLayout();
       h_layout_2->addWidget(tips_widget_2);
       h_layout_2->addSpacing(150);
       h_layout_2->addWidget(install_widget_2);
       h_layout_2->addStretch();
       h_layout_2->addWidget(remove_widget_2);
       h_layout_2->addStretch();
       h_layout_2->addWidget(check_widget_2);
       h_layout_2->addStretch();
       h_layout_2->setContentsMargins(100,0,100,0);
     /********* total **************/
       QVBoxLayout *main_layout = new QVBoxLayout(this);
       main_layout->addSpacing(10);
       main_layout->addLayout(h_layout_0);
       main_layout->addWidget(widget_2_label_0);
       main_layout->addWidget(wid_2_show_info_1);
       main_layout->addWidget(tools);
       main_layout->addLayout(h_layout_2);
       main_layout->addWidget(wid_2_show_info_2);
       main_layout->addLayout(h_layout_1);
       main_layout->addWidget(wid_2_show_info_3);
       main_layout->setContentsMargins(0,0,0,0);
       widget_2->setLayout(main_layout);
}
/*hddtemp install/uninstall*/
void Main_Page_four::judge_hddtemp()
{
    out = "";
    QString program = "bash";
    QStringList arguments;
    arguments<<"/usr/bin/disk/disktool/hddtemp_judge.sh";
    pro->start(program, arguments);
    if(!pro->waitForStarted())
    {
        return;
    }
    while(pro->waitForReadyRead())
    {
        out = pro->readAll().trimmed();
    }
    if(out == "Y")
    {
        tips_widget_2->setText(tr("hddtemp 已安装"));
        install_widget_2->setEnabled(false);
        remove_widget_2->setEnabled(true);
        check_widget_2->setEnabled(true);
    }
    else if(out == "N")
    {
        tips_widget_2->setText(tr("hddtemp 未安装"));
        remove_widget_2->setEnabled(false);
        install_widget_2->setEnabled(true);
        check_widget_2->setEnabled(false);
    }
}
void Main_Page_four::check_hddtemp()
{
    if( Flag_Read_Pwd == 0 )
    {
        input_pwd_widget->exec();
        if( Flag_Cancel == 1 )
            return;
        check_hddtemp();
    }
    else if( Flag_Read_Pwd == 1)
    {
        out = "";
        QString program = "bash";
        QStringList arguments;
        arguments<<"/usr/bin/disk/disktool/hddtemp_tool.sh"<<PWD;
        pro->start(program, arguments);
        while(!pro->waitForFinished(0))
        {
            out += pro->readAll();
            wid_2_show_info_2->setText(out);
        }
    }
}

/*install hddtemp*/
void Main_Page_four::install_hddtemp()
{
    if( Flag_Read_Pwd == 0 )
    {
        input_pwd_widget->exec();
        if( Flag_Cancel == 1 )
            return;
        install_hddtemp();
    }
    else if( Flag_Read_Pwd == 1)
    {
        QString program = "bash";
        QStringList arguments;
        arguments<<"/usr/bin/disk/disktool/hddtemp_install.sh"<<PWD;
        pro->start(program, arguments);
        while(!pro->waitForFinished(0))
        {
        }
        judge_hddtemp();//判断安装情况
    }
}
/*remove hddtemp*/
void Main_Page_four::remove_hddtemp()
{
    if( Flag_Read_Pwd == 0 )
    {
        input_pwd_widget->exec();
        if( Flag_Cancel == 1 )
            return;
        remove_hddtemp();
    }
    else if( Flag_Read_Pwd == 1)
    {
        QString program = "bash";
        QStringList arguments;
        arguments<<"/usr/bin/disk/disktool/hddtemp_remove.sh"<<PWD;
        pro->start(program, arguments);
        while(!pro->waitForFinished(0))
        {
        }
        judge_hddtemp();//判断安装情况
    }
}
void Main_Page_four::start_timer()
{
//    QTimer::singleShot(100, this, SLOT(re_test_disk_perf_slots()));
//    re_test_disk_perf_slots();
}
/*接受信号 刷新信息*/
void Main_Page_four::set_wid_2_info_1(QString str)
{
    wid_2_show_info_1->setText(str);
}
void Main_Page_four::set_wid_2_info_3(QString str)
{
    wid_2_show_info_3->setText(str);
}
/*开启线程  运行脚本 disk_hdparm*/
void Main_Page_four::re_test_disk_perf_slots()
{
    if( Flag_Read_Pwd == 0 )
    {
        input_pwd_widget->exec();
        if( Flag_Cancel == 1 )
            return;
        re_test_disk_perf_slots();
    }
    else if( Flag_Read_Pwd == 1)
    {
      QTimer::singleShot(100, thread_test_dd, SLOT(start_timer()));
    }
}

void Main_Page_four::start_button_slots()
{
    if( Flag_Read_Pwd == 0 )
    {
        input_pwd_widget->exec();
        if( Flag_Cancel == 1 )
            return;
        start_button_slots();
    }
    else if( Flag_Read_Pwd == 1)
    {
        My_Obj_Dd_Test_object->start_test();
    }
}

void Main_Page_four::init_widget_3()
{
    widget_3 = new QWidget();
    io_info = new QLabel();
    re_test_io = new QPushButton();
    line_label_3 = new QLabel();
    line_label_3->setFixedHeight(10);
    line_label_3->installEventFilter(this);
    wid_3_show_info = new QTextBrowser();

    io_info->setFixedSize(150,40);
    //re_test_io->setFixedSize(100,40);
    wid_3_show_info->setFixedSize(680,400);

    /*字体*/
    QFont font;
    font.setPointSize(16);
    //this->setFont(font);
    io_info->setFont(font);
    //re_test_io->setFont(font);
/**/
    io_info->setText(tr("IO性能检测"));
    QFont font1;
    font1.setPointSize(13);
    re_test_io->setText(tr("一键检测"));
    re_test_io->setFont(font1);
/*布局*/
    QHBoxLayout *widget_3_H_layout = new QHBoxLayout();/*水平布局*/
    widget_3_H_layout->addWidget(io_info, 0, Qt::AlignCenter);
    widget_3_H_layout->addStretch();
    widget_3_H_layout->addWidget(re_test_io, 0, Qt::AlignCenter);
    widget_3_H_layout->setContentsMargins(20, 5, 20, 5);
    QVBoxLayout *widget_3_V_layout = new QVBoxLayout();/*垂直布局*/
    widget_3_V_layout->addLayout(widget_3_H_layout);
    widget_3_V_layout->addWidget(line_label_3);
    widget_3_V_layout->addWidget(wid_3_show_info, 0, Qt::AlignCenter);
    widget_3_V_layout->setContentsMargins(0, 0, 5, 5);
    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addLayout(widget_3_V_layout);
    main_layout->setContentsMargins(0,0,0,0);

    widget_3->setLayout(main_layout);
}

void Main_Page_four::re_test_io_slots()
{
    out = "";
    QString program = "bash";
    QStringList arguments;
    arguments<<"/usr/bin/disk/io_diskstats.sh";
    pro->start(program, arguments);
    while(pro->waitForReadyRead())
    {
        out += pro->readAll();
        wid_3_show_info->setText(out);
    }
}

void Main_Page_four::init_widget_4()
{
    widget_4 = new QWidget();
    wid_4_show_info = new QTextBrowser();
    QFont ft;
    ft.setPointSize(15);
    //ft_4.setBold(true);

    QLabel *label_2 = new QLabel(tr("磁盘读写速度检测"));
    label_2->setFont(ft);

    widget_4_line_label = new QLabel();
    widget_4_line_label->setFixedSize(680,20);
    widget_4_line_label->installEventFilter(this);

    tips_widget_4 = new QLabel(tr("iostat install?"));
    install_widget_4 = new QPushButton(tr("一键安装"));
    install_widget_4->setFixedSize(80,30);
    remove_widget_4 = new QPushButton(tr("一键卸载"));
    remove_widget_4->setFixedSize(80,30);
    check_widget_4 = new QPushButton(tr("一键检测"));
    check_widget_4->setFixedSize(80,30);

    QHBoxLayout *widget_4_layout_1 = new QHBoxLayout();
    widget_4_layout_1->addWidget(tips_widget_4);
    widget_4_layout_1->addSpacing(150);
    widget_4_layout_1->addWidget(install_widget_4);
    widget_4_layout_1->addStretch();
    widget_4_layout_1->addWidget(remove_widget_4);
    widget_4_layout_1->addStretch();
    widget_4_layout_1->addWidget(check_widget_4,0,Qt::AlignCenter);
    widget_4_layout_1->addStretch();
    widget_4_layout_1->setContentsMargins(50,0,0,0);

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addWidget(label_2,0,Qt::AlignLeft);
    main_layout->addWidget(widget_4_line_label);
    main_layout->addLayout(widget_4_layout_1);
    main_layout->addWidget(wid_4_show_info);
    widget_4->setLayout(main_layout);

}
/*sysstat是否安装*/
void Main_Page_four::init_widget_4_bash()
{
    out = "";
    QString program = "bash";
    QStringList arguments;
    arguments<<"/usr/bin/disk/disktool/sysstat_judge.sh";
    pro->start(program, arguments);
    while(pro->waitForReadyRead())
    {
        out = pro->readAll().trimmed();
    }
    if(out == "Y")//如果安装
    {
        tips_widget_4->setText(tr("IO测试工具sysstat已安装"));
        install_widget_4->setEnabled(false);
        remove_widget_4->setEnabled(true);
        check_widget_4->setEnabled(true);
    }
    else if(out == "N")//如果未安装
    {
        tips_widget_4->setText(tr("IO测试工具sysstat未安装"));
        install_widget_4->setEnabled(true);
        remove_widget_4->setEnabled(false);
        check_widget_4->setEnabled(false);
    }
}
/*安装sysstat*/
void Main_Page_four::install_sysstat()
{
    if( Flag_Read_Pwd == 0 )
    {
        input_pwd_widget->exec();
        if( Flag_Cancel == 1 )
            return;
        install_sysstat();
    }
    else if( Flag_Read_Pwd == 1)
    {
        QString program = "bash";
        QStringList arguments;
        arguments<<"/usr/bin/disk/disktool/sysstat_install.sh"<<PWD;
        pro->start(program, arguments);
        while(!pro->waitForFinished(0))
        {
        }
        init_widget_4_bash();//判断安装情况
    }
}
/*卸载sysstat*/
void Main_Page_four::remove_sysstat()
{
    if( Flag_Read_Pwd == 0 )
    {
        input_pwd_widget->exec();
        if( Flag_Cancel == 1 )
            return;
        remove_sysstat();
    }
    else if( Flag_Read_Pwd == 1)
    {
        QString program = "bash";
        QStringList arguments;
        arguments<<"/usr/bin/disk/disktool/sysstat_remove.sh"<<PWD;
        pro->start(program, arguments);
        while(!pro->waitForFinished(0))
        {
        }
        init_widget_4_bash();//判断安装情况
    }
}

void Main_Page_four::check_sysstat()
{
    if( Flag_Read_Pwd == 0 )
    {
        input_pwd_widget->exec();
        if( Flag_Cancel == 1 )
            return;
        check_sysstat();
    }
    else if( Flag_Read_Pwd == 1)
    {

        out = "";
        QString program = "bash";
        QStringList arguments;
        arguments<<"/usr/bin/disk/disktool/iostat_tool.sh"<<PWD;
        pro->start(program, arguments);
        while(true == pro->waitForFinished())
        {
            out += pro->readAll().trimmed();
            wid_4_show_info->setText(out);
        }
    }
}

bool Main_Page_four::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == line_label_1)
    {
        if(event->type() == QEvent::Paint)
        {
            int label_height = line_label_1->height();
            int label_width = line_label_1->width();
            QPainter painter(line_label_1);//QPainter类低水平的绘制，例如在窗口部件上
            painter.setPen(QPen(QColor(200, 200, 200), 2, Qt::SolidLine));//绘笔
            painter.drawLine(0, label_height/2, label_width, label_height/2);	//绘
        }
    }

        if(obj == widget_2_label_0)
        {
            if(event->type() == QEvent::Paint)
            {
                int width = widget_2_label_0->width();
                int height = widget_2_label_0->height();
                QPainter painter(widget_2_label_0);
                painter.setPen(QPen(QColor(220, 220, 220), 2, Qt::SolidLine));
                painter.drawLine(0,height/2,width,height/2);

            }
        }
        if(obj == widget_2_label_1)
        {
            if(event->type() == QEvent::Paint)
            {
                int width = widget_2_label_1->width();
                int height = widget_2_label_1->height();
                QPainter painter(widget_2_label_1);
                painter.setPen(QPen(QColor(220, 220, 220), 2, Qt::SolidLine));
                painter.drawLine(0,height/2,width,height/2);

            }
        }
        if(obj == line_label_3)
        {
            if(event->type() == QEvent::Paint)
            {
                int width = line_label_3->width();
                int height = line_label_3->height();
                QPainter painter(line_label_3);
                painter.setPen(QPen(QColor(220, 220, 220), 2, Qt::SolidLine));
                painter.drawLine(0,height/2,width,height/2);

            }
        }
        if(obj == widget_4_line_label)
        {
            if(event->type() == QEvent::Paint)
            {
                int width = widget_4_line_label->width();
                int height = widget_4_line_label->height();
                QPainter painter(widget_4_line_label);
                painter.setPen(QPen(QColor(220, 220, 220), 2, Qt::SolidLine));
                painter.drawLine(0,height/2,width,height/2);

            }
        }
    return QWidget::eventFilter(obj, event);
}
/*页面切换时候的初始化页面程序*/
void Main_Page_four::init_bash(int n)
{
    if( n == 0 )
        this->re_test_disk_slots();
    if(n == 1)
    {
        if(times == 0){
            times++;
            this->re_test_disk_perf_slots();
        }
        this->judge_hddtemp();
    }
    if( n == 2 )
        this->re_test_io_slots();
    if( n == 3)
    {
        this->init_widget_4_bash();
        if(check_widget_4->isEnabled())//如果可用  则运行检测
            this->check_sysstat();
    }
}
