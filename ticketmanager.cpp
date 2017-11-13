#include "ticketmanager.h"
#include <QEventLoop>

TicketManager::TicketManager(QObject *parent,const QList<QAbstractItemModel*> &tableList) : QObject(parent),m_Timer(),m_EmailReader(nullptr)
{
    connect(&m_Timer,SIGNAL(timeout()),this,SLOT(timerTimeout()));
    m_TableList=tableList;
    m_Timer.start(1000);
}

void TicketManager::timerTimeout()
{

    delete m_EmailReader;
    m_EmailReader=nullptr;

    //QEventLoop loop;
    //MailReader* reader=new MailReader(0,m_TableList);
    m_EmailReader=new MailReader(0,m_TableList);
    m_Timer.start(600000);
    //loop.exec();
    //reader->deleteLater();
}
