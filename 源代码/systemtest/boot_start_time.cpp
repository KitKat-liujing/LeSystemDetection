#include "boot_start_time.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QDesktopWidget>
#include <QApplication>
#include "common.h"
#include <QPushButton>
#include <QPixmap>

Boot_Start_Time::Boot_Start_Time(QWidget *parent) :
    DropShadowWidget(parent)
{
    this->resize(300,200);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    show_msg = new QTextBrowser();
    show_msg->setStyleSheet("background-color:#eaeaea");
    show_msg->setFixedSize(300, 140);
    close_button = new QPushButton();
    close_button->setFixedSize(25,25);
    close_button->setStyleSheet("QPushButton{border-image: url(:/title/close.png);}"
                                "QPushButton:hover{border-image: url(:/title/close_hover.png);}"
                                "QPushButton:pressed{border-image: url(:/title/close_pressed.png);}");
    connect(close_button, SIGNAL(clicked()), this, SLOT(hide()));
    pro = new QProcess();
    out = "";
    QString program = "bash";
    QStringList arguments;
    arguments<<"/usr/bin/boot_start/time1.sh";
    pro->start(program, arguments);
    while(pro->waitForReadyRead())
    {
        out += pro->readAll();
    }
    show_msg->setText(out);

    this->skin_name = DEFAULT_SKIN;
    QHBoxLayout *close_button_layout = new QHBoxLayout();
    close_button_layout->addStretch();
    close_button_layout->addWidget(close_button, 0, Qt::AlignRight);
    close_button_layout->setContentsMargins(0,0,0,0);
    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addLayout(close_button_layout);
    main_layout->addStretch();
    main_layout->addWidget(show_msg);
    main_layout->setContentsMargins(0, 0, 0, 0);
    setLayout(main_layout);
    QDesktopWidget *d = QApplication::desktop();
    this->move(d->width()-300,d->height()-200);
}

Boot_Start_Time::~Boot_Start_Time()
{
}

void Boot_Start_Time::paintEvent(QPaintEvent *event)
{
    DropShadowWidget::paintEvent(event);
    int draw_height = 60;
    int width = this->width();
    int height = this->height();

    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawPixmap(QRect(0, 0, this->width(), this->height()), QPixmap(skin_name));

    QPainter painter2(this);
    painter2.setPen(Qt::NoPen);
    painter2.setBrush(QColor("#A4D3EE"));
    painter2.drawRect(QRect(0, draw_height, width, height-draw_height));

}
