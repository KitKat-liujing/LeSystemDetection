#include "main_page_two.h"
#include <QVBoxLayout>
#include <QFont>

My_Obj_Flush_Cpu::My_Obj_Flush_Cpu()
{
    proc = new QProcess();
    out = "";
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(Flush_cpu_info()));
    timer->start(500);
}
void My_Obj_Flush_Cpu::Flush_cpu_info()
{
    out = "";
    QString program = "bash";
    QStringList arguments;
    arguments<<"/usr/bin/cpu_show/cpu_show2.sh";
    proc->start(program, arguments);
    while(true == proc->waitForFinished())
    {
        out += proc->readAll().trimmed();
    }
    emit send_cpu_info(out);
}

My_Obj_Test_Cpu::My_Obj_Test_Cpu()
{
    proc = new QProcess();
    out = "";
}
void My_Obj_Test_Cpu::start_test_cpu()
{
    out = "";
    emit send_cpu_info("正在检测，请耐心等待...");
    QString program = "bash";
    QStringList arguments;
    arguments<<"/usr/bin/cpu_show/cpu_cal_rate.sh";
    proc->start(program, arguments);
    while(!proc->waitForFinished(0))
    {
        out += proc->readAll();
    }
    emit send_cpu_info(out);
}

Main_Page_two::Main_Page_two(QWidget *parent) :
    QWidget(parent)
{
    /*初始化窗口*/
    init_list_widget();
    init_widget_1();
    init_widget_2();
    /*设置堆栈窗口*/
    stack = new QStackedWidget();
    stack->addWidget(widget_1);
    stack->addWidget(widget_2);

    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addWidget(list);
    main_layout->addWidget(stack);
    main_layout->setStretchFactor(list, 1);
    main_layout->setStretchFactor(stack, 4);
    main_layout->setContentsMargins(0,0,0,0);
    setLayout(main_layout);

    pro = new QProcess();
    out = "";
    My_Obj_Flush_Cpu_object = new My_Obj_Flush_Cpu();
    thread_flush_cpu = new QThread();
    My_Obj_Flush_Cpu_object->moveToThread(thread_flush_cpu);
    thread_flush_cpu->start();
    My_Obj_Test_Cpu_object = new My_Obj_Test_Cpu();
    thread_test_cpu = new QThread();
    thread_test_cpu->start();
    My_Obj_Test_Cpu_object->moveToThread(thread_test_cpu);

    connect(list, SIGNAL(currentRowChanged(int)), stack, SLOT(setCurrentIndex(int)));
    connect(list, SIGNAL(currentRowChanged(int)), this, SLOT(init_bash(int)));
    connect(My_Obj_Flush_Cpu_object, SIGNAL(send_cpu_info(QString)), this, SLOT(Flush_Cpu_Rate(QString)));
    connect(My_Obj_Test_Cpu_object, SIGNAL(send_cpu_info(QString)), this, SLOT(Set_Test_cpu(QString)));
    connect(re_test_cpu_2, SIGNAL(clicked()), My_Obj_Test_Cpu_object, SLOT(start_test_cpu()));

    this->setAutoFillBackground(true);
    list->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;background-color:#eaeaea");
    this->setStyleSheet("QTextBrowser{background-color: #eaeaea; border:0px solid grey; border-radius: 8px;}");

    this->re_test_cpu_1_slots();
}
void Main_Page_two::init_list_widget()
{
    list = new QListWidget();
        /*listwidget按钮设置*/
    QListWidgetItem *Item_0 = new QListWidgetItem(tr("cpu基本信息"));
    Item_0->setIcon(QIcon(":/page_two/cpu1"));
    Item_0->setTextAlignment(Qt::AlignLeft);
    Item_0->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    QListWidgetItem *Item_1 = new QListWidgetItem(tr("cpu性能检测"));
    Item_1->setIcon(QIcon(":/page_two/cpu2"));
    Item_1->setTextAlignment(Qt::AlignLeft);
    Item_1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    list->insertItem(0,Item_0);
    list->insertItem(1,Item_1);
    //标签字体大小
    QFont font;
    font.setPointSize(14);
    font.setUnderline(1);
    list->setFont(font);
}

