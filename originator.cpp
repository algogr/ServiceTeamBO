#include "originator.h"
#include "algosqltablemodel.h"

Originator::Originator(QObject *parent)

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
    AlgoSqlTableModel *ol= qobject_cast<AlgoSqlTableModel*> (tableList.at(2));


}


void Originator::retrieve(const QList<QAbstractItemModel*> &tableList)
{

}

