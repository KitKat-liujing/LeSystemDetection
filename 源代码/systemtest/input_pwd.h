/*
密码检测系统
*/
#ifndef INPUT_PWD_H
#define INPUT_PWD_H

#include "drop_shadow_widget.h"
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QProcess>

class Input_Pwd: public DropShadowWidget
{
    Q_OBJECT

public:
    explicit Input_Pwd(QDialog *parent = 0);
    ~Input_Pwd();

private:
    QLabel *tips;
    QLabel *remind;
    QLineEdit *pwd_edit;
    QPushButton *submit;
    QPushButton *cancel;

    QProcess *pro_pwd;
    QString out_pwd;

protected:
        virtual void paintEvent(QPaintEvent *event);

protected slots:
    void Set_Pwd();
    void Set_Cancel();
public slots:

};

#endif // INPUT_PWD_H
