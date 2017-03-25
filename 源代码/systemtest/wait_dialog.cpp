#include "wait_dialog.h"
#include <QHBoxLayout>

Waiting_Dialog::Waiting_Dialog(QWidget *parent):
    QDialog(parent)
{
    setWindowFlags(Qt::WindowStaysOnTopHint);
    m_Timer = new QTimer();
    m_ProgressBar = new QProgressBar(this);
    m_CurrentValue = m_MaxValue = m_UpdateInterval = 0;
    m_ProgressBar->setRange(0, 100);
    connect(m_Timer, SIGNAL(timeout()), this, SLOT(UpdateSlot()));
    m_ProgressBar->setTextVisible(false);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(m_ProgressBar);
    setLayout(layout);

}

Waiting_Dialog::~Waiting_Dialog()
{

}

void Waiting_Dialog::UpdateSlot()
{
    m_CurrentValue++;
    if( m_CurrentValue == m_MaxValue )
        m_CurrentValue = 0;
    m_ProgressBar->setValue(m_CurrentValue);

}

void Waiting_Dialog::Start(int interval, int maxValue)
{
    m_UpdateInterval = interval;
    m_MaxValue = maxValue;
    m_Timer->start(m_UpdateInterval);
    m_ProgressBar->setRange(0, m_MaxValue);
    m_ProgressBar->setValue(0);
}

void Waiting_Dialog::Stop()
{
    m_Timer->stop();
}
