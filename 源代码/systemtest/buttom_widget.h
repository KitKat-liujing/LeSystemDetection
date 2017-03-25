/*
底部窗口栏
*/
#ifndef BUTTOM_WIDGET_H
#define BUTTOM_WIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>

class Buttom_Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Buttom_Widget(QWidget *parent = 0);

protected:
    QLabel *learn_Label;
    QLabel *officer;

signals:

public slots:
private:
    QHBoxLayout *bottom_layout;
    QLabel *contract_label;
};

#endif // BUTTOM_WIDGET_H
