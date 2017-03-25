#include "title_widget.h"
#include "common.h"

TitleWidget::TitleWidget(QWidget *parent)
    :QWidget(parent)
{
    version_title = new QLabel();
    skin_button = new PushButton();
    main_menu_button = new PushButton();
    min_button = new PushButton();
    close_button = new PushButton();

    sys_test_logo = new QLabel();
    sys_team = new QLabel();
    sys_test = new QLabel();

    //设置图片
    skin_button->setPicName(QString(":/title/skin"));
    min_button->setPicName(QString(":/title/min"));
    close_button->setPicName(QString(":/title/close"));
    main_menu_button->setPicName(QString(":/title/menu"));

    //title布局
    QHBoxLayout *title_layout = new QHBoxLayout();
    title_layout->addSpacing(5);
    title_layout->addWidget(version_title,0,Qt::AlignVCenter);
    title_layout->addStretch();
    title_layout->addWidget(skin_button, 0, Qt::AlignTop);
    title_layout->addWidget(main_menu_button, 0, Qt::AlignTop);
    title_layout->addWidget(min_button, 0, Qt::AlignTop);
    title_layout->addWidget(close_button, 0, Qt::AlignTop);
    version_title->setContentsMargins(5,0,0,0);
    QFont font = this->font();
    font.setPointSize(12);
    version_title->setFont(font);

    QFont ft;
    ft.setPointSize(12);
    ft.setBold(true);

    version_title->setText(tr("LE") +  QString("  ") + QString("乐测评监测软件"));
    version_title->setFont(ft);
    version_title->setStyleSheet("color:black");
    skin_button->setToolTip(tr("change skin"));
    main_menu_button->setToolTip(tr("main menu"));
    min_button->setToolTip(tr("minimize"));
    close_button->setToolTip(tr("close"));

    QLabel *logo_label = new QLabel();
    QPixmap pixmap(":/page1/logo.png");
    logo_label->setPixmap(pixmap);
    logo_label->setFixedSize(pixmap.size());

    QStringList string_list;
    string_list<<":/page1/func1.png"<<":/page1/func2.png"<<":/page1/func3.png"<<":/page1/func4.png"
                    <<":/page1/func5.png"<<":/page1/func6.png"<<":/page1/func7.png";

    QHBoxLayout *button_layout = new QHBoxLayout();
    QSignalMapper *signal_mapper = new QSignalMapper(this);
    for(int i = 0; i < string_list.size(); i++)
    {
        ToolButton *tool_button = new ToolButton(string_list.at(i));
        button_list.append(tool_button);
        tool_button->setFixedSize(80, 80);
        connect(tool_button,SIGNAL(clicked()),signal_mapper,SLOT(map()));
        signal_mapper->setMapping(tool_button, QString::number(i, 10));
        button_layout->addWidget(tool_button, 0, Qt::AlignBottom);
    }

    connect(signal_mapper, SIGNAL(mapped(QString)),this,SLOT(turnPage(QString)));
    connect(skin_button, SIGNAL(clicked()), this, SLOT(change_skin()));
    connect(close_button, SIGNAL(clicked()), this, SIGNAL(close_window()));
    connect(min_button, SIGNAL(clicked()), SIGNAL(hide_window()));
    connect(main_menu_button,SIGNAL(clicked()),this,SIGNAL(show_main_menu()));

    button_layout->setSpacing(6);//button之间间距
    button_layout->addStretch();
    button_layout->setContentsMargins(0,0,0,0);

    button_list.at(0)->setText(tr("首页"));
    button_list.at(1)->setText(tr("cpu"));
    button_list.at(2)->setText(tr("内存"));
    button_list.at(3)->setText(tr("磁盘"));
    button_list.at(4)->setText(tr("网络"));
    button_list.at(5)->setText(tr("系统"));
    button_list.at(6)->setText(tr("安全"));
    //button_list.at(7)->setText(tr("拓展"));

//    QVBoxLayout *sys_layout = new QVBoxLayout();
//    sys_layout->addWidget(sys_test);
//    sys_layout->addWidget(sys_team);
//    sys_layout->setContentsMargins(0,5,5,0);
//    QHBoxLayout *logo_layout = new QHBoxLayout();
//    logo_layout->addStretch();
//    logo_layout->addLayout(sys_layout);
//    logo_layout->addSpacing(5);
//    logo_layout->addWidget(sys_test_logo);
//    logo_layout->setContentsMargins(0,0,30,0);
    QHBoxLayout *last_layout = new QHBoxLayout();
    last_layout->addLayout(button_layout);
    last_layout->addStretch();
    last_layout->addWidget(logo_label);
    last_layout->addStretch();

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->setMargin(1);
    main_layout->addLayout(title_layout);
    main_layout->addStretch();
    main_layout->addLayout(last_layout);

    setLayout(main_layout);
    setFixedHeight(120);
}

TitleWidget::~TitleWidget()
{

}

void TitleWidget::turnPage(QString current_page)
{
    bool ok;
    int current_index = current_page.toInt(&ok, 10);//

    for(int i=0; i<button_list.count(); i++)
    {
        ToolButton *tool_button = button_list.at(i);
        if(current_index == i)
        {
            tool_button->setMousePress(true);
        }
        else
        {
            tool_button->setMousePress(false);
        }
    }

    emit turnPage(current_index);
}

void TitleWidget::change_skin()
{
    if ( Flag_skin == 8)
        Flag_skin = 0;
    QStringList skin_list;
    skin_list<<":/skin/1_big.jpg"<<":/skin/2_big.png"<<":/skin/3_big.jpg"<<":/skin/4_big.jpg"<<":/skin/5_big.jpg"<<":/skin/6_big.jpg"<<":/skin/7_big.jpg"<<":/skin/8_big.png";
    emit change_skin(skin_list.at(Flag_skin));
    Flag_skin++;
}
