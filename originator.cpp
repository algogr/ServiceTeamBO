#include "originator.h"
#include "algosqltablemodel.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>

Originator::Originator(QObject *parent):m_Id(),m_ErpId(),m_code(),m_Name()


{


}

QString Originator::Name() const
{
    return m_Name;
}

void Originator::setName(const QString &Name)
{
    m_Name = Name;
}

int Originator::Id() const
{
    return m_Id;
}

void Originator::setId(int Id)
{
    m_Id = Id;
}

int Originator::ErpId() const
{
    return m_ErpId;
}

void Originator::setErpId(int ErpId)
{
    m_ErpId = ErpId;
}

void Originator::persist(const QList<QAbstractItemModel *> &tableList)
{



}


void Originator::retrieve(const QList<QAbstractItemModel*> &tableList)
{



}

