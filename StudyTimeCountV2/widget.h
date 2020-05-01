#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "timecount.h"

// 添加类的前置声明
class QSqlTableModel;
class timeCount;
class QTimer;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_showTableBtn_clicked();

    void on_chooseTask_currentTextChanged(const QString &arg1);

    void on_addTaskBtn_clicked();

    void on_deleteBtn_clicked();

    void on_startTaskBtn_clicked();

    void on_stopTaskBtn_clicked();

    void on_deleteTaskBtn_clicked();

    void on_amendBtn_clicked();

    void on_amendCancelBtn_clicked();

    void timerUpdate();//更新时间

private:
    Ui::Widget *ui;
    QSqlTableModel *model;
    timeCount *item;
    QTimer *timer;
};

// 一些函数调用
QString addZero(const int n);//当数字为单数时在前面加0
QString ymd2qstring(const int date[]);// 将年月日转换为QString类型
QString hms2qstring(const int time[]);// 将时间转换为QString类型

#endif // WIDGET_H
