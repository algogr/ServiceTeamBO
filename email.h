#ifndef EMAIL_H
#define EMAIL_H

#include <QObject>
#include "ticket.h"
#include <QSqlDatabase>
#include <QAbstractItemModel>


class Email : public QObject
{
    Q_OBJECT
public:
    explicit Email(QObject *parent = nullptr);

    QByteArray body() const;
    void setBody(const QByteArray &body);
    Ticket* createTicket(const QList<QAbstractItemModel*>& tableList);



    QString BodytoString() const;
    void setBodytoString(const QString &BodytoString);

private:
    QByteArray m_body;
    QString m_BodytoString;
    QString readField(const QString &fieldName);
    void decodeQuotedPrintable(QString &text);
    void cleanText(QString &text,const QStringList &fieldList);
    QStringList m_EmailFieldsNormal,m_EmailFieldsOpap;
    void parseDescription(Customer* cptr,Ticket* tptr);





signals:

public slots:
};

#endif // EMAIL_H
