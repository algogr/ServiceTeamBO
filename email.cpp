#include "email.h"
#include "ticket.h"
#include "customer.h"
#include "originator.h"
#include <QDebug>
#include <QRegExp>
#include <QMutex>
#include <QThread>

Email::Email(QObject *parent) : QObject(parent),m_EmailFieldsNormal(),m_EmailFieldsOpap(),m_BodytoString()
{

    m_EmailFieldsNormal<<"Incident"<<"Title"<<"Company"<<"  Service"<<"Interaction ID"\
                      <<"Recipient"<<"Location"<<"Department"<<"City"\
                     <<"County"<<"Address"<<"Email"<<"Phone"<<"Reported Date"\
                    <<"Urgency"<<"Priority"<<"Description"<<"Customer Ticket No"<<\
                      "Appointment From"<<"Appointment To";

    m_EmailFieldsOpap<<"Service Request"<<"POS Name:"<<"POS Code:"<<"Main Phone:"<<"Secondary Phone:"<<"Code Type:"\
                    <<"Date Opened:"<<"Response Time:"<<"Extra Phone:"<<"SR Owner:"<<"Status:";


}

QByteArray Email::body() const
{
    return m_body;
}

void Email::setBody(const QByteArray &body)
{
    m_body = body;
}

Ticket *Email::createTicket(const QList<QAbstractItemModel *> &tableList)
{
    QMutex mutex;
    mutex.lock();
    Originator* originator=new Originator;
    Customer* customer=new Customer;
    Ticket* ticket=new Ticket;
    QLocale::setDefault(QLocale::English);



    if (!m_body.contains("Incident"))
    {
        //QByteArray enc=QByteArray::fromBase64(m_body.toUtf8());

        m_body.replace("\r\n","");
        int r=m_body.indexOf("}");
        m_body=m_body.mid(r,-1);

        m_BodytoString=QString::fromUtf8(QByteArray::fromBase64(m_body));

        m_BodytoString=QString::fromUtf8(QByteArray::fromBase64(m_body));
        cleanText(m_BodytoString,m_EmailFieldsOpap);
        originator->setErpId(4);

        customer->setName(readField("POS Name:").left(255));
        customer->setLocation(readField("POS Code:").left(255));
        customer->setPhone1(readField("Main Phone:").remove("'").left(20));
        customer->setPhone2(readField("Secondary Phone:").remove("'").left(20));
        customer->setOriginatorId(originator->ErpId());



        ticket->setOriginator(originator);
        ticket->setCustomer(customer);
        ticket->setTitle(readField("Code Type:").left(50));

        ticket->setIncident(readField("Service Request:").left(30));

        ticket->setReportedDate(QLocale().toDateTime(readField("Date Opened:"),"dd/MM/yyyy hh:mm:ss"));
        //ticket->setDescription(m_body);

        ticket->setAppointmentFrom(QLocale().toDateTime(readField("Response Time:"),"dd/MM/yyyy hh:mm:ss"));
        ticket->setTrnDate(QDateTime::currentDateTime());
        ticket->setDescription(m_BodytoString);
        ticket->setCustomerTicketNo(ticket->Incident());


    }
    else
    {
        m_BodytoString=QString::fromUtf8(m_body);
        decodeQuotedPrintable(m_BodytoString);
        cleanText(m_BodytoString,m_EmailFieldsNormal);
        QString company=readField("Company");
        if (company.contains("CARDLINK"))
        {
            originator->setErpId(9);

        }

        if (company.contains("FIELD"))
        {
            originator->setErpId(8);

        }

        if (company.contains("WIND"))
        {
            originator->setErpId(2);

        }

        if (company.contains("HOL"))
        {
            QString customerTicket=readField("Customer Ticket No");
            if (customerTicket.contains("H"))
                originator->setErpId(5);
            else
                originator->setErpId(1);



        }


        customer->setName(readField("Recipient").left(255));
        customer->setLocation(readField("Location").left(255));
        customer->setCity(readField("City").left(255));
        customer->setCounty(readField("County").left(255));
        customer->setAddress(readField("Address").left(255));
        customer->setEmail(readField("Email"));
        customer->setPhone2(readField("Phone").remove("'").left(20));
        customer->setOriginatorId(originator->ErpId());



        ticket->setOriginator(originator);
        ticket->setCustomer(customer);
        ticket->setIncident(readField("Incident"));
        ticket->setTitle(readField("Title").left(50));
        ticket->setService(readField("Service"));
        ticket->setDepartment(readField("Department").left(30));

        ticket->setReportedDate(QLocale().toDateTime(readField("Reported Date"),"ddd MMM d yyyy hh:mm:ss"));
        ticket->setDescription(readField("Description"));
        ticket->setCustomerTicketNo(readField("Customer Ticket No").left(50));
        //TODO Parametric date format
        ticket->setAppointmentFrom(QLocale().toDateTime(readField("Appointment From"),"ddd MMM d yyyy hh:mm:ss"));
        qDebug()<<"APPPPPPP"<<ticket->AppointmentFrom();
        ticket->setAppointmentTo(QLocale().toDateTime(readField("Appointment To"),"ddd MMM d yyyy hh:mm:ss"));
        ticket->setTrnDate(QDateTime::currentDateTime());


        ticket->setPriority(readField("Priority").left(1).toInt());

        parseDescription(customer,ticket);



    }











    originator->persist(tableList);
    QThread::msleep(1000);
    customer->persist(tableList);
    QThread::msleep(5000);
    ticket->persist(tableList);
    QThread::msleep(5000);

mutex.unlock();









    qDebug()<<customer;



}

