#include "ticket.h"

Ticket::Ticket(QObject *parent)

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

QString Ticket::InteractionId() const
{
    return m_InteractionId;
}

void Ticket::setInteractionId(const QString &InteractionId)
{
    m_InteractionId = InteractionId;
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

int Ticket::Urgency() const
{
    return m_Urgency;
}

void Ticket::setUrgency(int Urgency)
{
    m_Urgency = Urgency;
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

}


void Ticket::retrieve(const QList<QAbstractItemModel*> &tableList)
{

}
