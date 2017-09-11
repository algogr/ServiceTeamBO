#include "customer.h"

Customer::Customer(QObject *parent)

{

}

QString Customer::Code() const
{
    return m_Code;
}

void Customer::setCode(const QString &Code)
{
    m_Code = Code;
}

QString Customer::Name() const
{
    return m_Name;
}

void Customer::setName(const QString &Name)
{
    m_Name = Name;
}

QString Customer::Location() const
{
    return m_Location;
}

void Customer::setLocation(const QString &Location)
{
    m_Location = Location;
}

QString Customer::Department() const
{
    return m_Department;
}

void Customer::setDepartment(const QString &Department)
{
    m_Department = Department;
}

QString Customer::City() const
{
    return m_City;
}

void Customer::setCity(const QString &City)
{
    m_City = City;
}

QString Customer::County() const
{
    return m_County;
}

void Customer::setCounty(const QString &County)
{
    m_County = County;
}

QString Customer::Address() const
{
    return m_Address;
}

void Customer::setAddress(const QString &Address)
{
    m_Address = Address;
}

QString Customer::Email() const
{
    return m_Email;
}

void Customer::setEmail(const QString &Email)
{
    m_Email = Email;
}

QString Customer::Phone1() const
{
    return m_Phone1;
}

void Customer::setPhone1(const QString &Phone1)
{
    m_Phone1 = Phone1;
}


QString Customer::Phone2() const
{
    return m_Phone2;
}

void Customer::setPhone2(const QString &Phone2)
{
    m_Phone2 = Phone2;
}

QString Customer::PC() const
{
    return m_PC;
}

void Customer::setPC(const QString &PC)
{
    m_PC = PC;
}

int Customer::Id() const
{
    return m_Id;
}

void Customer::setId(int Id)
{
    m_Id = Id;
}

int Customer::ErpId() const
{
    return m_ErpId;
}

void Customer::setErpId(int ErpId)
{
    m_ErpId = ErpId;
}

void Customer::persist(const QList<QAbstractItemModel*> &tableList)
{

}


void Customer::retrieve(const QList<QAbstractItemModel*> &tableList)
{

}