QString Email::BodytoString() const
{
    return m_BodytoString;
}

void Email::setBodytoString(const QString &BodytoString)
{
    m_BodytoString = BodytoString;
}

QString Email::readField(const QString &fieldName)
{
    QString sf("!@#"+fieldName+":");
    int start=m_BodytoString.indexOf(sf,0)+fieldName.size()+4;
    int end=m_BodytoString.indexOf("!@#",start);
    QString value=m_BodytoString.mid(start,end-start).trimmed();
    if (fieldName=="Phone")
    {
        value.replace("+0030","");
        value.replace(QRegExp("\\+[0-9]{2}"),"");
        value.replace(QRegExp("[A-Za-zα-ωΑ-Ωά-ώ]"),"");
        value.replace(QRegExp("[-|:& ]"),",");
        value.replace(QRegExp(",{2,99}"),",");
        value.replace(QRegExp("2[0-9]{9}"),"");
        value.replace(QRegExp(",$"),"");
        value.replace(QRegExp("^,"),"");

    }

    if (fieldName=="Incident")
    {
        QRegExp rg("[A-Z]{2}[0-9]{6,}");
        int r=rg.indexIn(value);
        QStringList testlist=rg.capturedTexts();
        value=testlist[0];
    }

    if (fieldName=="Service Request:")
    {
        QRegExp rg("[0-9]{1}\-[0-9]{8,}");
        int r=rg.indexIn(m_BodytoString);
        QStringList testlist=rg.capturedTexts();
        value=testlist[0];

    }
    /*
    if (fieldName=="Appointment To")
    {
        value=m_body.mid(start,24).trimmed();
    }
    */




    qDebug()<<fieldName<<":"<<value;
    return value;
}

void Email::cleanText(QString &text,const QStringList &fieldList)
{
    //text.replace("\r\n"," ");
    //OPAP TILL HEre
    text.replace("C2A0"," ");
    text.replace(" GMT+0300","");
    text.replace(" GMT+0200","");
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
    text.replace("&#39;","");
    text.replace("&nbsp;","");
    //Special replacements

    text.replace("Service Recipient","Recipient");




}

void Email::parseDescription(Customer *cptr,Ticket* tptr)
{
    QString description=readField("Description");
    QRegExp landline("2[0-9]{9}");
    QRegExp mobile("6[0-9]{9}");
    QRegExp loopnumber("21[BbΒβ][0-9]{7}");
    if (landline.indexIn(description)>0)
        cptr->setPhone1(description.mid(landline.indexIn(description),10).remove("'"));
    //TODO Αν υπάρχει ήδη το κινητο στο phone να μην το ξαναπροσθέτει
    if (mobile.indexIn(description)>0)
        cptr->setPhone2(description.mid(mobile.indexIn(description),10).remove("'")+","+cptr->Phone2().remove("'"));
    if (loopnumber.indexIn(description)>0)
        cptr->setLoopNumber(description.mid(loopnumber.indexIn(description),10));
    QRegExp subCategory("#Σύμπτωμα βλάβης:");
    if (subCategory.indexIn(description)>0)
    {
        int start=subCategory.indexIn(description);
        QString part=description.mid(start+17,-1);
        int end=part.indexOf("#");
        part=part.left(end);
        tptr->setSubCategory(part);

    }

    QRegExp eskalit("#Όριο στο εσκαλίτ:");
    if (eskalit.indexIn(description)>0)
    {
        int start=eskalit.indexIn(description);
        QString part=description.mid(start+18,-1);
        int end=part.indexOf("#");
        part=part.left(end);
        tptr->setEscalit(part);
        qDebug()<<"ΕΣΚΑΛΙΤ"<<tptr->Escalit();

    }

    eskalit.setPattern("Escalate Limit:");
    if (eskalit.indexIn(description)>0)
    {
        int start=eskalit.indexIn(description);
        QString part=description.mid(start+15,-1);
        int end=part.indexOf(":");
        part=part.left(end-3);
        tptr->setEscalit(part);
        qDebug()<<"ΕSCALIT:"<<tptr->Escalit();

    }


    QRegExp oteport("OTE Port:");
    if (oteport.indexIn(description)>0)
    {
        int start=oteport.indexIn(description);
        QString part=description.mid(start+9,-1);
        int end=part.indexOf("OTE Site");
        part=part.left(end);
        tptr->setOtePort(part);

    }









}

void Email::decodeQuotedPrintable(QString &text)
{


    text.replace("\r\n","");
    text.replace("==","=");
    text.replace("&amp;","&");
    text.replace("=C2=A0"," ");
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
    text.replace("=CE=89","ω");
    text.replace("=CE=8A","Ί");
    text.replace("=CE=8C","ό");
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
