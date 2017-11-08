
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "mailreader.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include "algosqltablemodel.h"
#include <QAbstractItemModel>
#include <QSqlQuery>
#include "algolocation.h"
#include "ticketmanager.h"
#include <QFile>
#include <QDir>
#include <QSettings>
int main(int argc, char *argv[])
{
    QFile st(QDir::currentPath()+"/settings.ini");
    QString settingsFile=QDir::currentPath()+"/settings.ini";
    QSettings *settings=new QSettings(settingsFile,QSettings::IniFormat);

    if (!st.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        settings->setValue("dsnMySQL","serviceteam");
        settings->setValue("hostnameMySQL","localhost");
        settings->setValue("dsnSQLServer","soft1");
        settings->setValue("userSQLServer","sa");
        settings->setValue("passSQLServer","tt123!@#");
        settings->setValue("excelFullPath","c:\\jim\\tsolakidi.xls");
        settings->setValue("batchFilesPath","C:\\algo\\AutoImport\\");
        settings->setValue("cusBatchFilename","AutoRunCusImport.bat");
        settings->setValue("salBatchFilename","AutoRunSalImport.bat");
        settings->setValue("imapHostname","imap.gmail.com");
        settings->setValue("imapPort",993);
        settings->setValue("imapUser","algosakis@gmail.com");
        settings->setValue("imapPass","v@$230698");
        settings->sync();
    }
    st.close();



    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QList <QAbstractItemModel*> TableModelsList;



    QSqlDatabase db1=QSqlDatabase::addDatabase("QODBC3",settings->value("dsnMySQL").toString());
    db1.setDatabaseName(settings->value("dsnMySQL").toString());
    db1.setHostName(settings->value("hostnameMySQL").toString());



    QSqlDatabase db2=QSqlDatabase::addDatabase("QODBC3",settings->value("dsnSQLServer").toString());

    db2.setDatabaseName(settings->value("dsnSQLServer").toString());

    db2.setUserName(settings->value("userSQLServer").toString());
    db2.setPassword(settings->value("passSQLServer").toString());


    QSqlDatabase db3=QSqlDatabase::addDatabase("QODBC3");
    db3.setDatabaseName("DRIVER={Microsoft Excel Driver (*.xls, *.xlsx, *.xlsm, *.xlsb)};DBQ="+QString(settings->value("excelFullPath").toString()));


    if (db1.open()==false)
    {
        qDebug()<<"Error on MySQL:"<< db1.lastError().text();
        exit(0);
    }


    if (db2.open()==false)
    {
        qDebug()<<"Error on Soft1:"<< db2.lastError().text();
        exit(0);
    }

    if (db3.open()==false)
    {
        qDebug()<<"Error on Excel:"<< db3.lastError().text();
        //exit(0);
    }
    else
    {
        qDebug()<<db3.isOpen();
        QSqlQuery query(db3);
        query.exec("select * from [WorkOrders$]");
        while (query.next())
        {
            qDebug()<<query.value(0).toString();
        }
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
    customerTempEModel->setTable("CCCTEMPCUST");
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





/*
    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
*/
    return app.exec();
}
