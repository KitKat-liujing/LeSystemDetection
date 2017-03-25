/*
    设置阴影边框   鼠标移动
*/
#ifndef DROP_SHADOW_WIDGET_H
#define DROP_SHADOW_WIDGET_H


#include <QDialog>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <qmath.h>

class DropShadowWidget : public QDialog
{
    Q_OBJECT

public:

    explicit DropShadowWidget(QWidget *parent = 0);
    ~DropShadowWidget();

protected:

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);

private:

    QPoint move_point; //移动的距离
    bool mouse_press; //按下鼠标左键

};

#endif // DROP_SHADOW_WIDGET_H
