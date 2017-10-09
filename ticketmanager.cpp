#include "ticketmanager.h"
#include "mailreader.h"
#include <QEventLoop>

TicketManager::TicketManager(QObject *parent,const QList<QAbstractItemModel*> &tableList) : QObject(parent),m_Timer()
{
    connect(&m_Timer,SIGNAL(timeout()),this,SLOT(timerTimeout()));
    m_TableList=tableList;
    m_Timer.start(1000);
}

void TicketManager::timerTimeout()
{
    //QEventLoop loop;
    //MailReader* reader=new MailReader(0,m_TableList);
    MailReader* reader=new MailReader(0,m_TableList);
    m_Timer.start(120000);
    //loop.exec();
    //reader->deleteLater();
}
