#ifndef TICKETMANAGER_H
#define TICKETMANAGER_H

#include <QObject>
#include <QTimer>
#include "mailreader.h"
#include <QAbstractItemModel>

class TicketManager : public QObject
{
    Q_OBJECT
public:
    explicit TicketManager(QObject *parent = nullptr,const QList<QAbstractItemModel*> &tableList=QList<QAbstractItemModel*>());

private:
    QTimer m_Timer;
    QList<QAbstractItemModel*> m_TableList;
    MailReader* m_EmailReader;
signals:

public slots:
    void timerTimeout();

};

#endif // TICKETMANAGER_H
