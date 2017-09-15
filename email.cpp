#include "email.h"
#include "ticket.h"
#include "customer.h"
#include "originator.h"
#include <QDebug>
#include <QRegExp>

Email::Email(QObject *parent) : QObject(parent)
{

    m_EmailFieldsNormal<<"Title"<<"Company"<<"Service"<<"Interaction ID"\
            <<"Service Recipient"<<"Location"<<"Department"<<"City"\
           <<"County"<<"Address"<<"Email"<<"Phone"<<"Reported Date"\
        <<"Urgency"<<"Priority"<<"Description"<<"Customer Ticket No"<<\
        "Appointment From"<<"Appointment To";

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
    //int start=m_body.indexOf("<html");
    //int end=m_body.indexOf("</html");
    //m_body=m_body.mid(start,(end-start)+7);
    cleanText(m_body,m_EmailFieldsNormal);

    Originator* originator=new Originator;
    Customer* customer=new Customer;
    Ticket* ticket=new Ticket;
    qDebug()<<"Cleaned Up::"<<m_body<<"End cleaned body";

    originator->setName(readField("Company"));
    customer->setName(readField("Service Recipient"));
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
    customer->persist(tableList);
    qDebug()<<"Description:"<<ticket->Description();










    qDebug()<<customer;



}

QString Email::readField(const QString &fieldName)
{
    //int start1,start2,start3,start4,end;
    if (fieldName=="Incident")
    {
        QRegExp inc("Incident");
        return m_body.mid(inc.indexIn(m_body)+9,8);
    }
    /*
    qDebug()<<"FieldNmae:"<<fieldName;
    start1=m_body.indexOf(fieldName+"<o:p>");
    qDebug()<<"1.stat1:"<<start1;
    start2=m_body.indexOf("<td",start1);
    qDebug()<<"2.stat2:"<<start2;
    start3=m_body.indexOf("<span",start2);
    qDebug()<<"3.stat3:"<<start3;
    start4=m_body.indexOf(">",start3);
    qDebug()<<"4.stat4:"<<start4;
    end=m_body.indexOf("<o:p>",start4);
    qDebug()<<"end:"<<end;
    QString value=m_body.mid(start4+1,end-start4-1);
    value.trimmed();
    */
    int start=m_body.indexOf(fieldName)+fieldName.size()+1;
    int end=m_body.indexOf("!@#",start);
    QString value=m_body.mid(start,end-start);

    qDebug()<<"Mystr:"<<value;
    //if (end-start4<=7)
      //  value="";
    return value;
}

void Email::cleanText(QString &text,const QStringList &fieldList)
{
    text.replace(" GMT+0300","");
    text.replace("=","");
    text.replace("  "," "); //2 space
    text.replace("   "," "); //3 space
    text.replace("    "," "); //4 space
    text.replace("     "," "); //5 space
    text.replace("      "," "); //6 space
    text.replace("       "," "); //7 space
    text.replace("        "," "); //8 space
    text.replace("         "," "); //9 space
    text.replace("          "," ");

    text.replace(QRegExp("<(?:[^>=]|='[^']*'|=""[^\"\"]*\"\"|=[^'\"\"][^\s>]*)*>"),"");
    //text.replace(QRegExp("<(\\w+)")," ");
    //text.replace(QRegExp("(?:[^>=]|='[^']*'|=\"[^\"]*\"|=[^'\"][^\s>]*)*>")," ");

    for (int i=0;i<fieldList.size();i++)
    {
        text.replace(QRegExp(fieldList.at(i)),"!@#"+fieldList.at(i)+":");
    }



}

void Email::decodeQuotedPrintable(QString &text)
{
    text.replace("\r\n","");
    text.replace("==","=");
    text.replace("=C2=Α0"," ");
    text.replace("=CF","=CE");
    text.replace("=CE=82","ς");
    text.replace("=CE=83","σ");
    text.replace("=CE=84","τ");



    text.replace("=CE=80","π");
    text.replace("=CE=81","ρ");
    text.replace("=CE=85","υ");
    text.replace("=CE=87","χ");

    text.replace("=CE=86","Ά");
    text.replace("=CE=88","Έ");
    text.replace("=CE=89","Ή");
    text.replace("=CE=8A","Ί");
    text.replace("=CE=8C","Ό");
    text.replace("=CE=8D","ύ");
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





}
