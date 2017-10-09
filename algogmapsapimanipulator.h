#ifndef ALGOGMAPSAPIMANIPULATOR_H
#define ALGOGMAPSAPIMANIPULATOR_H
#include <QString>
#include <QVariantList>


class AlgoGMapsApiManipulator
{
public:
    AlgoGMapsApiManipulator();
    static QString readPostalCode(const QString &jsonData);
    static QVariantList readLocation(const QString &jsonData);
    static QVariantList readResults(const QString &jsonData);
};

#endif // ALGOGMAPSAPIMANIPULATOR_H
