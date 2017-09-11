#include "algosqlquerymodel.h"

AlgoSqlQueryModel::AlgoSqlQueryModel(QObject* parent):QSqlQueryModel(parent)
{

}

void AlgoSqlQueryModel::setQuery(const QString &query, const QSqlDatabase &db)
{
    QSqlQueryModel::setQuery(query,db);
}

bool AlgoSqlQueryModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    QSqlQueryModel::setHeaderData(section,orientation,value,role);

}

