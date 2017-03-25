#include "main_widget.h"
#include <QVBoxLayout>
#include <QDesktopWidget>
#include <QApplication>
#include <QPropertyAnimation>
#include <QIcon>

main_widget::main_widget(QWidget *parent)
    : DropShadowWidget(parent)
{

//    setMaximumSize(900,600);
//    setMinimumSize(900,600);
    setFixedSize(900,625);
    QDesktopWidget *d = QApplication::desktop();
    this->move((d->width()-this->width())/2, (d->height()-this->height())/2);
    this->skin_name = DEFAULT_SKIN;

 /********* show   boot   time   **************/
    start_time_widget = new Boot_Start_Time();
    tmr_show_start_time = new QTimer(this);
    connect(tmr_show_start_time, SIGNAL(timeout()), this, SLOT(show_start_time()));
    tmr_show_start_time->start(10000);
    tmr_hide_start_time = new QTimer(this);
    connect(tmr_hide_start_time, SIGNAL(timeout()), this, SLOT(hide_start_time()));

 /*********** please  input  pwd  ************************/
    input_pwd_widget = new Input_Pwd();
    tmr_input_pwd = new QTimer();
    connect(tmr_input_pwd, SIGNAL(timeout()), this, SLOT(show_input_pwd_widget()));
    tmr_input_pwd->start(500);

    stacked_widget = new QStackedWidget();
    title_widget = new TitleWidget();
    one_widget = new Main_Page_One();
    two_widget = new Main_Page_two();
    three_widget = new Main_Page_three();
    four_widget = new Main_Page_four();
    five_widget = new Main_Page_five();
    six_widget = new Main_Page_six();
    serven_widget = new main_page_serven();
    //eight_widget = new main_page_eight();
    sys_test_widget = new Sys_Test_Widget();//系统检测页面
    button_widget = new Buttom_Widget();

    main_menu = new Main_Menu();

    stacked_widget->addWidget(one_widget);
    stacked_widget->addWidget(two_widget);
    stacked_widget->addWidget(three_widget);
    stacked_widget->addWidget(four_widget);
    stacked_widget->addWidget(five_widget);
    stacked_widget->addWidget(six_widget);
    stacked_widget->addWidget(serven_widget);
    //stacked_widget->addWidget(eight_widget);
    stacked_widget->addWidget(sys_test_widget);

    QVBoxLayout *stack_layout = new QVBoxLayout();
    stack_layout->addWidget(stacked_widget);
    stack_layout->setSpacing(0);
    stack_layout->setContentsMargins(0,0,0,0);

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addWidget(title_widget);
    main_layout->addLayout(stack_layout);
    main_layout->addWidget(button_widget);
    main_layout->addStretch();
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0,0,0,0);

    setLayout(main_layout);

    connect(title_widget, SIGNAL(turnPage(int)), this, SLOT(turnPage(int)));//页面跳转
//    connect(one_widget, SIGNAL(sendinfo(QString)), two_widget, SLOT(getinfo(QString)));
    connect(title_widget, SIGNAL(change_skin(QString)), this, SLOT(change_skin(QString)));//修改皮肤
    connect(title_widget, SIGNAL(close_window()), this, SLOT(close()));//关闭程序
    connect(title_widget, SIGNAL(hide_window()), this, SLOT(hide()));
    connect(one_widget, SIGNAL(go_sys_test_page()), this, SLOT(go_sys_test_page()));
    connect(title_widget,SIGNAL(show_main_menu()),this,SLOT(show_main_menu()));
    title_widget->turnPage("0");


    createMenu();
    //判断系统是否支持托盘图标
    if(!QSystemTrayIcon::isSystemTrayAvailable())
    {
    return;
    }
    //实例 QSystemTrayIcon
    myTrayIcon = new QSystemTrayIcon(this);
    //设置图标
    myTrayIcon->setIcon(QIcon(":/page1/logo1.png"));
    //鼠标放托盘图标上提示信息
    myTrayIcon->setToolTip("Qt 托盘图标功能");
    //设置消息
    myTrayIcon->showMessage("托盘","托盘管理",QSystemTrayIcon::Information,10000);
    //托盘菜单
    myTrayIcon->setContextMenu(myMenu);
    //显示
    myTrayIcon->show();
}

main_widget::~main_widget()
{

}

void main_widget::turnPage(int current_page)
{
    if(current_page == 0)
    {
        stacked_widget->setCurrentWidget(one_widget);
        Flag_Current_Main_Page = 0;
    }
    if(current_page == 1)
    {
        stacked_widget->setCurrentWidget(two_widget);
        Flag_Current_Main_Page = 1;
    }
    if(current_page == 2)
    {
        stacked_widget->setCurrentWidget(three_widget);
        Flag_Current_Main_Page = 2;
    }
    if(current_page == 3)
    {
        stacked_widget->setCurrentWidget(four_widget);
        Flag_Current_Main_Page = 3;
    }
    if(current_page == 4)
    {
        stacked_widget->setCurrentWidget(five_widget);
    }
    if(current_page == 5)
    {
        stacked_widget->setCurrentWidget(six_widget);
    }
    if(current_page == 6)
    {
        stacked_widget->setCurrentWidget(serven_widget);
    }
    if(current_page == 7)
    {
        //stacked_widget->setCurrentWidget(eight_widget);
    }

}

void main_widget::show_start_time()
{
    start_time_widget->show();
    tmr_show_start_time->stop();
    tmr_hide_start_time->start(6000);
}

void main_widget::hide_start_time()
{
    start_time_widget->close();
    tmr_hide_start_time->stop();
}

void main_widget::show_input_pwd_widget()
{
    tmr_input_pwd->stop();
    input_pwd_widget->exec();
}

void main_widget::paintEvent(QPaintEvent *event)
{
    DropShadowWidget::paintEvent(event);
    setWindowIcon(QIcon(":/page1/logo1.ico"));
    int draw_height = 120;
    int width = this->width();
    int height = this->height();

    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawPixmap(QRect(0, 0, this->width(), this->height()), QPixmap(skin_name));

    QPainter painter2(this);
    painter2.setPen(Qt::NoPen);
    painter2.setBrush(Qt::white);
    painter2.drawRect(QRect(2, draw_height, width-4, height-draw_height-23));
}

void main_widget::change_skin(QString new_skin_name)
{
    this->skin_name = new_skin_name;//换肤
    update();
}

void main_widget::go_sys_test_page()
{
    stacked_widget->setCurrentWidget(sys_test_widget);//跳转页面
    sys_test_widget->start_timer();//开启定时器检测
    Flag_Sys_Test_Page = 1;//检测页面标志位置
}
void main_widget::createMenu()
{
    restoreWinAction = new QAction("恢复(&R)",this);
    quitAction = new QAction("退出(&Q)",this);
    //恢复
    connect(restoreWinAction,SIGNAL(triggered()),this,SLOT(showNormal()));
    //退出
    connect(quitAction,SIGNAL(triggered()),qApp,SLOT(quit()));
    myMenu = new QMenu((QWidget*)QApplication::desktop());
    //添加菜单
    myMenu->addAction(restoreWinAction);
    //分隔符
    myMenu->addSeparator();
    myMenu->addAction(quitAction);
}
void main_widget::showNormal()
{
    this->show();
}
void main_widget::show_main_menu()
{
    QPoint p = rect().topRight();
    p.setX(p.x() - 90);
    p.setY(p.y() + 25);
    main_menu->exec(this->mapToGlobal(p));
}
