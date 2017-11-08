#ifndef MAILREADER_H
#define MAILREADER_H

#include <QObject>
#include  "email.h"
#include <QSslSocket>
#include <QAbstractItemModel>

class MailReader : public QObject
{
    Q_OBJECT
public:
    explicit MailReader(QObject *parent = nullptr,const QList<QAbstractItemModel*> &tableList=QList<QAbstractItemModel*>());
    QList<int> fetchNewUIDs();
    Email* readMail(int UID);
    void connectIMAP();
    void clearNewList(int start);
    void parseTicketList(int start);



private:
    QString m_Host;
    int m_Port;
    QString m_UserName,m_Password;
    QStringList m_NewList,m_NewTicketList;
    QSslSocket m_socket;
    int m_ResponseId;
    bool m_ResponseComplete;
    QByteArray m_Response;
    QList<Email*> m_EmailList;
    void processEmailList();
    QList<QAbstractItemModel*> m_TableList;




signals:


public slots:

    void connected();
    void readyRead();


};

#endif // MAILREADER_H
