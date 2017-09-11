#ifndef TICKET_H
#define TICKET_H

#include <QObject>
#include "customer.h"
#include "originator.h"
#include <QDateTime>
#include <QSqlDatabase>


class Ticket : public QObject
{
    Q_OBJECT
public:
    explicit Ticket(QObject *parent = nullptr);

    QString Incident() const;
    void setIncident(const QString &Incident);

    QString Title() const;
    void setTitle(const QString &Title);

    QString InteractionId() const;
    void setInteractionId(const QString &InteractionId);

    QString Description() const;
    void setDescription(const QString &Description);

    QString CustomerTicketNo() const;
    void setCustomerTicketNo(const QString &CustomerTicketNo);

    Originator *originator() const;
    void setOriginator(Originator *originator);

    Customer *customer() const;
    void setCustomer(Customer *customer);

    QDateTime ReportedDate() const;
    void setReportedDate(const QDateTime &ReportedDate);

    QDateTime AppointmentFrom() const;
    void setAppointmentFrom(const QDateTime &AppointmentFrom);

    QDateTime AppointmentTo() const;
    void setAppointmentTo(const QDateTime &AppointmentTo);

    QString Service() const;
    void setService(const QString &Service);

    int Urgency() const;
    void setUrgency(int Urgency);

    int Priority() const;
    void setPriority(int Priority);

    int id() const;
    void setId(int id);

    int ErpId() const;
    void setErpId(int ErpId);

    void persist(const QList<QAbstractItemModel*> &tableList);
    void retrieve(const QList<QAbstractItemModel*> &tableList);
private:
    QString m_Incident,m_Title,m_InteractionId,m_Description,m_CustomerTicketNo,m_Service;
    Originator* m_Originator;
    Customer* m_Customer;
    QDateTime m_ReportedDate,m_AppointmentFrom,m_AppointmentTo;
    int m_id,m_ErpId,m_Urgency,m_Priority;






signals:

public slots:
};

#endif // TICKET_H
