
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


    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);



    QFile st(QCoreApplication::applicationDirPath()+"/settings.ini");
    qDebug()<<"DIR1:"<<QCoreApplication::applicationDirPath();
    QString settingsFile=QCoreApplication::applicationDirPath() +"/settings.ini";
    QSettings settings(settingsFile,QSettings::IniFormat);

    if (!st.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        settings.setValue("userSQLServer","sa");
        settings.setValue("passSQLServer","tt123!@#");
        settings.setValue("excelFullPath","c:\\jim\\tsolakidi.xls");
        settings.setValue("batchFilesPath","C:\\algo\\AutoImport\\");
        settings.setValue("cusBatchFilename","AutoRunCusImport.bat");
        settings.setValue("salBatchFilename","AutoRunSalImport.bat");
        settings.setValue("imapHostname","imap.gmail.com");
        settings.setValue("imapPort",993);
        settings.setValue("imapUser","algosakis@gmail.com");
        settings.setValue("imapPass","v@$230698");
        settings.sync();
    }
    st.close();







    QList <QAbstractItemModel*> TableModelsList;




    QSqlDatabase db=QSqlDatabase::addDatabase("QODBC3",settings.value("dsnSQLServer").toString());

    db.setDatabaseName(settings.value("dsnSQLServer").toString());

    db.setUserName(settings.value("userSQLServer").toString());
    db.setPassword(settings.value("passSQLServer").toString());


    QSqlDatabase dbe=QSqlDatabase::addDatabase("QODBC3");
    dbe.setDatabaseName("DRIVER={Microsoft Excel Driver (*.xls, *.xlsx, *.xlsm, *.xlsb)};DBQ="+QString(settings.value("excelFullPath").toString()));




    if (db.open()==false)
    {
        qDebug()<<"Error on Soft1:"<< db.lastError().text();
        exit(0);
    }

    if (dbe.open()==false)
    {
        qDebug()<<"Error on Excel:"<< dbe.lastError().text();
        //exit(0);
    }
    else
    {
        qDebug()<<dbe.isOpen();
        QSqlQuery query(dbe);
        query.exec("select * from [WorkOrders$]");
        while (query.next())
        {
            qDebug()<<query.value(0).toString();
        }
        //exit(0);
    }





    AlgoSqlTableModel* cusEModel = new AlgoSqlTableModel(0,db);
    cusEModel->setTable("TRDR");
    cusEModel->sort(1,Qt::SortOrder::AscendingOrder);
    cusEModel->generateRoleNames();
    qDebug()<<cusEModel->roleNames();
    cusEModel->setFilter("");
    cusEModel->select();


    AlgoSqlTableModel* origEModel = new AlgoSqlTableModel(0,db);
    origEModel->setTable("CCCETERIA");
    origEModel->sort(1,Qt::SortOrder::AscendingOrder);
    origEModel->generateRoleNames();
    origEModel->setFilter("");
    origEModel->select();



    AlgoSqlTableModel* ticketEModel = new AlgoSqlTableModel(0,db);
    ticketEModel->setTable("CCCTEMPFINDOC");
    ticketEModel->sort(1,Qt::SortOrder::AscendingOrder);
    ticketEModel->generateRoleNames();
    ticketEModel->setFilter("");
    ticketEModel->select();

    AlgoSqlTableModel* customerTempEModel = new AlgoSqlTableModel(0,db);
    customerTempEModel->setTable("CCCTEMPCUST");
    customerTempEModel->sort(1,Qt::SortOrder::AscendingOrder);
    customerTempEModel->generateRoleNames();
    customerTempEModel->setFilter("");
    customerTempEModel->select();


    TableModelsList.append(cusEModel); //0
    TableModelsList.append(origEModel); //1
    TableModelsList.append(ticketEModel); //2
    TableModelsList.append(customerTempEModel);//3


    TicketManager* manager=new TicketManager(0,TableModelsList);





/*
    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
*/
    return app.exec();
}
