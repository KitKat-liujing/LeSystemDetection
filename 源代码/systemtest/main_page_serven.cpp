#include "main_page_serven.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextBrowser>
#include <QLabel>
#include <QBitmap>
#include <QPainter>
#include <QEvent>

main_page_serven::main_page_serven(QWidget *parent) : QWidget(parent)
{
    input_pwd_widget = new Input_Pwd();
    pro = new QProcess();
    init_widget1();
    init_widget2();
    init_widget3();
    init_widget4();
    init_widget5();
    init_widget6();

//    this->show_edit_1();
//    this->show_edit_2();
//    this->show_edit_3();
    list = new QListWidget();
        /*listwidget按钮设置*/
    QListWidgetItem *Item_1 = new QListWidgetItem(tr("安全检测"));
    Item_1->setIcon(QIcon(":/page_serven/security_1"));
    Item_1->setTextAlignment(Qt::AlignLeft);
    Item_1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    QListWidgetItem *Item_2= new QListWidgetItem(tr("权限扫描"));
    Item_2->setIcon(QIcon(":/page_serven/security_2"));
    Item_2->setTextAlignment(Qt::AlignLeft);
    Item_2->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    QListWidgetItem *Item_3= new QListWidgetItem(tr("md5校验"));
    Item_3->setIcon(QIcon(":/page_serven/security_3"));
    Item_3->setTextAlignment(Qt::AlignLeft);
    Item_3->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    QListWidgetItem *Item_4 = new QListWidgetItem(tr("/bin"));
    Item_4->setIcon(QIcon(":/page_serven/security_4"));
    Item_4->setTextAlignment(Qt::AlignLeft);
    Item_4->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    QListWidgetItem *Item_5 = new QListWidgetItem(tr("/usr"));
    Item_5->setIcon(QIcon(":/page_serven/security_4"));
    Item_5->setTextAlignment(Qt::AlignLeft);
    Item_5->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    QListWidgetItem *Item_6 = new QListWidgetItem(tr("/usr/local"));
    Item_6->setIcon(QIcon(":/page_serven/security_4"));
    Item_6->setTextAlignment(Qt::AlignLeft);
    Item_6->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    list->insertItem(0,Item_1);
    list->insertItem(1,Item_2);
    list->insertItem(2,Item_3);
    list->insertItem(3,Item_4);
    list->insertItem(4,Item_5);
    list->insertItem(5,Item_6);
    //标签字体大小
    QFont font;
    font.setPointSize(14);
    font.setUnderline(1);
    list->setFont(font);

    /*设置堆栈窗口*/
    stack = new QStackedWidget();


    stack->addWidget(widget_1);
    stack->addWidget(widget_2);
    stack->addWidget(widget_3);
    stack->addWidget(widget_4);
    stack->addWidget(widget_5);
    stack->addWidget(widget_6);

    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addWidget(list);
    main_layout->addWidget(stack);
    main_layout->setStretchFactor(list, 1);
    main_layout->setStretchFactor(stack, 4);
    main_layout->setContentsMargins(0,0,0,0);
    setLayout(main_layout);

    connect(list, SIGNAL(currentRowChanged(int)), stack, SLOT(setCurrentIndex(int)));
    connect(list, SIGNAL(currentRowChanged(int)), this, SLOT(init_bash(int)));//获取页面切换信号  设置页面初始化信息

    this->setAutoFillBackground(true);
    list->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;background-color:#eaeaea");
    this->setStyleSheet("QTextBrowser{background-color: #eaeaea; border:0px solid grey; border-radius: 8px;}");


}

