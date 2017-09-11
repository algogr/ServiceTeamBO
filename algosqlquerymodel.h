#ifndef ALGOSQLQUERYMODEL_H
#define ALGOSQLQUERYMODEL_H

#include <QSqlQueryModel>

class AlgoSqlQueryModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    AlgoSqlQueryModel(QObject* parent=0);
    Q_INVOKABLE void setQuery(const QString &query,const QSqlDatabase &db=QSqlDatabase());
    Q_INVOKABLE bool setHeaderData(int section,Qt::Orientation orientation,const QVariant &value,int role =Qt::EditRole);

};

#endif // ALGOSQLQUERYMODEL_H
