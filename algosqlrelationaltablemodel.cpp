#include "algosqlrelationaltablemodel.h"
#include <QSqlRecord>
#include <QDebug>


AlgoSqlRelationalTableModel::AlgoSqlRelationalTableModel(QObject *parent, QSqlDatabase db):QSqlRelationalTableModel(parent,db)
{

}

AlgoSqlRelationalTableModel::~AlgoSqlRelationalTableModel()
{

}

QVariant AlgoSqlRelationalTableModel::data(const QModelIndex &index, int role) const
{
    if(index.row() >= rowCount())
        {
            return QString("");
        }
        if(role < Qt::UserRole)
        {
            return QSqlRelationalTableModel::data(index, role);
        }
        else
        {
            // search for relationships
            for (int i = 0; i < columnCount(); i++)
            {
                if (this->relation(i).isValid())
                {

                    return record(index.row()).value(QString(roles.value(role)));
                }
            }
        // if no valid relationship was found
        return QSqlRelationalTableModel::data(this->index(index.row(), role - Qt::UserRole - 1), Qt::DisplayRole);

                    }
}

void AlgoSqlRelationalTableModel::generateRoleNames()
{

    roles.clear();

        int nbCols = this->columnCount();

        for (int i = 0; i < nbCols; i++)
        {
            roles[Qt::UserRole + i + 1] = QVariant(this->headerData(i, Qt::Horizontal).toString()).toByteArray();
        }


}

void AlgoSqlRelationalTableModel::setSort(int column, Qt::SortOrder order)
{
    QSqlRelationalTableModel::setSort(column,order);
}

void AlgoSqlRelationalTableModel::setFilter(const QString &filter)
{

    QSqlRelationalTableModel::setFilter(filter);
}