main_page_serven::~main_page_serven()
{

}
void main_page_serven::init_widget1()
{
    widget_1 = new QWidget();
    QFont ft;
    ft.setPointSize(15);
    QLabel *label_1 = new QLabel("安全检测登录状态");
    label_1->setFont(ft);
    QPushButton *button_1 = new QPushButton("重新检测");
    QFont ft1;
    ft1.setPointSize(13);
    button_1->setFont(ft1);
    QHBoxLayout *layout_1 = new QHBoxLayout();
    layout_1->addWidget(label_1);
    layout_1->addStretch();
    layout_1->addWidget(button_1);
    layout_1-> setContentsMargins(20, 5, 20, 5);

    broswer_1 = new QTextBrowser();
    line_0 = new QLabel();
    line_0 ->setFixedSize(680,20);
    line_0->installEventFilter(this);

    QLabel *label_2 = new QLabel("检测木马后门程序");
    label_2->setFont(ft);
    QPushButton *button_2 = new QPushButton("重新检测");
    button_2->setFont(ft1);
    QHBoxLayout *layout_2 = new QHBoxLayout();
    layout_2->addWidget(label_2);
    layout_2->addStretch();
    layout_2->addWidget(button_2);
    layout_2->setContentsMargins(20, 5, 20, 5);


    broswer_2 = new QTextBrowser();

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addLayout(layout_1);
    main_layout->addWidget(broswer_1);
    main_layout->addWidget(line_0);
    main_layout->addLayout(layout_2);
    main_layout->addWidget(broswer_2);
    main_layout->setContentsMargins(20,5,20,5);
    widget_1->setLayout(main_layout);
    connect(button_1,SIGNAL(clicked()),this,SLOT(user_show_1()));
    connect(button_2,SIGNAL(clicked()),this,SLOT(user_show_2()));
    this->user_show_1();
    this->user_show_2();

}
void main_page_serven::user_show_1()
{
    broswer_1->setText("");
    //pro = new QProcess();
    out = "";
    QString program = "bash";
    QStringList arguments;
    arguments<<"/usr/bin/security/1/1.sh";
    pro->start(program, arguments);
    while(pro->waitForReadyRead())
    {
        out += pro->readAll();
        broswer_1->setText(out);
    }
}
void main_page_serven::user_show_2()
{
    broswer_2->setText("");
    //pro = new QProcess();
    out = "";
    QString program = "bash";
    QStringList arguments;
    arguments<<"/usr/bin/security/1/2.sh";
    pro->start(program, arguments);
    while(pro->waitForReadyRead())
    {
        out += pro->readAll();
        broswer_2->setText(out);
    }
}
void  main_page_serven::init_widget2()
{
    widget_2 = new QWidget();
    //widget_1->setContentsMargins(0,0,100,80);
    QFont ft;
    ft.setPointSize(15);
    QLabel *label = new QLabel("监测目录匹配权限");
    label->setFont(ft);

    QFont ft1;
    ft1.setPointSize(13);
    button_1 = new QPushButton("监测目录");
    button_2 = new QPushButton("权限匹配");
    button_1->setFont(ft1);
    button_2->setFont(ft1);
    layout_1 = new QHBoxLayout();
    layout_1->addWidget(label);
    layout_1->addStretch();
    layout_1->addWidget(button_1);
    layout_1->addWidget(button_2);
    layout_1->setContentsMargins(20, 5, 20, 5);
    text_1 = new QTextBrowser();
    text_1->setFixedSize(700,500);
    layout_2 = new QVBoxLayout();
    layout_2->addLayout(layout_1);
    //layout_2->addStretch();
    layout_2->addWidget(text_1,0,Qt::AlignCenter);
    layout_2->addStretch();
    layout_2->setContentsMargins(20,5,20,5);
    connect(button_1,SIGNAL(clicked()),this,SLOT(dentry()));
    connect(button_2,SIGNAL(clicked()),this,SLOT(compare()));
    widget_2->setLayout(layout_2);
    this->dentry();
}
void main_page_serven::dentry()
{
    text_1->setText("");
    //pro = new QProcess();
    out = "";
    QString program = "bash";
    QStringList arguments;
    arguments<<"/usr/bin/security/2/1.sh";
    pro->start(program, arguments);
    while(pro->waitForReadyRead())
    {
        out += pro->readAll();
        text_1->setText(out);
    }
}
void main_page_serven::compare()
{
    text_1->setText("");
    //pro = new QProcess();
    out = "";
    QString program = "bash";
    QStringList arguments;
    arguments<<"/usr/bin/security/2/2.sh";
    pro->start(program, arguments);
    while(pro->waitForReadyRead())
    {
        out += pro->readAll();
        text_1->setText(out);
    }
}
void main_page_serven::init_widget3()
{
    widget_3 = new QWidget();
    QFont font;
    font.setPointSize(15);
    this->setFont(font);
        //widget_2_label_1->setFont(ft);
    QLabel *label_1 = new QLabel(tr("md5值监测目录"));
    label_1->setFixedHeight(30);
    label_1->setFont(font);
    QFont font1;
    font1.setPointSize(13);
    QPushButton *button = new QPushButton("重新检测");
    button->setFont(font1);
    QHBoxLayout *layout_1 = new QHBoxLayout();
    layout_1->addWidget(label_1);
    layout_1->addStretch();
    layout_1->addWidget(button);
    layout_1->setContentsMargins(20, 5, 20, 5);

    line_1 = new QLabel();
    line_1 ->setFixedSize(600,20);
    line_1->installEventFilter(this);

    line_2 = new QLabel();
    line_2 ->setFixedSize(600,20);
    line_2->installEventFilter(this);


    line_3 = new QLabel();
    line_3 ->setFixedSize(600,20);
    line_3->installEventFilter(this);

    edit_1 = new QTextBrowser();
    edit_2 = new QTextBrowser();
    edit_3 = new QTextBrowser();
    QVBoxLayout *layout_2 = new QVBoxLayout();
    layout_2->addLayout(layout_1);
    layout_2->addWidget(line_1);
    layout_2->addWidget(edit_1);
    layout_2->addWidget(line_2);
    layout_2->addWidget(edit_2);
    layout_2->addWidget(line_3);
    layout_2->addWidget(edit_3);
    layout_2->setContentsMargins(20,5,20,5);
    widget_3->setLayout(layout_2);

}
bool main_page_serven::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == line_0)
    {
        if(event->type() == QEvent::Paint)
        {
            int width = line_0->width();
            int height = line_0->height();
            QPainter painter(line_0);
            painter.setPen(QPen(QColor(220, 220, 220), 3, Qt::DashLine));
            painter.drawLine(0,height/2,width,height/2);
        }
    }
    if(obj == line_1)
    {
        if(event->type() == QEvent::Paint)
        {
            int width = line_1->width();
            int height = line_1->height();
            QPainter painter(line_1);
            painter.setPen(QPen(QColor(220, 220, 220), 3, Qt::DashLine));
            painter.drawLine(0,height/2,width,height/2);
        }
    }
    if(obj == line_2)
    {
        if(event->type() == QEvent::Paint)
        {
            int width = line_2->width();
            int height = line_2->height();
            QPainter painter(line_2);
            painter.setPen(QPen(QColor(220, 220, 220), 3, Qt::DashLine));
            painter.drawLine(0,height/2,width,height/2);
        }
    }
    if(obj == line_3)
    {
        if(event->type() == QEvent::Paint)
        {
            int width = line_3->width();
            int height = line_3->height();
            QPainter painter(line_3);
            painter.setPen(QPen(QColor(220, 220, 220), 3, Qt::DashLine));
            painter.drawLine(0,height/2,width,height/2);
        }
    }
    return QWidget::eventFilter(obj, event);
}
void main_page_serven::show_edit_1()
{
    if( Flag_Read_Pwd == 0 )
    {
        input_pwd_widget->exec();
        if( Flag_Cancel == 1 )
            return;
        show_edit_1();
    }
    else if( Flag_Read_Pwd == 1)
    {

        out = "";
        QString program = "bash";
        QStringList arguments;
        arguments<<"/usr/bin/security/3/part1.sh"<<PWD;
        pro->start(program, arguments);
        while(true == pro->waitForFinished())
        {
            out += pro->readAll().trimmed();
            edit_1->setText(out);
        }
        out = "";
         QStringList arguments1;
        arguments1<<"/usr/bin/security/3/part2.sh"<<PWD;
        pro->start(program, arguments1);
        while(true == pro->waitForFinished())
        {
            out += pro->readAll().trimmed();
            edit_2->setText(out);
        }
        out = "";
         QStringList arguments2;
        arguments2<<"/usr/bin/security/3/part3.sh"<<PWD;
        pro->start(program, arguments2);
        while(true == pro->waitForFinished())
        {
            out += pro->readAll().trimmed();
            edit_3->setText(out);
        }
    }
}
void main_page_serven::init_widget4()
{
    QFont font;
    font.setPointSize(16);
    this->setFont(font);
        //widget_2_label_1->setFont(ft);
    QLabel *label_1 = new QLabel(tr("/bin"));
    label_1->setFixedHeight(30);
    label_1->setFont(font);

    widget_4 = new QWidget();

    QHBoxLayout *layout_2 = new QHBoxLayout();
    QPushButton *h_button_1 = new QPushButton("一键监测");
    //h_button_1->setStyleSheet("QPushButton{ font-family:'Microsoft YaHei';font-size:15px;color:#00BBFF;}");
    connect(h_button_1,SIGNAL(clicked()),this,SLOT(check1()));
    QPushButton *h_button_2 = new QPushButton("一键匹配");
    //h_button_2->setStyleSheet("QPushButton{ font-family:'Microsoft YaHei';font-size:15px;color:#00BBFF;}");
    connect(h_button_2,SIGNAL(clicked()),this,SLOT(compare1()));
//    QPushButton *h_button_3 = new QPushButton("删除备份");
//    h_button_3->setStyleSheet("QPushButton{ font-family:'Microsoft YaHei';font-size:15px;color:#00BBFF;}");
//    connect(h_button_3,SIGNAL(clicked()),this,SLOT(remove1()));
    layout_2->addStretch();
    layout_2->addWidget(h_button_1);
    layout_2->addWidget(h_button_2);
   // layout_2->addWidget(h_button_3);

    widget4_text = new QTextBrowser();
    QVBoxLayout *layout_3 = new QVBoxLayout();
    layout_3->addLayout(layout_2);
    layout_3->setContentsMargins(20,5,20,5);
    layout_3->addWidget(widget4_text);

    widget_4->setLayout(layout_3);
}

