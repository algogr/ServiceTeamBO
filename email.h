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

    QString body() const;
    void setBody(const QString &body);
    Ticket* createTicket(const QList<QAbstractItemModel*>& tableList);



private:
    QString m_body;
    QString readField(const QString &fieldName);
    void decodeQuotedPrintable(QString &text);
    void cleanText(QString &text);



signals:

public slots:
};

#endif // EMAIL_H
