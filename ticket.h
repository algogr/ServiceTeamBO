#ifndef TICKET_H
#define TICKET_H

#include <QObject>
#include "customer.h"
#include "originator.h"
#include <QDateTime>
#include <QSqlDatabase>
#include "algosqltablemodel.h"


class Ticket : public QObject
{
    Q_OBJECT
public:
    explicit Ticket(QObject *parent = nullptr);

    QString Incident() const;
    void setIncident(const QString &Incident);

    QString Title() const;
    void setTitle(const QString &Title);

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


    int Priority() const;
    void setPriority(int Priority);

    int id() const;
    void setId(int id);


    void persist(const QList<QAbstractItemModel*> &tableList);
    void retrieve(const QList<QAbstractItemModel*> &tableList);
    QString Department() const;
    void setDepartment(const QString &Department);

    QDateTime trnDate() const;
    void setTrnDate(const QDateTime &trnDate);

    QString Escalit() const;
    void setEscalit(const QString &Escalit);

    QString Job() const;
    void setJob(const QString &Job);

    QString SubJob() const;
    void setSubJob(const QString &SubJob);

    QString Category() const;
    void setCategory(const QString &Category);

    QString SubCategory() const;
    void setSubCategory(const QString &SubCategory);

    QString otePort() const;
    void setOtePort(const QString &otePort);

private:
    QString m_Incident,m_Title,m_Description,m_CustomerTicketNo,m_Service,m_Department;
    QString m_Escalit,m_Job,m_SubJob,m_Category,m_SubCategory,m_otePort;
    Originator* m_Originator;
    Customer* m_Customer;
    QDateTime m_ReportedDate,m_AppointmentFrom,m_AppointmentTo,m_trnDate;
    int m_id,m_Priority;
    void createToErp(AlgoSqlTableModel* model);







signals:

public slots:
};

#endif // TICKET_H
