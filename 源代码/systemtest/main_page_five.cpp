#include "main_page_five.h"
/*Netspeed  object init*/
My_Obj_Netspeed::My_Obj_Netspeed()
{
    proc = new QProcess();
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(start_timer()));
    timer->start(500);
}
void My_Obj_Netspeed::start_timer()
{
//    if(timer->isActive())
//        timer->stop();
    out = "";
    QString program = "bash";;
    QStringList arguments;
    arguments<<"/usr/bin/netinfo/2/netspeed.sh";
    proc->start(program, arguments);
    if(!proc->waitForStarted())
    {
        return;
    }
    while(true == proc->waitForFinished())
    {
            out += proc->readAll();
        emit send_Netspeed(out);
    }
//    timer->start(1500);
}
/*tcp_udp object init*/
My_Obj_udp_tcp::My_Obj_udp_tcp()
{
    proc = new QProcess();
    out = "";
//    QTimer::singleShot(100,this,SLOT(start_timer()));
}
void My_Obj_udp_tcp::start_timer()
{
    out = "";
    QString program = "bash";
    QStringList arguments;
    arguments<<"/usr/bin/netinfo/2/tcp_udp.sh";
    proc->start(program, arguments);
    if(!proc->waitForStarted())
    {
        return;
    }
    while(!proc->waitForFinished(0))
    {
        out += proc->readAll();
    }
    emit send_udp_tcp(out);
}
/*Net Flow*/
My_Obj_Net_Flow::My_Obj_Net_Flow()
{
    proc = new QProcess();
    out = "";
}

void My_Obj_Net_Flow::Net_Flow_wire(QString arg)
{
    out = "";
    QString program = "bash";
    QStringList arguments;
    arguments<<"/usr/bin/netinfo/2/ethavgflow.sh"<<arg;
    proc->start(program, arguments);
    if(!proc->waitForStarted())
    {
        return;
    }
    while(!proc->waitForFinished(0))
    {
        out += proc->readAll();
    }
    emit send_Net_Flow(1,out);//
}
void My_Obj_Net_Flow::Net_Flow_wireless(QString arg)
{
    out = "";
    QString program = "bash";
    QStringList arguments;
    arguments<<"/usr/bin/netinfo/2/wlanavgflow.sh"<<arg;
    proc->start(program, arguments);
    if(!proc->waitForStarted())
    {
        return;
    }
    while(!proc->waitForFinished(0))
    {
        out += proc->readAll();
    }
    emit send_Net_Flow(2,out);//
}

