#include "main_page_six.h"

Main_Page_six::Main_Page_six(QWidget *parent) :
    QWidget(parent)
{
    init_list_widget();
    init_widget_1();
    init_widget_2();
    init_widget_3();

    stack = new QStackedWidget();
    stack->addWidget(widget_1);
    stack->addWidget(widget_2);
    stack->addWidget(widget_3);

    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addWidget(list);
    main_layout->addWidget(stack);
    main_layout->setStretchFactor(list, 1);
    main_layout->setStretchFactor(stack, 4);
    main_layout->setContentsMargins(0,0,0,0);
    setLayout(main_layout);

    pro = new QProcess();
    out = "";
    input_pwd_widget = new Input_Pwd();

    connect(list, SIGNAL(currentRowChanged(int)), stack, SLOT(setCurrentIndex(int)));
    connect(list, SIGNAL(currentRowChanged(int)), this, SLOT(init_widget_bash(int)));
    connect(re_test_os, SIGNAL(clicked()), this, SLOT(re_test_os_slots()));
    connect(re_test_hard, SIGNAL(clicked()), this, SLOT(re_test_hard_slots()));
    connect(more_detail_hard, SIGNAL(clicked()), this, SLOT(more_detail_hard_slots()));
    connect(re_test_os_run, SIGNAL(clicked()), this, SLOT(re_test_os_run_slots()));
    connect(more_detail_os_run, SIGNAL(clicked()), this, SLOT(more_detail_os_run_slots()));

    this->setAutoFillBackground(true);
    list->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;background-color:#eaeaea");
    this->setStyleSheet("QTextBrowser{background-color: #eaeaea; border:0px solid grey; border-radius: 8px;}");

    this->re_test_os_slots();
}

void Main_Page_six::init_list_widget()
{
    list = new QListWidget();
        /*listwidget按钮设置*/
    QListWidgetItem *Item_0 = new QListWidgetItem(tr("系统信息"));
    Item_0->setIcon(QIcon(":/other/os1"));
    Item_0->setTextAlignment(Qt::AlignLeft);
    Item_0->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    QListWidgetItem *Item_1 = new QListWidgetItem(tr("硬件信息"));
    Item_1->setIcon(QIcon(":/other/os2"));
    Item_1->setTextAlignment(Qt::AlignLeft);
    Item_1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    QListWidgetItem *Item_2 = new QListWidgetItem(tr("系统运行信息"));
    Item_2->setIcon(QIcon(":/other/os3"));
    Item_2->setTextAlignment(Qt::AlignLeft);
    Item_2->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    list->insertItem(0,Item_0);
    list->insertItem(1,Item_1);
    list->insertItem(2,Item_2);

    //标签字体大小
    QFont font;
    font.setPointSize(14);
    font.setUnderline(1);
    list->setFont(font);
}

void Main_Page_six::init_widget_1()
{
    widget_1 = new QWidget();
    os_info = new QLabel();
    re_test_os = new QPushButton();
    line_label_1 = new QLabel();
    line_label_1->setFixedHeight(10);
    line_label_1->installEventFilter(this);
    wid_1_show_info = new QTextBrowser();

//    os_info->setFixedSize(150,40);
//    re_test_os->setFixedSize(100,40);
    wid_1_show_info->setFixedSize(680,400);

    /*字体*/
    QFont font;
    font.setPointSize(15);
    os_info->setText(tr("系统信息详情"));
    os_info->setFont(font);
    QFont font1;
    font1.setPointSize(13);
    re_test_os->setText(tr("重新检测"));
    re_test_os->setFont(font1);
/**/


/*布局*/
    QHBoxLayout *widget_1_H_layout = new QHBoxLayout();/*水平布局*/
    widget_1_H_layout->addWidget(os_info, 0, Qt::AlignCenter);
    widget_1_H_layout->addStretch();
    widget_1_H_layout->addWidget(re_test_os, 0, Qt::AlignCenter);
    widget_1_H_layout->setContentsMargins(20, 0, 5, 5);
    QVBoxLayout *widget_1_V_layout = new QVBoxLayout();/*垂直布局*/
    widget_1_V_layout->addLayout(widget_1_H_layout);
    widget_1_V_layout->addWidget(line_label_1);
    widget_1_V_layout->addWidget(wid_1_show_info, 0, Qt::AlignCenter);
    widget_1_V_layout->setContentsMargins(0, 0, 5, 5);
    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addLayout(widget_1_V_layout);
    main_layout->setContentsMargins(0,0,0,0);

    widget_1->setLayout(main_layout);

}

