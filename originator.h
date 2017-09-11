#ifndef ORIGINATOR_H
#define ORIGINATOR_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QAbstractItemModel>

class Originator : public QObject
{
    Q_OBJECT
public:
    explicit Originator(QObject *parent = nullptr);

    Q_INVOKABLE QString Name() const;
    Q_INVOKABLE void setName(const QString &Name);

    QString code() const;
    void setCode(const QString &code);

    int Id() const;
    void setId(int Id);

    int ErpId() const;
    void setErpId(int ErpId);


    void persist(const QList<QAbstractItemModel*> &tableList);
    void retrieve(const QList<QAbstractItemModel*> &tableList);

private:
    QString m_code,m_Name;
    int m_Id,m_ErpId;

signals:

public slots:
};

#endif // ORIGINATOR_H
