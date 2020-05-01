#include "widget.h"
#include "connection.h"
#include <QProcess>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //运行MySQL数据库
    QProcess process;
    process.start("D:/installers/MySQL/mysql-8.0.19-winx64/bin/mysqld.exe");

    if (!createConnection()) return 0;

    Widget w;
    w.show();
    return a.exec();
}
