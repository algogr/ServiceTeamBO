#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "mailreader.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include "algosqltablemodel.h"
#include <QAbstractItemModel>


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QList <QAbstractItemModel*> TableModelsList;

    //TODO parametric credentials

    QSqlDatabase db1=QSqlDatabase::addDatabase("QMYSQL","local");
    db1.setDatabaseName("ServiceTeam");
    db1.setHostName("localhost");
    db1.setPort(3306);
    db1.setUserName("root");
    db1.setPassword("101264");



    QSqlDatabase db2=QSqlDatabase::addDatabase("QMYSQL","erp");
    db2.setDatabaseName("hourglass");
    db2.setHostName("localhost");
    db2.setPort(3306);
    db2.setUserName("root");
    db2.setPassword("101264");

    if (db1.open()==false)
    {
        qDebug()<<"Error on MySQL:"<< db1.lastError().text();
        exit(0);
    }

    if (db2.open()==false)
    {
        qDebug()<<"Error on ERP:"<< db2.lastError().text();
        exit(0);
    }

    AlgoSqlTableModel* cusLModel = new AlgoSqlTableModel(0,db1);
    cusLModel->setTable("Customer");
    cusLModel->sort(1,Qt::SortOrder::AscendingOrder);
    cusLModel->generateRoleNames();
    cusLModel->setFilter("");
    cusLModel->select();



    AlgoSqlTableModel* cusEModel = new AlgoSqlTableModel(0,db2);
    cusEModel->setTable("Customer");
    cusEModel->sort(1,Qt::SortOrder::AscendingOrder);
    cusEModel->generateRoleNames();
    cusEModel->setFilter("");
    cusEModel->select();

    AlgoSqlTableModel* origLModel = new AlgoSqlTableModel(0,db1);
    origLModel->setTable("Originator");
    origLModel->sort(1,Qt::SortOrder::AscendingOrder);
    origLModel->generateRoleNames();
    origLModel->setFilter("");
    origLModel->select();

    AlgoSqlTableModel* origEModel = new AlgoSqlTableModel(0,db2);
    origEModel->setTable("Originator");
    origEModel->sort(1,Qt::SortOrder::AscendingOrder);
    origEModel->generateRoleNames();
    origEModel->setFilter("");
    origEModel->select();


    AlgoSqlTableModel* ticketLModel = new AlgoSqlTableModel(0,db1);
    ticketLModel->setTable("Originator");
    ticketLModel->sort(1,Qt::SortOrder::AscendingOrder);
    ticketLModel->generateRoleNames();
    ticketLModel->setFilter("");
    ticketLModel->select();

    AlgoSqlTableModel* ticketEModel = new AlgoSqlTableModel(0,db2);
    ticketEModel->setTable("Originator");
    ticketEModel->sort(1,Qt::SortOrder::AscendingOrder);
    ticketEModel->generateRoleNames();
    ticketEModel->setFilter("");
    ticketEModel->select();

    TableModelsList.append(cusLModel); //0
    TableModelsList.append(cusEModel); //1
    TableModelsList.append(origLModel); //2
    TableModelsList.append(origEModel); //3
    TableModelsList.append(ticketLModel); //4
    TableModelsList.append(ticketEModel); //5


    MailReader* rd=new MailReader(0,TableModelsList);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