Main_Page_five::Main_Page_five(QWidget *parent) :
    QWidget(parent)
{
    /*初始化窗口信息*/
    init_list_widget();
    init_widget_1();
    init_widget_2();
    init_widget_3();
    init_widget_4();
/*堆栈窗口*/
    stack = new QStackedWidget();
    stack->addWidget(widget_1);
    stack->addWidget(widget_2);
    stack->addWidget(widget_3);
    stack->addWidget(widget_4);
    /* */
    input_pwd_widget = new Input_Pwd();
    pro = new QProcess();
    out = "";

    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addWidget(list);
    main_layout->addWidget(stack);
    main_layout->setStretchFactor(list, 1);
    main_layout->setStretchFactor(stack, 4);
    main_layout->setContentsMargins(0,0,0,0);
    setLayout(main_layout);

    My_Obj_Netspeed_object = new My_Obj_Netspeed();
    thread_1 = new QThread();
    My_Obj_Netspeed_object->moveToThread(thread_1);

    My_Obj_udp_tcp_object = new My_Obj_udp_tcp();
    thread_2 = new QThread();
    thread_2->start();
    My_Obj_udp_tcp_object->moveToThread(thread_2);

    My_Obj_Net_Flow_object = new My_Obj_Net_Flow();
    thread_3 = new QThread();
    My_Obj_Net_Flow_object->moveToThread(thread_3);

    connect(list, SIGNAL(currentRowChanged(int)), stack, SLOT(setCurrentIndex(int)));//页面切换
    connect(list, SIGNAL(currentRowChanged(int)), this, SLOT(init_bash(int)));
    connect(re_test_net, SIGNAL(clicked()), this, SLOT(re_test_net_slots()));//touch网络基本信息检测按钮
    connect(more_detail_for_net, SIGNAL(clicked()), this, SLOT(more_detail_for_net_slots()));
    connect(My_Obj_Netspeed_object, SIGNAL(send_Netspeed(QString)), this, SLOT(get_Netspeed(QString)));//接受网速更新
    connect(test_3, SIGNAL(clicked()), My_Obj_udp_tcp_object, SLOT(start_timer()));//触发信号 开始udp_tcp检测
    connect(My_Obj_udp_tcp_object, SIGNAL(send_udp_tcp(QString)), this, SLOT(get_udp_tcp(QString)));//udp_tcp
    connect(test_1, SIGNAL(clicked()), this, SLOT(test_1_clicked()));//test-wire
    connect(test_2, SIGNAL(clicked()), this, SLOT(test_2_clicked()));//test-wireless
    connect(My_Obj_Net_Flow_object, SIGNAL(send_Net_Flow(int,QString)), this, SLOT(set_wid_2_text_show(int,QString)));//set text_show (test_wire/test_wireless)
    connect(re_test_safe, SIGNAL(clicked()), this, SLOT(re_test_safe_slots()));//re_test_safe
    connect(more_detail_for_safe, SIGNAL(clicked()), this, SLOT(more_detail_for_safe_slots()));//more_info_for_safe
    connect(re_test_wired, SIGNAL(clicked()), this, SLOT(show_wire_msg()));//re_test_wire
    connect(re_test_wireless, SIGNAL(clicked()), this, SLOT(show_wireless_msg()));//re_test_wireless

    this->setAutoFillBackground(true);
    list->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;background-color:#eaeaea");
    this->setStyleSheet("QTextBrowser{background-color: #eaeaea; border:0px solid grey; border-radius: 8px;}");

    re_test_net_slots();
}

