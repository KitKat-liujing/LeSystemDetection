#include "main_page_one.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDesktopWidget>
#include <QApplication>
#include <QPainter>
#include <QtTest/QtTest>
#include "common.h"

Main_Page_One::Main_Page_One(QWidget *parent) :
    QDialog(parent)
{
    this->initLeft();
    this->initRightTop();
    this->initRightCenter();
    this->initRightBottom();
    this->initRight();

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
    pro = new QProcess();
    out = "";


    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addWidget(main_splitter);
    main_layout->setSpacing(0);//空隙
    main_layout->setContentsMargins(0, 0, 0, 0);/*这是设置一个元素所有外边距的宽度，
                                                                                    或者设置各边上外边距的宽度 */

    this->setLayout(main_layout);//将main_layout设置为当前widget的布局

    connect(sys_test_button, SIGNAL(clicked()), this, SIGNAL(go_sys_test_page()));
    this->home_btime();
}

Main_Page_One::~Main_Page_One()
{
}

void Main_Page_One::initLeft()
{
    left_widget = new QWidget();
    label = new QLabel();//图片
    time_label = new QLabel();
    sys_test_button = new QPushButton();//检测按钮
    left_widget->resize(650, 500);

    QPixmap label_pixmap(":/sys_test_widget/check");
    label->setPixmap(label_pixmap);
    label->setFixedSize(label_pixmap.size());

    QFont suggest_font = time_label->font();//返回默认应用程序字体
    suggest_font.setPointSize(15);//字体大小
    suggest_font.setBold(true);//加粗
    time_label->setFont(suggest_font);
    time_label->setObjectName("grayLabel");
    time_label->setText(tr("welcome make test"));

    QFont system_safe_font = this->font();
    system_safe_font.setPointSize(14);
    system_safe_font.setBold(true);

    QPixmap pixmap(":/sys_test_widget/power");
    sys_test_button->setIcon(pixmap);
    sys_test_button->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
    sys_test_button->setIconSize(pixmap.size());
    sys_test_button->setFixedSize(180, 70);
    sys_test_button->setObjectName("greenButton");

    QFont power_font = sys_test_button->font();
    power_font.setPointSize(16);
    sys_test_button->setFont(power_font);
    sys_test_button->setText(tr("一键测评"));

    QVBoxLayout *v_layout = new QVBoxLayout();//纵向布局
    v_layout->addWidget(time_label);
//    v_layout->addWidget(system_safe_label);
    v_layout->addStretch();//平均分配的意思
    v_layout->setSpacing(15);//空隙
    v_layout->setContentsMargins(30, 30, 0, 0);

    QHBoxLayout *h_layout = new QHBoxLayout();//横向布局
    h_layout->addWidget(label, 0, Qt::AlignTop);//这个枚举类型是用来描述对齐方式的
    h_layout->addLayout(v_layout);
    h_layout->addStretch();
    h_layout->setSpacing(20);
    h_layout->setContentsMargins(30, 20, 0, 0);

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addLayout(h_layout);
    main_layout->addWidget(sys_test_button, 0, Qt::AlignCenter);

    main_layout->addStretch();
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);

    left_widget->setLayout(main_layout);

    this->setAutoFillBackground(true);
    left_widget->setStyleSheet("QPushButton{color:#030303;background:#63B8FF; border-style: double;\
                               border-width: 4px;\
                               border-color: #ffcc00;}");
    this->setStyleSheet("QTextBrowser{background-color: #eaeaea; border:1px solid grey; border-radius: 8px;}");

 /*
    left_widget->setStyleSheet("QPushButton{image:url(:/skin/0.png); subcontrol-position: right center;\
                               color:black; background-color: red;\
                               border-style: double;\
                               border-width: 2px;\
                               border-radius: 10px;\
                               border-color: #ffccff;\
                               font: bold 18px;\
                               text-align: top;\
                               min-width: 8em;}");
*/

}

void Main_Page_One::home_btime()
{
    out = "";
    QString program = "bash";
    QStringList arguments;
    arguments<<"/usr/bin/home_info/homeinfo_btime.sh";
    pro->start(program, arguments);
    if(!pro->waitForStarted())
    {
        return;
    }
    while(!pro->waitForFinished(0))
    {
            out += pro->readAll();
    }
    time_label->setText(out);
}
void Main_Page_One::initRight()
{
    right_splitter = new QSplitter();
}

void Main_Page_One::initRightTop()
{
    right_top_widget = new User_Msg();

}
void Main_Page_One::initRightCenter()
{
//    right_center_widget = new QWidget();
    right_center_widget = new show_percent_page();
}

void Main_Page_One::initRightBottom()
{
//    right_bottom_widget = new QWidget();
    right_bottom_widget = new Net_Speed();
}