void Main_Page_six::re_test_os_slots()
{
    wid_1_show_info->setText("");
    out = "";
    QString program = "bash";
    QStringList arguments;
    arguments<<"/usr/bin/otherinfo/systeminfo.sh";
    pro->start(program, arguments);
    while(pro->waitForReadyRead())
    {
        out += pro->readAll();
        wid_1_show_info->setText(out);
    }
}

void Main_Page_six::init_widget_2()
{
    widget_2 = new QWidget();
    hardware_info = new QLabel();
    re_test_hard = new QPushButton();
    more_detail_hard = new QPushButton();
    line_label_2 = new QLabel();
    line_label_2->setFixedHeight(10);
    line_label_2->installEventFilter(this);
    wid_2_show_info = new QTextBrowser();

//    hardware_info->setFixedSize(150,40);
//    re_test_hard->setFixedSize(100,40);
//    more_detail_hard->setFixedSize(100,40);
    wid_2_show_info->setFixedSize(680,400);

    /*字体*/
    QFont font;
    font.setPointSize(15);
    //this->setFont(font);
    hardware_info->setText(tr("其它硬件信息详情"));
    hardware_info->setFont(font);


    QFont font1;
    font1.setPointSize(13);
    re_test_hard->setText(tr("重新检测"));
    more_detail_hard->setText(tr("更多信息"));
    re_test_hard->setFont(font1);
    more_detail_hard->setFont(font1);
/**/
//    hardware_info->setText(tr("其它硬件信息详情"));
//    re_test_hard->setText(tr("重新检测"));
//    more_detail_hard->setText(tr("更多信息"));
/*布局*/
    QHBoxLayout *widget_2_H_layout = new QHBoxLayout();
    widget_2_H_layout->addWidget(hardware_info, 0, Qt::AlignCenter);
    widget_2_H_layout->addStretch();
    widget_2_H_layout->addWidget(re_test_hard, 0, Qt::AlignCenter);
    widget_2_H_layout->addWidget(more_detail_hard, 0, Qt::AlignCenter);
    widget_2_H_layout->setContentsMargins(20, 5, 20, 5);
    QVBoxLayout *widget_2_V_layout = new QVBoxLayout();
    widget_2_V_layout->addLayout(widget_2_H_layout);
    widget_2_V_layout->addWidget(line_label_2);
    widget_2_V_layout->addWidget(wid_2_show_info, 0, Qt::AlignCenter);
    widget_2_V_layout->setContentsMargins(0, 0, 5, 5);
    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addLayout(widget_2_V_layout);
    main_layout->setContentsMargins(0,0,0,0);

    widget_2->setLayout(main_layout);
}

void Main_Page_six::re_test_hard_slots()
{
    wid_2_show_info->setText("");
    out = "";
    QString program = "bash";
    QStringList arguments;
    arguments<<"/usr/bin/otherinfo/hardwareinfo.sh";
    pro->start(program, arguments);
    while(pro->waitForReadyRead())
    {
        out += pro->readAll();
        wid_2_show_info->setText(out);
    }
}

