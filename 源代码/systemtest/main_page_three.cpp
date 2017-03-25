#include "main_page_three.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>

Main_Page_three::Main_Page_three(QWidget *parent) :
    QWidget(parent)
{
    pro = new QProcess();
    out = "";

    list = new QListWidget();
    stack = new QStackedWidget();
    work_window = new QWidget();
    test_options = new QLabel();
    re_test = new QPushButton();
    show_msg = new QTextBrowser();
    Input_Pwd_Widget = new Input_Pwd();
    /*listwidget按钮设置*/
    QListWidgetItem *zero = new QListWidgetItem();//新建对象
    zero->setIcon(QIcon(":/page_two/cpu1"));//设置图标
    zero->setText(tr("内存基本信息"));
    zero->setTextAlignment(Qt::AlignLeft);
    zero->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);

    QListWidgetItem *one = new QListWidgetItem();
    one->setIcon(QIcon(":/page_two/cpu2"));
    one->setText(tr("内存核心概要"));
    one->setTextAlignment(Qt::AlignLeft);
    one->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);

    list->insertItem(0,zero);
    list->insertItem(1,one);
 /*init_work_window 布局*/
    line_label = new QLabel();
    line_label->setFixedHeight(10);
    line_label->installEventFilter(this);//eventFilter
        /*控件大小*/
    //test_options->setFixedSize(150,40);
    //re_test->setFixedSize(100,40);
    show_msg->setFixedSize(680,400);
    /*default */
    test_options->setText(tr("内存信息详情"));
    QFont font1;
    font1.setPointSize(13);

    re_test->setText(tr("刷新"));
    re_test->setFont(font1);

//    show_msg->setFixedSize();
    QHBoxLayout *H_layout = new QHBoxLayout();
    H_layout->addWidget(test_options, 0, Qt::AlignCenter);
    H_layout->addStretch();
    H_layout->addWidget(re_test, 0, Qt::AlignCenter);
    H_layout->setContentsMargins(20,5,20,5);
    QVBoxLayout *V_layout = new QVBoxLayout();
    V_layout->addLayout(H_layout);
    V_layout->addWidget(line_label);
    V_layout->addWidget(show_msg, 0, Qt::AlignCenter);
    V_layout->setContentsMargins(0,0,5,5);
    QHBoxLayout *work_layout = new QHBoxLayout();
    work_layout->addLayout(V_layout);
    work_layout->setContentsMargins(0,0,0,0);

    work_window->setLayout(work_layout);

    stack->addWidget(work_window);
    stack->addWidget(work_window);

    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addWidget(list);
    main_layout->addWidget(stack);
    main_layout->setStretchFactor(list, 1);
    main_layout->setStretchFactor(stack, 4);
    main_layout->setContentsMargins(0,0,0,0);
    setLayout(main_layout);

    connect(list, SIGNAL(currentRowChanged(int)), stack, SLOT(setCurrentIndex(int)));
    connect(list, SIGNAL(currentRowChanged(int)), this, SLOT(change_widget_cfg(int)));//页面切换时候修改页面配置
    connect(pro, SIGNAL(readyReadStandardOutput()), this, SLOT(show_msg_to_browser()));//读取标准输出
    connect(re_test, SIGNAL(clicked()), this, SLOT(flush_msg()));//重新检测按钮  重新检测

    /*配色*/
    this->setAutoFillBackground(true);
    //标签字体大小
    QFont font;
    font.setPointSize(15);
    test_options->setFont(font);

    QFont font2;
    font2.setPointSize(14);
    font2.setUnderline(1);
    list->setFont(font2);

    this->setAutoFillBackground(true);

    list->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;background-color:#eaeaea");

    this->setStyleSheet("QTextBrowser{background-color: #eaeaea; border:0px solid grey; border-radius: 8px;}");

    current_bash = 0;
    this->flush_msg();
}

void Main_Page_three::change_widget_cfg(int n)
{
    /*
    if( Flag_Read_Pwd == 0 ) //检测标志位  密码是否存在|正确
    {
        Input_Pwd_Widget->exec();
        if( Flag_Cancel == 1 ) //如果是取消后返回,则退出
            return;
        change_widget_cfg(n);
    }
    else{
        if (Flag_Read_Pwd == 1)
        {*/
            current_bash = n;//设置标志位(当前页面)
            switch(n)
            {
                case 0:
                {
                    test_options->setText(tr("内存信息详情"));
                    re_test->setText(tr("重新检测"));
                    show_msg->setText("");
                    current_bash = n;
                    out = "";
                    QString program = "bash";
                    QStringList arguments;
                    arguments<<"/usr/bin/mem_show/mem_show1.sh";
                    pro->start(program, arguments);
                    while(true == pro->waitForFinished());
                    break;
                }
                case 1:
                {
                    test_options->setText(tr("内存核心信息详情"));
                    re_test->setText(tr("刷新"));
                    show_msg->setText("");
                    if( Flag_Read_Pwd == 0 ) //检测标志位  密码是否存在|正确
                    {
                        Input_Pwd_Widget->exec();
                        if( Flag_Cancel == 1 ) //如果是取消后返回,则退出
                            return;
                        change_widget_cfg(n);
                    }
                    out = "";
                    QString program = "bash";
                    QStringList arguments;
                    arguments<<"/usr/bin/mem_show/mem_show2.sh"<<PWD;
                    pro->start(program, arguments);
                    while(true == pro->waitForFinished());
                    break;
                }
            }
//        }
//    }
}

bool Main_Page_three::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == line_label)
    {
        if(event->type() == QEvent::Paint)
        {
            int label_height = line_label->height();
            int label_width = line_label->width();
            QPainter painter(line_label);//QPainter类低水平的绘制，例如在窗口部件上
            painter.setPen(QPen(QColor(200, 200, 200), 2, Qt::SolidLine));//绘笔
            painter.drawLine(0, label_height/2, label_width, label_height/2);	//绘
        }
    }
    return QWidget::eventFilter(obj, event);
}


void Main_Page_three::show_msg_to_browser()
{
    out += pro->readAll();
    show_msg->setText(out);
}

void Main_Page_three::flush_msg()
{
    this->change_widget_cfg(current_bash);
}
