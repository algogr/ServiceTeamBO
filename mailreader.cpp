#include "mailreader.h"
#include "ticket.h"
#include "customer.h"

MailReader::MailReader(QObject *parent,const QList<QAbstractItemModel*> &tablelist) : QObject(parent),m_socket(),\
    m_ResponseId(0),m_NewList(),m_ResponseComplete(true),m_Response(),\
    m_NewTicketList(),m_EmailList()
{
    m_TableList=tablelist;
    connectIMAP();
}

QList<int> MailReader::fetchNewUIDs()
{

}

Email *MailReader::readMail(int UID)
{
QString decodeQuotedPrintable(const QString &text);
}

void MailReader::connectIMAP()
{
    connect(&m_socket,SIGNAL(encrypted()),this,SLOT(connected()));
    connect(&m_socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
    //TODO Check netwotk connection
    //TODO Parametetric
    m_socket.connectToHostEncrypted("imap.gmail.com", 993);

}

void MailReader::clearNewList(int start)
{
    m_ResponseId=start;
    //qDebug()<<"Before clear:"<<m_NewList.size()<<":"<<m_ResponseId-10000;
    if (m_NewList.size()==m_ResponseId-10000)
    {
        //qDebug()<<"Tickeys:"<<m_NewTicketList;
        m_NewList.clear();
        m_Response.clear();
        m_ResponseComplete=true;
        parseTicketList(20000);
        return;
    }
    //qDebug()<<"clear"<<m_NewList[(m_ResponseId-10000)];
    QString test="SRR UID fetch "+m_NewList[(m_ResponseId-10000)]+" BODY[HEADER.FIELDS (SUBJECT)]" ;

    m_socket.write(test.toUtf8());
    m_socket.write("\r\n");


}

void MailReader::parseTicketList(int start)
{
    m_ResponseId=start;
    qDebug()<<"Before clear:"<<m_NewTicketList.size()<<":"<<m_ResponseId-20000;
    if (m_NewTicketList.size()==m_ResponseId-20000)
    {
        m_ResponseComplete=true;
        processEmailList();
        qDebug()<<"Ticks:"<<m_NewTicketList;

        return;
    }

    QString test="SRS UID fetch "+m_NewTicketList[(m_ResponseId-20000)]+" BODY[text]" ;
    m_socket.write(test.toUtf8());
    m_socket.write("\r\n");

}

void MailReader::processEmailList()
{
    QString decodedText;
    for (int i=0;i<m_EmailList.size();i++)
    {
        //TODO EDO EIMAI 1
        Email* email=m_EmailList[i];
        email->createTicket(m_TableList);



    }


}

void MailReader::connected()
{
    //TODO Parametetric
    QString credentials="001 login algosakis@gmail.com v@$230698";
    m_socket.write(credentials.toUtf8());
    m_socket.write("\r\n");
}

void MailReader::readyRead()
{
    // qDebug()<<"Mpaino"<<m_ResponseId;

    if (m_ResponseComplete)
    {
        qDebug()<<"ResponseTrue"<<m_ResponseId;
        m_Response.clear();
        m_ResponseId++;
    }

    if (m_ResponseId==2)
    {
        m_ResponseComplete=false;
        while(m_socket.bytesAvailable()>0)
        {
            m_socket.readAll();


        }
        m_ResponseComplete=true;

        m_socket.write("002 select INBOX");
        m_socket.write("\r\n");
        return;
    }

    if (m_ResponseId==3)
    {

        m_ResponseComplete=false;
        while(m_socket.bytesAvailable()>0)
        {
            m_socket.readAll();


        }
        m_ResponseComplete=true;
        QString list="SR1 UID SEARCH UNSEEN";
        m_socket.write(list.toUtf8());
        m_socket.write("\r\n");
        return;
    }

    if (m_ResponseId==4)
    {
        m_ResponseComplete=false;
        while(m_socket.bytesAvailable()>0)
        {
            m_Response=m_socket.readAll();


        }
        m_ResponseComplete=true;
        //qDebug()<<"1:"<<m_Response;
        QRegExp regxp1("SEARCH ");
        QRegExp regxp2("\r\nSR1");
        int start=regxp1.indexIn(m_Response)+7;
        int end=regxp2.indexIn(m_Response);
        m_Response=m_Response.mid(start,end-start);
        m_NewList=m_Response.split(" ");
        //qDebug()<<"2:"<<m_Response;
        //qDebug()<<"3:"<<m_NewList;
        clearNewList(10000);

    }

    if (m_ResponseId>10000 && m_ResponseId<20000)
    {
        //qDebug()<<"Loopa"<<m_ResponseId-10000;
        m_ResponseComplete=false;
        while(m_socket.bytesAvailable()>0)
        {
            m_Response+=m_socket.readAll();


        }

        QRegExp regxp("SRR OK Success\r\n");

        if (regxp.indexIn(m_Response)>0)
        {
            m_ResponseComplete=true;
            regxp.setPattern("Incident");
            if(regxp.indexIn(m_Response)>0)
            {
              m_NewTicketList.append(m_NewList[(m_ResponseId-10001)]);
            }
            //qDebug()<<m_Response;

            clearNewList(m_ResponseId);
         }

            return;
    }





    if (m_ResponseId>20000 && m_ResponseId<30000)
    {
        qDebug()<<"Loopa"<<m_ResponseId-20000;
        m_ResponseComplete=false;
        while(m_socket.bytesAvailable()>0)
        {
            m_Response+=m_socket.readAll();


        }

        QRegExp regxp("SRS OK Success\r\n");

        if (regxp.indexIn(m_Response)>0)
        {
            m_ResponseComplete=true;
            Email* email=new Email;
            email->setBody(m_Response);
            m_EmailList.append(email);

            qDebug()<<m_Response;

            parseTicketList(m_ResponseId);

         }

            return;
    }



}
