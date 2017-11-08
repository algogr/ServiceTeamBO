#include "ticket.h"
#include "algosqltablemodel.h"
#include <QSqlRecord>
#include <QDebug>
#include <QSqlError>
#include <QDir>
#include <QThread>
#include <QMutex>
#include <QSettings>

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
    QMutex mutex;
    mutex.lock();
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

        createToLocal(tl);


        AlgoSqlTableModel *te= qobject_cast<AlgoSqlTableModel*> (tableList.at(5));

        createToErp(te);

        te->select();



    }

        mutex.unlock();
        return;



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

QDateTime Ticket::trnDate() const
{
    return m_trnDate;
}

void Ticket::setTrnDate(const QDateTime &trnDate)
{
    m_trnDate = trnDate;
}

QString Ticket::Escalit() const
{
    return m_Escalit;
}

void Ticket::setEscalit(const QString &Escalit)
{
    m_Escalit = Escalit;
}

QString Ticket::Job() const
{
    return m_Job;
}

void Ticket::setJob(const QString &Job)
{
    m_Job = Job;
}

QString Ticket::SubJob() const
{
    return m_SubJob;
}

void Ticket::setSubJob(const QString &SubJob)
{
    m_SubJob = SubJob;
}

QString Ticket::Category() const
{
    return m_Category;
}

void Ticket::setCategory(const QString &Category)
{
    m_Category = Category;
}

QString Ticket::SubCategory() const
{
    return m_SubCategory;
}

void Ticket::setSubCategory(const QString &SubCategory)
{
    m_SubCategory = SubCategory;
}

QString Ticket::otePort() const
{
    return m_otePort;
}

void Ticket::setOtePort(const QString &otePort)
{
    m_otePort = otePort;
}

void Ticket::createToErp(AlgoSqlTableModel *model)
{
    QSqlRecord r= model->record();
    r.setValue("ccceteria",m_Originator->ErpId());
    qDebug()<<"trnDate():2"<<trnDate();
    r.setValue("trndate",trnDate());
    r.setValue("ccctickettitle",Title());
    r.setValue("cccservice","");
    r.setValue("cccreporteddate",ReportedDate());
    r.setValue("cccpriority",Priority());
    r.setValue("cccdescription",Description());
    r.setValue("cccticketno",CustomerTicketNo());
    r.setValue("cccappointmentfrom",AppointmentFrom());
    r.setValue("cccappointmentto",AppointmentTo());
    r.setValue("custcode",m_Customer->Code());
    r.setValue("cccincident",Incident());
    r.setValue("ccceskalit",Escalit());
    r.setValue("cccypokatigoria",SubCategory());
    r.setValue("cccoteport",otePort());

    r.setValue("isins",0);
    r.remove(0);

    model->insertRecord(-1,r);
        if(model->submitAll()) {
            qDebug()<<"Commit:"<<Incident();




            model->database().commit();

            QDir::setCurrent("c:\\algo\\autoimport");
            system("AutoRunSalImport.bat");

            QThread::msleep(5000);
        }
        else {
                model->database().rollback();
                qDebug() << "Database Write Error" <<
                         "The database reported an error: " <<
                          model->lastError().text();

        }

    return;

}

void Ticket::createToLocal(AlgoSqlTableModel *model)
{
    QSqlRecord r= model->record();
    r.setValue("originatorid",m_Originator->Id());
    qDebug()<<"OriginatorId"<<m_Originator->Id();
    qDebug()<<"CustomerId"<<m_Customer->Id();
    r.setValue("cusid",m_Customer->Id());
    r.setValue("erpcusid",m_Customer->ErpId());
    r.setValue("title",Title());
    r.setValue("service","");
    r.setValue("reporteddate",ReportedDate());
    r.setValue("priority",Priority());
    r.setValue("description",Description());
    r.setValue("customerticketno",CustomerTicketNo());
    r.setValue("appointmentfrom",AppointmentFrom());
    r.setValue("appointmentto",AppointmentTo());
    r.setValue("incident",Incident());
    r.setValue("department",Department());
    r.remove(0);

    model->insertRecord(-1,r);
    if(model->submitAll()) {
        qDebug()<<"Commit:"<<Incident();
        model->database().commit();
    }
    else {
        model->database().rollback();
                qDebug() << "Database Write Error" <<
                     "The database reported an error: " <<
                      model->lastError().text();

    }

    return;

}
