/*
新建toolbutton类按钮事件。设置属性
*/
#ifndef TOOL_BUTTON_H
#define TOOL_BUTTON_H

#include <QToolButton>
#include <QMouseEvent>
#include <QPainter>

class ToolButton : public QToolButton
{

public:

    explicit ToolButton(QString pic_name, QWidget *parent = 0);
    ~ToolButton();
    void setMousePress(bool mouse_press);

protected:

    void enterEvent(QEvent *);//enter
    void leaveEvent(QEvent *);//leave
    void mousePressEvent(QMouseEvent *event);//press
    void paintEvent(QPaintEvent *event);//paint
    void painterInfo(int top_color, int middle_color, int bottom_color);

public:

    bool mouse_over; //鼠标是否移过
    bool mouse_press; //鼠标是否按下
};


#endif // TOOL_BUTTON_H