void main_page_serven::check1()
{
    if( Flag_Read_Pwd == 0 )
    {
        input_pwd_widget->exec();
        if( Flag_Cancel == 1 )
            return;
        check1();
    }
    else if( Flag_Read_Pwd == 1)
    {

        out = "";
        QString program = "bash";
        QStringList arguments;
        arguments<<"/usr/bin/security/4/part1.sh"<<PWD;
        //pro = new QProcess();
        pro->start(program, arguments);
        while(true == pro->waitForFinished())
        {
            out += pro->readAll().trimmed();
            widget4_text->setText(out);
        }
    }
}
void main_page_serven::compare1()
{
    if( Flag_Read_Pwd == 0 )
    {
        input_pwd_widget->exec();
        if( Flag_Cancel == 1 )
            return;
        compare1();
    }
    else if( Flag_Read_Pwd == 1)
    {

        out = "";
        QString program = "bash";
        QStringList arguments;
        arguments<<"/usr/bin/security/4/test1.sh"<<PWD;
        //pro = new QProcess();
        pro->start(program, arguments);
       while(true == pro->waitForFinished())
        {
            out += pro->readAll().trimmed();
            widget4_text->setText(out);
        }
    }
}

void main_page_serven::init_widget5()
{
    widget_5 = new QWidget();
    QFont font;
    font.setPointSize(16);
    this->setFont(font);
        //widget_2_label_1->setFont(ft);
    QLabel *label_1 = new QLabel(tr("/usr"));
    label_1->setFixedHeight(30);
    label_1->setFont(font);
    //QLabel *tips = new QLabel("正在检测，请耐心等待...");
    QHBoxLayout *layout_2 = new QHBoxLayout();
    QPushButton *h_button_1 = new QPushButton("一键监测");
    //h_button_1->setStyleSheet("QPushButton{ font-family:'Microsoft YaHei';font-size:15px;color:#00BBFF;}");
    connect(h_button_1,SIGNAL(clicked()),this,SLOT(check2()));
    QPushButton *h_button_2 = new QPushButton("一键匹配");
    connect(h_button_2,SIGNAL(clicked()),this,SLOT(compare2()));
    //h_button_2->setStyleSheet("QPushButton{ font-family:'Microsoft YaHei';font-size:15px;color:#00BBFF;}");
//    QPushButton *h_button_3 = new QPushButton("删除备份");
//    h_button_3->setStyleSheet("QPushButton{ font-family:'Microsoft YaHei';font-size:15px;color:#00BBFF;}");
    //layout_2->addWidget(tips);
    layout_2->addStretch();
    layout_2->addWidget(h_button_1);
    layout_2->addWidget(h_button_2);
   // layout_2->addWidget(h_button_3);

    widget5_text= new QTextBrowser();
    QVBoxLayout *layout_3 = new QVBoxLayout();
    layout_3->addLayout(layout_2);
    layout_3->addWidget(widget5_text);
    layout_3->setContentsMargins(20,5,20,5);

    widget_5->setLayout(layout_3);

}
void main_page_serven::check2()
{
    if( Flag_Read_Pwd == 0 )
    {
        input_pwd_widget->exec();
        if( Flag_Cancel == 1 )
            return;
        check2();
    }
    else if( Flag_Read_Pwd == 1)
    {

        out = "";
        QString program = "bash";
        QStringList arguments;
        arguments<<"/usr/bin/security/5/part1.sh"<<PWD;
        //pro = new QProcess();
        pro->start(program, arguments);
        while(true == pro->waitForFinished())
        {
            out += pro->readAll().trimmed();
            widget5_text->setText(out);
        }
    }
}
void main_page_serven::compare2()
{
    if( Flag_Read_Pwd == 0 )
    {
        input_pwd_widget->exec();
        if( Flag_Cancel == 1 )
            return;
        compare1();
    }
    else if( Flag_Read_Pwd == 1)
    {

        out = "";
        QString program = "bash";
        QStringList arguments;
        arguments<<"/usr/bin/security/5/test1.sh"<<PWD;
        //pro = new QProcess();
        pro->start(program, arguments);
       while(true == pro->waitForFinished())
        {
            out += pro->readAll().trimmed();
            widget5_text->setText(out);
        }
    }
}
void main_page_serven::init_widget6()
{
    widget_6 = new QWidget();
    QFont font;
    font.setPointSize(16);
    this->setFont(font);
        //widget_2_label_1->setFont(ft);
    QLabel *label_1 = new QLabel(tr("/usr/local"));
    label_1->setFixedHeight(30);
    label_1->setFont(font);
    QHBoxLayout *layout_2 = new QHBoxLayout();
    QPushButton *h_button_1 = new QPushButton("一键监测");
    //h_button_1->setStyleSheet("QPushButton{ font-family:'Microsoft YaHei';font-size:15px;color:#00BBFF;}");
    connect(h_button_1,SIGNAL(clicked()),this,SLOT(check3()));
    QPushButton *h_button_2 = new QPushButton("一键匹配");
    //h_button_2->setStyleSheet("QPushButton{ font-family:'Microsoft YaHei';font-size:15px;color:#00BBFF;}");
    connect(h_button_2,SIGNAL(clicked()),this,SLOT(compare3()));
    //QPushButton *h_button_3 = new QPushButton("删除备份");
    //h_button_3->setStyleSheet("QPushButton{ font-family:'Microsoft YaHei';font-size:15px;color:#00BBFF;}");
    layout_2->addStretch();
    layout_2->addWidget(h_button_1);
    layout_2->addWidget(h_button_2);
     //layout_2->addWidget(h_button_3);

    widget6_text = new QTextBrowser();
    QVBoxLayout *layout_3 = new QVBoxLayout();
    layout_3->addLayout(layout_2);
    layout_3->addWidget(widget6_text);
    layout_3->setContentsMargins(20,5,20,5);
    widget_6->setLayout(layout_3);

}
void main_page_serven::check3()
{
    if( Flag_Read_Pwd == 0 )
    {
        input_pwd_widget->exec();
        if( Flag_Cancel == 1 )
            return;
        check3();
    }
    else if( Flag_Read_Pwd == 1)
    {

        out = "";
        QString program = "bash";
        QStringList arguments;
        arguments<<"/usr/bin/security/6/part1.sh"<<PWD;
        //pro = new QProcess();
        pro->start(program, arguments);
        while(true == pro->waitForFinished())
        {
            out += pro->readAll().trimmed();
            widget6_text->setText(out);
        }
    }
}
void main_page_serven::compare3()
{
    if( Flag_Read_Pwd == 0 )
    {
        input_pwd_widget->exec();
        if( Flag_Cancel == 1 )
            return;
        compare1();
    }
    else if( Flag_Read_Pwd == 1)
    {

        out = "";
        QString program = "bash";
        QStringList arguments;
        arguments<<"/usr/bin/security/6/test1.sh"<<PWD;
        //pro = new QProcess();
        pro->start(program, arguments);
       while(true == pro->waitForFinished())
        {
            out += pro->readAll().trimmed();
            widget6_text->setText(out);
        }
    }
}
void main_page_serven::init_bash(int n)
{
    if(n == 2)
        this->show_edit_1();
}