void Main_Page_two::init_widget_1()
{
    widget_1 = new QWidget();
    cpu_info_1 = new QLabel();
    re_test_cpu_1 = new QPushButton();
    line_label_1 = new QLabel();
    line_label_1->setFixedHeight(5);
    line_label_1->installEventFilter(this);
    wid_1_show_info = new QTextBrowser();

//    cpu_info_1->setFixedSize(150,40);
//    re_test_cpu_1->setFixedSize(100,40);
    wid_1_show_info->setFixedSize(680,400);

    /*字体*/
    QFont font;
    font.setPointSize(15);
    //this->setFont(font);


    QFont font1;
    font1.setPointSize(13);

/**/
    cpu_info_1->setText(tr("cpu详情检测"));
    cpu_info_1->setFont(font);

    re_test_cpu_1->setText(tr("重新检测"));
     re_test_cpu_1->setFont(font1);
/*布局*/
    QHBoxLayout *widget_1_H_layout = new QHBoxLayout();/*水平布局*/
    widget_1_H_layout->addWidget(cpu_info_1, 0, Qt::AlignCenter);
    widget_1_H_layout->addStretch();
    widget_1_H_layout->addWidget(re_test_cpu_1, 0, Qt::AlignCenter);
    widget_1_H_layout->setContentsMargins(20, 5, 20, 5);
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

void Main_Page_two::re_test_cpu_1_slots()
{
    out = "";
    QString program = "bash";
    QStringList arguments;
    arguments<<"/usr/bin/cpu_show/cpu_show1.sh";
    pro->start(program, arguments);
    while(true == pro->waitForFinished())
    {
        out += pro->readAll().trimmed();
        wid_1_show_info->setText(out);
    }
}

void Main_Page_two::init_widget_2()
{
    widget_2 = new QWidget();
    cpu_info_2_1 = new QLabel();
    cpu_info_2_2 = new QLabel();
    re_test_cpu_2 = new QPushButton();
    line_label_2_1 = new QLabel();
    line_label_2_2 = new QLabel();
    line_label_2_1->setFixedHeight(4);
    line_label_2_1->installEventFilter(this);
    line_label_2_2->setFixedHeight(4);
    line_label_2_2->installEventFilter(this);
    wid_2_show_info_1 = new QTextBrowser();
    wid_2_show_info_2 = new QTextBrowser();

    wid_2_show_info_1->setFixedSize(680, 260);
    wid_2_show_info_2->setFixedSize(680, 80);
    /*字体*/
    QFont font;
    font.setPointSize(13);
    //this->setFont(font);
    QFont font1;
    font1.setPointSize(15);
    cpu_info_2_1->setFont(font1);
    cpu_info_2_2->setFont(font1);
    re_test_cpu_2->setFont(font);
/**/
    cpu_info_2_1->setText(tr("cpu性能检测"));
    cpu_info_2_2->setText(tr("cpu运算能力检测(浮点运算)"));
    re_test_cpu_2->setText(tr("开始检测"));
/*布局*/
    QHBoxLayout *widget_2_H_layout_1= new QHBoxLayout();/*水平布局*/
    widget_2_H_layout_1->addWidget(cpu_info_2_1, 0, Qt::AlignCenter);
    widget_2_H_layout_1->addStretch();
    widget_2_H_layout_1->setContentsMargins(20, 5, 20, 0);
    QHBoxLayout *widget_2_H_layout_2 = new QHBoxLayout();
    widget_2_H_layout_2->addWidget(cpu_info_2_2, 0, Qt::AlignCenter);
    widget_2_H_layout_2->addStretch();
    widget_2_H_layout_2->addWidget(re_test_cpu_2, 0, Qt::AlignCenter);
    widget_2_H_layout_2->setContentsMargins(20,0,25,0);
    QVBoxLayout *widget_2_V_layout = new QVBoxLayout();/*垂直布局*/
    widget_2_V_layout->addLayout(widget_2_H_layout_1);
    widget_2_V_layout->addWidget(line_label_2_1);
    widget_2_V_layout->addWidget(wid_2_show_info_1, 0, Qt::AlignCenter);
    widget_2_V_layout->addLayout(widget_2_H_layout_2);
    widget_2_V_layout->addWidget(line_label_2_2);
    widget_2_V_layout->addWidget(wid_2_show_info_2, 0, Qt::AlignCenter);
    widget_2_V_layout->setContentsMargins(0, 0, 5, 5);
    widget_2_V_layout->addStretch();
    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addLayout(widget_2_V_layout);
    main_layout->setContentsMargins(0,0,0,0);

    widget_2->setLayout(main_layout);
}
void Main_Page_two::Flush_Cpu_Rate(QString str)
{
    wid_2_show_info_1->setText(str);
}
void Main_Page_two::Set_Test_cpu(QString str)
{
    wid_2_show_info_2->setText(str);
}


bool Main_Page_two::eventFilter(QObject *obj, QEvent *event)
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
    if(obj == line_label_2_1)
    {
        if(event->type() == QEvent::Paint)
        {
            int label_height = line_label_2_1->height();
            int label_width = line_label_2_1->width();
            QPainter painter(line_label_2_1);//QPainter类低水平的绘制，例如在窗口部件上
            painter.setPen(QPen(QColor(200, 200, 200), 2, Qt::SolidLine));//绘笔
            painter.drawLine(0, label_height/2, label_width, label_height/2);	//绘
        }
    }
    if(obj == line_label_2_2)
    {
        if(event->type() == QEvent::Paint)
        {
            int label_height = line_label_2_2->height();
            int label_width = line_label_2_2->width();
            QPainter painter(line_label_2_2);//QPainter类低水平的绘制，例如在窗口部件上
            painter.setPen(QPen(QColor(200, 200, 200), 2, Qt::SolidLine));//绘笔
            painter.drawLine(0, label_height/2, label_width, label_height/2);	//绘
        }
    }

    return QWidget::eventFilter(obj, event);
}

void Main_Page_two::init_bash(int n)
{
    if( n == 0)
        this->re_test_cpu_1_slots();

}
