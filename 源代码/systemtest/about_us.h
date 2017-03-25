/*
 *关于我们
*/
#ifndef ABOUT_US_H
#define ABOUT_US_H

#include <QWidget>
#include <QLabel>
#include "drop_shadow_widget.h"
class About_Us : public QWidget
{
    Q_OBJECT
public:
    explicit About_Us(QWidget *parent = 0);
    ~About_Us();

signals:

public slots:
private:
    QLabel *content,*lastly,*version,*chmod;
};

#endif // ABOUT_US_H
