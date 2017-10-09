#include "ticket.h"
#include "algosqltablemodel.h"
#include <QSqlRecord>
#include <QDebug>
#include <QSqlError>

Ticket::Ticket(QObject *parent):QObject(),m_id(),m_ErpId(),m_Incident(),\
    m_Originator(),m_Customer(),m_Title(),m_Service(),\
    m_ReportedDate(),m_Priority(),m_Description(),\
    m_CustomerTicketNo(),m_AppointmentFrom(),m_AppointmentTo()


{

}

QString Ticket::Incident() const
{
    return m_Incident;
}

void Ticket::setIncident(const QString &Incident)
{
    m_Incident = Incident;
}

QString Ticket::Title() const
{
    return m_Title;
}

void Ticket::setTitle(const QString &Title)
{
    m_Title = Title;
}


QString Ticket::Description() const
{
    return m_Description;
}

void Ticket::setDescription(const QString &Description)
{
    m_Description = Description;
}

QString Ticket::CustomerTicketNo() const
{
    return m_CustomerTicketNo;
}

void Ticket::setCustomerTicketNo(const QString &CustomerTicketNo)
{
    m_CustomerTicketNo = CustomerTicketNo;
}

Originator *Ticket::originator() const
{
    return m_Originator;
}

void Ticket::setOriginator(Originator *originator)
{
    m_Originator = originator;
}


Customer *Ticket::customer() const
{
    return m_Customer;
}

void Ticket::setCustomer(Customer *customer)
{
    m_Customer = customer;
}

QDateTime Ticket::ReportedDate() const
{
    return m_ReportedDate;
}

void Ticket::setReportedDate(const QDateTime &ReportedDate)
{
    m_ReportedDate = ReportedDate;
}

QDateTime Ticket::AppointmentFrom() const
{
    return m_AppointmentFrom;
}

void Ticket::setAppointmentFrom(const QDateTime &AppointmentFrom)
{
    m_AppointmentFrom = AppointmentFrom;
}

QDateTime Ticket::AppointmentTo() const
{
    return m_AppointmentTo;
}

void Ticket::setAppointmentTo(const QDateTime &AppointmentTo)
{
    m_AppointmentTo = AppointmentTo;
}

QString Ticket::Service() const
{
    return m_Service;
}

void Ticket::setService(const QString &Service)
{
    m_Service = Service;
}


int Ticket::Priority() const
{
    return m_Priority;
}

void Ticket::setPriority(int Priority)
{
    m_Priority = Priority;
}

int Ticket::id() const
{
    return m_id;
}

void Ticket::setId(int id)
{
    m_id = id;
}

int Ticket::ErpId() const
{
    return m_ErpId;
}

void Ticket::setErpId(int ErpId)
{
    m_ErpId = ErpId;
}

void Ticket::persist(const QList<QAbstractItemModel *> &tableList)
{
    AlgoSqlTableModel *tl= qobject_cast<AlgoSqlTableModel*> (tableList.at(4));

    tl->setTable("Ticket");
    qDebug()<<"Rows:"<<tl->rowCount();
    tl->setFilter("incident='"+Incident()+"'");
    tl->select();

    //TODO  Add code when ERP connection is ready
    if (tl->rowCount()==0)
    {

        tl->setFilter("");
        tl->select();

        QSqlRecord r= tl->record();
        r.setValue("originatorid",m_Originator->Id());
        qDebug()<<"OriginatorId"<<m_Originator->Id();
        qDebug()<<"CustomerId"<<m_Customer->Id();
        r.setValue("cusid",m_Customer->Id());
        r.setValue("erpcusid",m_Customer->ErpId());
        r.setValue("title",Title());
        r.setValue("service",Service());
        r.setValue("reporteddate",ReportedDate());
        r.setValue("priority",Priority());
        r.setValue("description",Description());
        r.setValue("customerticketno",CustomerTicketNo());
        r.setValue("appointmentfrom",AppointmentFrom());
        r.setValue("appointmentto",AppointmentTo());
        r.setValue("incident",Incident());
        r.setValue("department",Department());

        tl->insertRecord(-1,r);
        if(tl->submitAll()) {
            qDebug()<<"Commit:"<<Incident();
            tl->database().commit();
        }
        else {
            tl->database().rollback();
                    qDebug() << "Database Write Error" <<
                         "The database reported an error: " <<
                          tl->lastError().text();

        }




    }
    else
    {
        return;

    }

}


void Ticket::retrieve(const QList<QAbstractItemModel*> &tableList)
{

}

QString Ticket::Department() const
{
    return m_Department;
}

void Ticket::setDepartment(const QString &Department)
{
    m_Department = Department;
}