void Main_Page_five::init_list_widget()
{
    list = new QListWidget();
        /*listwidget按钮设置*/
    QListWidgetItem *Item_0 = new QListWidgetItem(tr("网络基本信息"));
    Item_0->setIcon(QIcon(":/netinfo/net1"));
    Item_0->setTextAlignment(Qt::AlignLeft);
    Item_0->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    QListWidgetItem *Item_1 = new QListWidgetItem(tr("网络性能检测"));
    Item_1->setIcon(QIcon(":/netinfo/net2"));
    Item_1->setTextAlignment(Qt::AlignLeft);
    Item_1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    QListWidgetItem *Item_2 = new QListWidgetItem(tr("网络安全检测"));
    Item_2->setIcon(QIcon(":/netinfo/net3"));
    Item_2->setTextAlignment(Qt::AlignLeft);
    Item_2->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    QListWidgetItem *Item_3 = new QListWidgetItem(tr("网络信息统计"));
    Item_3->setIcon(QIcon(":/netinfo/net4"));
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

void Main_Page_five::init_widget_1()
{
    widget_1 = new QWidget();
    net_info = new QLabel();
    re_test_net = new QPushButton();
    more_detail_for_net = new QPushButton();
    line_label_1 = new QLabel();
    line_label_1->setFixedHeight(10);
    line_label_1->installEventFilter(this);
    wid_1_show_info = new QTextBrowser();

    //net_info->setFixedSize(150,40);
    //re_test_net->setFixedSize(100,40);
    //more_detail_for_net->setFixedSize(100,40);
    wid_1_show_info->setFixedSize(680,400);

    /*字体*/
    QFont font;
    font.setPointSize(15);
    //this->setFont(font);
    net_info->setFont(font);
    QFont font1;
    font1.setPointSize(13);
    //this->setFont(font);
    re_test_net->setFont(font1);
    more_detail_for_net->setFont(font1);
/**/
    net_info->setText(tr("网络基本信息概要"));
    re_test_net->setText(tr("重新检测"));
    more_detail_for_net->setText(tr("更多信息"));
/*布局*/
    QHBoxLayout *widget_1_H_layout = new QHBoxLayout();
    widget_1_H_layout->addWidget(net_info, 0, Qt::AlignCenter);
    widget_1_H_layout->addStretch();
    widget_1_H_layout->addWidget(re_test_net, 0, Qt::AlignCenter);
    widget_1_H_layout->addWidget(more_detail_for_net, 0, Qt::AlignCenter);
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

void Main_Page_five::re_test_net_slots()
{
    wid_1_show_info->setText("");
    out = "";
    QString program = "bash";
    QStringList arguments;
    arguments<<"/usr/bin/netinfo/1/netinfo.sh";
    pro->start(program, arguments);
    while(pro->waitForReadyRead())
    {
        out += pro->readAll();
        wid_1_show_info->setText(out);
    }
}

void Main_Page_five::more_detail_for_net_slots()
{
    wid_1_show_info->setText("");
    out = "";
    if(Flag_Read_Pwd == 0)
    {
        input_pwd_widget->exec();
        if(Flag_Cancel)
            return;
        more_detail_for_net_slots();
    }
    else if(Flag_Read_Pwd == 1)
    {
        QString Program = "bash";
        QStringList arguments;
        arguments<<"/usr/bin/netinfo/1/netinfosu.sh"<<PWD;
        pro->start(Program, arguments);
        while(pro->waitForFinished())
        {
            out = pro->readAll();
            wid_1_show_info->setText(out);
        }
    }
}

void Main_Page_five::init_widget_2()
{
    widget_2 = new QWidget();
    /********* net_label**************/
    QFont ft;
    ft.setPointSize(15);
    //ft.setBold(true);
    net_label = new QLabel("网络性能");
    net_label->setFont(ft);

    /********* layout_1 **************/
    QHBoxLayout *h_layout_left = new QHBoxLayout();
    h_layout_left->addWidget(net_label, 0, Qt::AlignLeft);
    h_layout_left->addStretch();
    h_layout_left->setContentsMargins(10,0,0,0);
    /********* line_1**************/
    line_1 =new QLabel();
    line_1 ->setFixedSize(680,10);
    line_1->installEventFilter(this);
    /********* text_broswer **************/
    text_broswer = new QTextBrowser();
    text_broswer->setFixedSize(300,400);
    /********* line_2**************/
    line_2 =new QLabel();
    line_2 ->setFixedSize(340,10);
    line_2->installEventFilter(this);
    /*********average_label **************/
    average_label = new QLabel("测特定时间内网卡总流量和平均");
    /*********h_layout_right_1*************/
    label_2_1= new QLabel("有线网");
    label_2_2 = new QLabel("无线网");
    edit_1 = new QLineEdit();
    edit_2 = new QLineEdit();
    edit_1->setPlaceholderText(tr("请输入测试时间"));
    edit_2->setPlaceholderText(tr("请输入测试时间"));
    test_1 = new QPushButton("测试");
    test_2 = new QPushButton("测试");
    QHBoxLayout *h_layout_right_1 = new QHBoxLayout();
    h_layout_right_1->addWidget(label_2_1);
    h_layout_right_1->addWidget(edit_1);
    h_layout_right_1->addSpacing(10);
    h_layout_right_1->addWidget(test_1);
    h_layout_right_1->setContentsMargins(10,0,20,0);
    QHBoxLayout *h_layout_right_2 = new QHBoxLayout();
    h_layout_right_2->addWidget(label_2_2);
    h_layout_right_2->addWidget(edit_2);
    h_layout_right_2->addSpacing(10);
    h_layout_right_2->addWidget(test_2);
    h_layout_right_2->setContentsMargins(10,0,20,0);
    /*********text browser**************/
    net_broswer_1 = new QTextBrowser();
    net_broswer_2 = new QTextBrowser();
    net_broswer_1->setFixedSize(300,70);
    net_broswer_2->setFixedSize(300,70);
    /*********h_layout_right_3**************/
    QHBoxLayout *h_layout_right_3 = new QHBoxLayout();
    label_3 = new QLabel("测60s内tcp、udp信息");
    test_3 = new QPushButton("开始测试");
    test_3->setFixedSize(80,30);
    h_layout_right_3->addStretch();
    h_layout_right_3->addWidget(label_3);
    h_layout_right_3->addStretch();
    h_layout_right_3->addWidget(test_3);
    h_layout_right_3->addStretch();
    h_layout_right_3->setContentsMargins(10,0,20,0);
    /*********tcp_broswer**************/
    tcp_broswer = new QTextBrowser();
    tcp_broswer->setFixedSize(300, 100);
    /*********main_layout**************/
    QVBoxLayout *main_layout_left = new QVBoxLayout();
    main_layout_left->addWidget(text_broswer, 0, Qt::AlignCenter);
    QVBoxLayout *main_layout_right = new QVBoxLayout();
    main_layout_right->addWidget(average_label, 0, Qt::AlignCenter);
    main_layout_right->addLayout(h_layout_right_1);
    main_layout_right->addWidget(net_broswer_1, 0, Qt::AlignCenter);
    main_layout_right->addLayout(h_layout_right_2);
    main_layout_right->addWidget(net_broswer_2, 0, Qt::AlignCenter);
    main_layout_right->addLayout(h_layout_right_3);
    main_layout_right->addWidget(tcp_broswer, 0, Qt::AlignCenter);
    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addLayout(main_layout_left);
    main_layout->addLayout(main_layout_right);
    QVBoxLayout *main_main_layout = new QVBoxLayout();
    main_main_layout->addLayout(h_layout_left);
    main_main_layout->addWidget(line_1, 0, Qt::AlignCenter);
    main_main_layout->addLayout(main_layout);
    widget_2->setLayout(main_main_layout);
}

void Main_Page_five::get_Netspeed(QString str)
{
    text_broswer->setText(str);
}

void Main_Page_five::get_udp_tcp(QString str)
{
    tcp_broswer->setText(str);
}
/*网络连接状态*/
void Main_Page_five::test_network()
{
    out = "";
    QString program = "bash";
    QStringList arguments;
    arguments<<"/usr/bin/netinfo/2/test_netlink.sh";
    pro->start(program, arguments);
    if(!pro->waitForStarted())
    {
        return;
    }
    while(pro->waitForReadyRead())
    {
        out = pro->readAll().trimmed();
    }
    if(out == "0")
    {
        test_1->setEnabled(false);
        test_2->setEnabled(false);
    }
    else if(out == "1")
    {
        test_1->setEnabled(true);
        test_2->setEnabled(false);
    }
    else if(out == "2")
    {
        test_1->setEnabled(false);
        test_2->setEnabled(true);
    }
    else if(out == "3")
    {
        test_1->setEnabled(true);
        test_2->setEnabled(true);
    }
}
void Main_Page_five::test_1_clicked()
{
    QString getout = edit_1->text().trimmed();
    My_Obj_Net_Flow_object->Net_Flow_wire(getout);
    edit_1->clear();
    edit_1->setPlaceholderText(tr("请输入测试时间"));
}
void Main_Page_five::test_2_clicked()
{
    QString getout = edit_2->text().trimmed();
    My_Obj_Net_Flow_object->Net_Flow_wireless(getout);
    edit_2->clear();
    edit_2->setPlaceholderText(tr("请输入测试时间"));
}

void Main_Page_five::set_wid_2_text_show(int n, QString str)
{
    if( n == 1)
    net_broswer_1->setText(str);
    else if(n == 2)
        net_broswer_2->setText(str);
}
void Main_Page_five::init_widget_3()
{
    widget_3 = new QWidget();
    net_safe_info = new QLabel();
    re_test_safe = new QPushButton();
    more_detail_for_safe = new QPushButton();
    line_label_3 = new QLabel();
    line_label_3->setFixedHeight(10);
    line_label_3->installEventFilter(this);
    wid_3_show_info = new QTextBrowser();

    //net_safe_info->setFixedSize(150,40);
    //re_test_safe->setFixedSize(100,40);
    //more_detail_for_safe->setFixedSize(100,40);
    wid_3_show_info->setFixedSize(680,400);

    /*字体*/
    QFont font;
    font.setPointSize(15);
    //this->setFont(font);
    net_safe_info->setText(tr("网络安全检测信息"));

    net_safe_info->setFont(font);
    QFont font1;
    font1.setPointSize(13);
    re_test_safe->setText(tr("重新检测"));
    re_test_safe->setFont(font1);
    more_detail_for_safe->setText(tr("更多信息"));
    more_detail_for_safe->setFont(font1);
/**/

/*布局*/
    QHBoxLayout *widget_3_H_layout = new QHBoxLayout();
    widget_3_H_layout->addWidget(net_safe_info, 0, Qt::AlignCenter);
    widget_3_H_layout->addStretch();
    widget_3_H_layout->addWidget(re_test_safe, 0, Qt::AlignCenter);
    widget_3_H_layout->addWidget(more_detail_for_safe, 0, Qt::AlignCenter);
    widget_3_H_layout->setContentsMargins(20, 5, 20, 5);
    QVBoxLayout *widget_3_V_layout = new QVBoxLayout();
    widget_3_V_layout->addLayout(widget_3_H_layout);
    widget_3_V_layout->addWidget(line_label_3);
    widget_3_V_layout->addWidget(wid_3_show_info, 0, Qt::AlignCenter);
    widget_3_V_layout->setContentsMargins(0, 0, 5, 5);
    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addLayout(widget_3_V_layout);
    main_layout->setContentsMargins(0,0,0,0);

    widget_3->setLayout(main_layout);
}

void Main_Page_five::re_test_safe_slots()
{
    wid_3_show_info->setText("");
    out = "";
    QString program = "bash";
    QStringList arguments;
    arguments<<"/usr/bin/netinfo/3/net_secure.sh";
    pro->start(program, arguments);
    while(pro->waitForReadyRead())
    {
        out += pro->readAll();
        wid_3_show_info->setText(out);
    }
}

void Main_Page_five::more_detail_for_safe_slots()
{
    wid_3_show_info->setText("");
    out = "";
    if(Flag_Read_Pwd == 0)
    {
        input_pwd_widget->exec();
        if(Flag_Cancel)
            return;
        this->more_detail_for_safe_slots();
    }
    else if(Flag_Read_Pwd == 1)
    {
        QString Program = "bash";
        QStringList arguments;
        arguments<<"/usr/bin/netinfo/3/firewall.sh"<<PWD;
        pro->start(Program, arguments);
        while(pro->waitForFinished())
        {
            out += pro->readAll();
            wid_3_show_info->setText(out);
        }
    }
}

void Main_Page_five::init_widget_4()
{
    widget_4 = new QWidget();
    net_info_flow = new QLabel();
    re_test_wired = new QPushButton();
    re_test_wireless = new QPushButton();
    line_label_4 = new QLabel();
    line_label_4->setFixedHeight(10);
    line_label_4->installEventFilter(this);
    wid_4_show_wired = new QTextBrowser();
    wid_4_show_wireless = new QTextBrowser();

    //net_info_flow->setFixedSize(150,40);
    //re_test_wired->setFixedSize(100,40);
    //re_test_wireless->setFixedSize(100,40);
    wid_4_show_wired->setFixedSize(340,400);
    wid_4_show_wireless->setFixedSize(340,400);
    /*字体*/
    QFont font;
    font.setPointSize(16);
    //this->setFont(font);
    net_info_flow->setFont(font);

    QFont font1;
    font.setPointSize(13);
    re_test_wired->setFont(font1);
    re_test_wireless->setFont(font1);
/**/
    net_info_flow->setText(tr("网络信息统计信息"));
    re_test_wired->setText(tr("有线重测"));
    re_test_wireless->setText(tr("无线重测"));
/*布局*/
    QHBoxLayout *widget_4_H_layout = new QHBoxLayout();
    widget_4_H_layout->addWidget(net_info_flow, 0, Qt::AlignCenter);
    widget_4_H_layout->addStretch();
    widget_4_H_layout->addWidget(re_test_wired, 0, Qt::AlignCenter);
    widget_4_H_layout->addWidget(re_test_wireless, 0, Qt::AlignCenter);
    widget_4_H_layout->setContentsMargins(20, 5, 20, 5);
    QHBoxLayout *widget_4_text_layout = new QHBoxLayout();
    widget_4_text_layout->addStretch();
    widget_4_text_layout->addWidget(wid_4_show_wired);
    widget_4_text_layout->addSpacing(10);
    widget_4_text_layout->addWidget(wid_4_show_wireless);
    widget_4_text_layout->addStretch();
    QVBoxLayout *widget_4_V_layout = new QVBoxLayout();
    widget_4_V_layout->addLayout(widget_4_H_layout);
    widget_4_V_layout->addWidget(line_label_4);
    widget_4_V_layout->addLayout(widget_4_text_layout);
    widget_4_V_layout->setContentsMargins(0, 0, 5, 5);
    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addLayout(widget_4_V_layout);
    main_layout->setContentsMargins(0,0,0,0);

    widget_4->setLayout(main_layout);
}

void Main_Page_five::show_wire_msg()
{
    wid_4_show_wired->setText("");
    out = "";
    QString program = "bash";
    QStringList arguments;
    arguments<<"/usr/bin/netinfo/4/eth.sh";
    pro->start(program, arguments);
    while(pro->waitForReadyRead())
    {
        out += pro->readAll();
        wid_4_show_wired->setText(out);
    }
}

void Main_Page_five::show_wireless_msg()
{
    wid_4_show_wireless->setText("");
    out = "";
    QString program = "bash";
    QStringList arguments;
    arguments<<"/usr/bin/netinfo/4/wlan.sh";
    pro->start(program, arguments);
    while(pro->waitForReadyRead())
    {
        out += pro->readAll();
        wid_4_show_wireless->setText(out);
    }
}

bool Main_Page_five::eventFilter(QObject *obj, QEvent *event)
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
    if(obj == line_1)
    {
        if(event->type() == QEvent::Paint)
        {
            int label_height = line_1->height();
            int label_width = line_1->width();
            QPainter painter(line_1);//QPainter类低水平的绘制，例如在窗口部件上
            painter.setPen(QPen(QColor(200, 200, 200), 2, Qt::SolidLine));//绘笔
            painter.drawLine(0, label_height/2, label_width, label_height/2);	//绘
        }
    }
    if(obj == line_2)
    {
        if(event->type() == QEvent::Paint)
        {
            int label_height = line_2->height();
            int label_width = line_2->width();
            QPainter painter(line_2);//QPainter类低水平的绘制，例如在窗口部件上
            painter.setPen(QPen(QColor(200, 200, 200), 2, Qt::SolidLine));//绘笔
            painter.drawLine(0, label_height/2, label_width, label_height/2);	//绘
        }
    }
    if(obj == line_3)
    {
        if(event->type() == QEvent::Paint)
        {
            int label_height = line_3->height();
            int label_width = line_3->width();
            QPainter painter(line_3);//QPainter类低水平的绘制，例如在窗口部件上
            painter.setPen(QPen(QColor(200, 200, 200), 2, Qt::SolidLine));//绘笔
            painter.drawLine(0, label_height/2, label_width, label_height/2);	//绘
        }
    }

    if(obj == line_label_3)
    {
        if(event->type() == QEvent::Paint)
        {
            int label_height = line_label_3->height();
            int label_width = line_label_3->width();
            QPainter painter(line_label_3);//QPainter类低水平的绘制，例如在窗口部件上
            painter.setPen(QPen(QColor(200, 200, 200), 2, Qt::SolidLine));//绘笔
            painter.drawLine(0, label_height/2, label_width, label_height/2);	//绘
        }
    }

    if(obj == line_label_4)
    {
        if(event->type() == QEvent::Paint)
        {
            int label_height = line_label_4->height();
            int label_width = line_label_4->width();
            QPainter painter(line_label_4);//QPainter类低水平的绘制，例如在窗口部件上
            painter.setPen(QPen(QColor(200, 200, 200), 2, Qt::SolidLine));//绘笔
            painter.drawLine(0, label_height/2, label_width, label_height/2);	//绘
        }
    }

    return QWidget::eventFilter(obj, event);
}

void Main_Page_five::init_bash(int n)
{
    if(n == 1)
    {
        thread_1->start();
        this->test_network();
        thread_3->start();
    }
    if( n == 2)
        this->re_test_safe_slots();
    if( n == 3)
    {
        this->show_wire_msg();
        this->show_wireless_msg();
    }
}
