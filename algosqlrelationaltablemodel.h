#ifndef ALGOSQLRELATIONALTABLEMODEL_H
#define ALGOSQLRELATIONALTABLEMODEL_H
#include <QSqlRelationalTableModel>
#include <QSqlDatabase>




class AlgoSqlRelationalTableModel : public QSqlRelationalTableModel
{
    Q_OBJECT
public:
    AlgoSqlRelationalTableModel(QObject* parent=0,QSqlDatabase db=QSqlDatabase());
    ~AlgoSqlRelationalTableModel();

    Q_INVOKABLE QVariant data(const QModelIndex &index, int role=Qt::DisplayRole ) const;
    void generateRoleNames();
    QHash<int, QByteArray> roleNames() const {return roles; }
    Q_INVOKABLE void setSort(int column,Qt::SortOrder order);
    Q_INVOKABLE void setFilter(const QString& filter);

private:
    QHash<int, QByteArray> roles;

};

#endif // ALGOSQLRELATIONALTABLEMODEL_H
