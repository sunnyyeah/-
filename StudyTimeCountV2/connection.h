#ifndef CONNECTION_H
#define CONNECTION_H

#include<QMessageBox>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QStringList>
#include<QtDebug>

static bool createConnection() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("studytimecountqt");	// 选择要操作的数据库名，该数据库已经在MySQL中创建
    db.setUserName("root");
    db.setPassword("weibiyun");

    if (!db.open()) {
        QMessageBox::critical(nullptr, QObject::tr("无法打开数据库!"),
                              "无法创建数据库连接.", QMessageBox::Cancel);
        return false;
    }

    // 下面创建表
    // 如果MySQL数据库中已经存在同名的表，那么下面的代码不会执行
    QSqlQuery query;

    // 创建存储学习记录表
    bool success1 = query.exec("create table studytask(id varchar(20) primary key, date varchar(20),"
                              "task varchar(50) , totaltime varchar(20), "
                               "starttime varchar(20), stoptime varchar(20)) ");
    if(success1)
        qDebug() << "创建成功";

    // 创建存储任务的表
    bool success2 = query.exec("create table task(id varchar(20) primary key,name varchar(50)) ");
    query.exec("insert into task values(0,'请选择任务')");
    query.exec("insert into task values(1,'OpenCV走线项目')");
    if(success2)
        qDebug() << "创建成功";


    return true;

}


#endif // CONNECTION_H
