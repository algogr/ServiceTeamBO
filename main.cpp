
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "mailreader.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include "algosqltablemodel.h"
#include <QAbstractItemModel>
#include "algolocation.h"
#include "ticketmanager.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QList <QAbstractItemModel*> TableModelsList;

    //TODO parametric credentials

    QSqlDatabase db1=QSqlDatabase::addDatabase("QMYSQL","serviceteam");
    db1.setDatabaseName("ServiceTeam");
    db1.setHostName("localhost");
    db1.setPort(3306);
    db1.setUserName("root");
    db1.setPassword("101264");



    QSqlDatabase db2=QSqlDatabase::addDatabase("QODBC3","soft1");

    db2.setDatabaseName("soft1");
    db2.setHostName("192.168.2.248");
    db2.setPort(1433);
    db2.setUserName("sa");
    db2.setPassword("600096");

    if (db1.open()==false)
    {
        qDebug()<<"Error on MySQL:"<< db1.lastError().text();
        exit(0);
    }


    if (db2.open()==false)
    {
        qDebug()<<"Error on Soft1:"<< db2.lastError().text();
        //exit(0);
    }


    AlgoSqlTableModel* cusLModel = new AlgoSqlTableModel(0,db1);
    cusLModel->setTable("Customer");
    cusLModel->sort(1,Qt::SortOrder::AscendingOrder);
    cusLModel->generateRoleNames();
    cusLModel->setFilter("");
    cusLModel->select();



    AlgoSqlTableModel* cusEModel = new AlgoSqlTableModel(0,db2);
    cusEModel->setTable("TRDR");
    cusEModel->sort(1,Qt::SortOrder::AscendingOrder);
    cusEModel->generateRoleNames();
    qDebug()<<cusEModel->roleNames();
    cusEModel->setFilter("");
    cusEModel->select();

    AlgoSqlTableModel* origLModel = new AlgoSqlTableModel(0,db1);
    //origLModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    origLModel->setTable("Originator");
    origLModel->sort(1,Qt::SortOrder::AscendingOrder);
    origLModel->generateRoleNames();
    origLModel->setFilter("");
    origLModel->select();

    AlgoSqlTableModel* origEModel = new AlgoSqlTableModel(0,db2);
    origEModel->setTable("CCCETERIA");
    origEModel->sort(1,Qt::SortOrder::AscendingOrder);
    origEModel->generateRoleNames();
    origEModel->setFilter("");
    origEModel->select();


    AlgoSqlTableModel* ticketLModel = new AlgoSqlTableModel(0,db1);
    ticketLModel->setTable("Ticket");
    ticketLModel->sort(1,Qt::SortOrder::AscendingOrder);
    ticketLModel->generateRoleNames();
    ticketLModel->setFilter("");
    ticketLModel->select();

    AlgoSqlTableModel* ticketEModel = new AlgoSqlTableModel(0,db2);
    ticketEModel->setTable("CCCTEMPFINDOC");
    ticketEModel->sort(1,Qt::SortOrder::AscendingOrder);
    ticketEModel->generateRoleNames();
    ticketEModel->setFilter("");
    ticketEModel->select();

    AlgoSqlTableModel* customerTempEModel = new AlgoSqlTableModel(0,db2);
    customerTempEModel->setTable("CCCTEST1");
    customerTempEModel->sort(1,Qt::SortOrder::AscendingOrder);
    customerTempEModel->generateRoleNames();
    customerTempEModel->setFilter("");
    customerTempEModel->select();

    TableModelsList.append(cusLModel); //0
    TableModelsList.append(cusEModel); //1
    TableModelsList.append(origLModel); //2
    TableModelsList.append(origEModel); //3
    TableModelsList.append(ticketLModel); //4
    TableModelsList.append(ticketEModel); //5
    TableModelsList.append(customerTempEModel);//6


    //MailReader* rd=new MailReader(0,TableModelsList);
    TicketManager* manager=new TicketManager(0,TableModelsList);






    QQmlApplicationEngine engine;
    //engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    //if (engine.rootObjects().isEmpty())
      //  return -1;

    return app.exec();
}