void Main_Page_six::more_detail_hard_slots()
{
    wid_2_show_info->setText("");
    out = "";
    if(Flag_Read_Pwd == 0)
    {
        input_pwd_widget->exec();
        if(Flag_Cancel)
            return;
        this->more_detail_hard_slots();
    }
    else if(Flag_Read_Pwd == 1)
    {
        QString Program = "bash";
        QStringList arguments;
        arguments<<"/usr/bin/otherinfo/hardwareinfomore.sh"<<PWD;
        pro->start(Program, arguments);
        while(pro->waitForFinished())
        {
            out += pro->readAll();
            wid_2_show_info->setText(out);
        }
    }
}

void Main_Page_six::init_widget_3()
{
    widget_3 = new QWidget();
    os_run_info = new QLabel();
    re_test_os_run = new QPushButton();
    more_detail_os_run = new QPushButton();
    line_label_3 = new QLabel();
    line_label_3->setFixedHeight(10);
    line_label_3->installEventFilter(this);
    wid_3_show_info = new QTextBrowser();

//    os_run_info->setFixedSize(150,40);
//    re_test_os_run->setFixedSize(100,40);
//    more_detail_os_run->setFixedSize(100,40);
    wid_3_show_info->setFixedSize(680,400);

    /*字体*/
    QFont font;
    font.setPointSize(15);
    //this->setFont(font);
    os_run_info->setFont(font);
    os_run_info->setText(tr("系统运行信息"));

    QFont font1;
    font1.setPointSize(13);
    re_test_os_run->setText(tr("重新检测"));
    more_detail_os_run->setText(tr("更多信息"));
    re_test_os_run->setFont(font1);
    more_detail_os_run->setFont(font1);
/**/
//    os_run_info->setText(tr("系统运行信息"));
//    re_test_os_run->setText(tr("重新检测"));
//    more_detail_os_run->setText(tr("更多信息"));
/*布局*/
    QHBoxLayout *widget_3_H_layout = new QHBoxLayout();
    widget_3_H_layout->addWidget(os_run_info, 0, Qt::AlignCenter);
    widget_3_H_layout->addStretch();
    widget_3_H_layout->addWidget(re_test_os_run, 0, Qt::AlignCenter);
    widget_3_H_layout->addWidget(more_detail_os_run, 0, Qt::AlignCenter);
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

void Main_Page_six::re_test_os_run_slots()
{
    wid_3_show_info->setText("");
    out = "";
    QString program = "bash";
    QStringList arguments;
    arguments<<"/usr/bin/otherinfo/systemrun.sh";
    pro->start(program, arguments);
    while(pro->waitForReadyRead())
    {
        out += pro->readAll();
        wid_3_show_info->setText(out);
    }
}
void Main_Page_six::more_detail_os_run_slots()
{
    wid_3_show_info->setText("");
    out = "";
    if(Flag_Read_Pwd == 0)
    {
        input_pwd_widget->exec();
        if(Flag_Cancel)
            return;
        this->more_detail_os_run_slots();
    }
    else if(Flag_Read_Pwd == 1)
    {
        QString Program = "bash";
        QStringList arguments;
        arguments<<"/usr/bin/otherinfo/startup.sh"<<PWD;
        pro->start(Program, arguments);
        while(pro->waitForFinished())
        {
            out += pro->readAll();
            wid_3_show_info->setText(out);
        }
    }
}

bool Main_Page_six::eventFilter(QObject *obj, QEvent *event)
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
    if(obj == line_label_2)
    {
        if(event->type() == QEvent::Paint)
        {
            int label_height = line_label_2->height();
            int label_width = line_label_2->width();
            QPainter painter(line_label_2);//QPainter类低水平的绘制，例如在窗口部件上
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
    return QWidget::eventFilter(obj, event);
}

void Main_Page_six::init_widget_bash(int n)
{
    if(n == 0)
        this->re_test_os_slots();
    else
    {
        if(n == 1)
        this->re_test_hard_slots();
        else
        {
            if(n == 2)
            this->re_test_os_run_slots();
        }
    }
}
