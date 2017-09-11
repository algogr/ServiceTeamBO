#include "email.h"
#include "ticket.h"
#include "customer.h"
#include "originator.h"
#include <QDebug>

Email::Email(QObject *parent) : QObject(parent)
{

}

QString Email::body() const
{
    return m_body;
}

void Email::setBody(const QString &body)
{
    m_body = body;
}

Ticket *Email::createTicket(const QList<QAbstractItemModel *> &tableList)
{

    decodeQuotedPrintable(m_body);
    int start=m_body.indexOf("<html");
    int end=m_body.indexOf("</html");
    m_body=m_body.mid(start,(end-start)+7);
    cleanText(m_body);

    Originator* originator=new Originator;
    Customer* customer=new Customer;
    Ticket* ticket=new Ticket;

    originator->setName(readField("Company"));
    customer->setName(readField("Service Resipient"));
    customer->setLocation(readField("Location"));
    customer->setDepartment(readField("Department"));
    customer->setCity(readField("City"));
    customer->setCounty(readField("County"));
    customer->setAddress(readField("Address"));
    customer->setEmail(readField("Email"));
    customer->setPhone1(readField("Phone"));

    ticket->setOriginator(originator);
    ticket->setCustomer(customer);
    ticket->setIncident(readField("Incident"));
    ticket->setTitle(readField("Title"));
    ticket->setService(readField("Service"));
    ticket->setInteractionId(readField("Interaction ID"));
    ticket->setReportedDate(QDateTime::fromString(readField("Reported Date"),"ddd MMM d yyyy hh:mm:ss"));
    ticket->setDescription(readField("Description"));
    ticket->setCustomerTicketNo(readField("Customer Ticket No"));
    ticket->setAppointmentFrom(QDateTime::fromString(readField("Appointment From"),"ddd MMM d yyyy hh:mm:ss"));
    ticket->setAppointmentTo(QDateTime::fromString(readField("Appointment To"),"ddd MMM d yyyy hh:mm:ss"));
    ticket->setUrgency(readField("Urgency").left(1).toInt());
    ticket->setPriority(readField("Priority").left(1).toInt());

    originator->persist(tableList);








    qDebug()<<customer;



}

QString Email::readField(const QString &fieldName)
{
    int start,end;
    if (fieldName=="Incident")
    {
        QRegExp inc("Incident");
        return m_body.mid(inc.indexIn(m_body)+9,8);
    }


    start=m_body.indexOf(fieldName);
    qDebug()<<"1.stat:"<<start;
    start=m_body.indexOf("<td",start);
    qDebug()<<"2.stat:"<<start;
    start=m_body.indexOf("<span",start);
    qDebug()<<"3.stat:"<<start;
    start=m_body.indexOf(">",start);
    qDebug()<<"4.stat:"<<start;
    end=m_body.indexOf("<o:p>",start);
    qDebug()<<"end:"<<end;
    QString value=m_body.mid(start+1,end-start-1);
    value.trimmed();
    qDebug()<<"Mystr:"<<value;
    return value;
}

void Email::cleanText(QString &text)
{
    text.replace(" GMT+0300","");
    text.replace("=","");

    text.replace(" ="," ");
    text.replace("  "," "); //2 space
    text.replace("   "," "); //3 space
    text.replace("    "," "); //4 space
    text.replace("     "," "); //5 space
    text.replace("      "," "); //6 space
    text.replace("       "," "); //7 space
    text.replace("        "," "); //8 space
    text.replace("         "," "); //9 space
    text.replace("          "," ");
}

void Email::decodeQuotedPrintable(QString &text)
{
    text.replace("=CE=82","ς");
    text.replace("=CE=83","σ");
    text.replace("=CE=84","τ");
    text.replace("=CF","=CE");
    text.replace("=CE=\r\n","=CE");

    text.replace("=CE=80","π");
    text.replace("=CE=81","ρ");
    text.replace("=CE=85","υ");
    text.replace("=CE=87","χ");

    text.replace("=CE=86","Ά");
    text.replace("=CE=88","Έ");
    text.replace("=CE=89","Ή");
    text.replace("=CE=8A","Ί");
    text.replace("=CE=8C","Ό");
    text.replace("=CE=8E","Ύ");
    text.replace("=CE=8F","Ώ");
    text.replace("=CE=91","Α");
    text.replace("=CE=92","Β");
    text.replace("=CE=93","Γ");
    text.replace("=CE=94","Δ");
    text.replace("=CE=95","Ε");
    text.replace("=CE=96","Ζ");
    text.replace("=CE=97","Η");
    text.replace("=CE=98","Θ");
    text.replace("=CE=99","Ι");
    text.replace("=CE=9A","Κ");
    text.replace("=CE=9B","Λ");
    text.replace("=CE=9C","Μ");
    text.replace("=CE=9D","N");
    text.replace("=CE=9E","Ξ");
    text.replace("=CE=9F","Ο");
    text.replace("=CE=A0","Π");
    text.replace("=CE=A1","Ρ");
    text.replace("=CE=A3","Σ");
    text.replace("=CE=A4","Τ");
    text.replace("=CE=A5","Υ");
    text.replace("=CE=A6","Φ");
    text.replace("=CE=A7","Χ");
    text.replace("=CE=A8","Ψ");
    text.replace("=CE=A9","Ω");

    text.replace("=CE=B1","α");
    text.replace("=CE=B2","β");
    text.replace("=CE=B3","γ");
    text.replace("=CE=B4","δ");
    text.replace("=CE=B5","ε");
    text.replace("=CE=B6","ζ");
    text.replace("=CE=B7","η");
    text.replace("=CE=B8","θ");
    text.replace("=CE=B9","ι");
    text.replace("=CE=BA","κ");
    text.replace("=CE=BB","λ");
    text.replace("=CE=BC","μ");
    text.replace("=CE=BD","ν");
    text.replace("=CE=BE","ξ");
    text.replace("=CE=BF","ο");
    text.replace("=CE=C0","π");
    text.replace("=CE=C1","ρ");
    text.replace("=CE=C2","σ");
    text.replace("=CE=C3","τ");
    text.replace("=CE=C4","υ");
    text.replace("=CE=C5","φ");
    text.replace("=CE=C6","χ");
    text.replace("=CE=C7","ψ");
    text.replace("=CE=C8","ω");

    text.replace("=CE=AC","ά");
    text.replace("=CE=AD","έ");
    text.replace("=CE=AE","ή");
    text.replace("=CE=AF","ί");
    text.replace("=CE=CC","ό");
    text.replace("=CE=CD","ύ");
    text.replace("=CE=CE","ώ");



    text.replace("\r\n","");

}
