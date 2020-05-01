#include "widget.h"
#include "ui_widget.h"
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QTimer>
#include <QDateTime>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 初始状态显示的界面为第一个页
    ui->stackedWidget->setCurrentIndex(0);

    // 实例化timer
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Widget::timerUpdate);

    // 实例化item对象
    item = new timeCount();

    // 实例化model
    model = new QSqlTableModel(this);
    // 将模型设置到视图中
    ui->tableView->setModel(model);
    // 设置编辑策略——如果没有这句就无法对viewTable中的表信息进行增删改
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    // 设置ComboBox的初始值
    QSqlQueryModel *taskmodel = new QSqlQueryModel(this);
    taskmodel->setQuery("select name from task");
    ui->chooseTask->setModel(taskmodel);

    // 使一些按钮不可用
    ui->startTaskBtn->setEnabled(false);
    ui->stopTaskBtn->setEnabled(false);
    ui->deleteTaskBtn->setEnabled(false);
}

Widget::~Widget()
{
    delete ui;
}

// 显示学习状况
void Widget::on_showTableBtn_clicked()
{
    // 跳转到第二页
    ui->stackedWidget->setCurrentIndex(1);

    model->setTable("studytask");
    model->setHeaderData(0,Qt::Horizontal,tr("序号"));
    model->setHeaderData(1,Qt::Horizontal,tr("日期"));
    model->setHeaderData(2,Qt::Horizontal,tr("任务"));
    model->setHeaderData(3,Qt::Horizontal,tr("时长"));
    model->setHeaderData(4,Qt::Horizontal,tr("StartTime"));
    model->setHeaderData(5,Qt::Horizontal,tr("FinishTime"));

    //ui->amendBtn->setEnable(true);

    model->select();
}

// 选择任务——comboBox设置
void Widget::on_chooseTask_currentTextChanged(const QString &task)
{
    if(task == "请选择任务"){
        ui->startTaskBtn->setEnabled(false);
        ui->deleteTaskBtn->setEnabled(false);
        ui->addTaskBtn->setEnabled(true);
    }
    else{
        ui->startTaskBtn->setEnabled(true);
        ui->addTaskBtn->setEnabled(false);
        ui->deleteTaskBtn->setEnabled(true);
    }
}

// 添加任务按钮
void Widget::on_addTaskBtn_clicked()
{
    QString task = ui->taskEdit->text();
    if(task != NULL){
        // 新添加一行
        QSqlQuery query;
        query.exec("select id from task");
        query.last();
        qreal temp = query.value(0).toInt() + 1;
        qDebug() << temp;

        QString id;
        id = QString::number(temp);
        qDebug() << id;

        // 事务操作
        QSqlDatabase::database().transaction();
        bool rtn = query.exec(QString("insert into task values('%1','%2')").arg(id).arg(task));
        if(rtn){
            QSqlDatabase::database().commit();
            QMessageBox::information(this, tr("提示"),tr("添加成功"),QMessageBox::Ok);
        }
        else{
            QSqlDatabase::database().rollback();
            QMessageBox::information(this, tr("提示"),tr("添加失败"),QMessageBox::Ok);
        }

        // 修改ComboBox中的值
        QSqlQueryModel *taskmodel = new QSqlQueryModel(this);
        taskmodel->setQuery("select name from task");
        ui->chooseTask->setModel(taskmodel);

        // 清空edit中的值
        ui->taskEdit->clear();
    }
}

// 删除任务——比较这个部分的操作和“删除一条记录的操作”，会发现使用tableView和不使用时的操作方法不同
void Widget::on_deleteTaskBtn_clicked()
{
    QString task = ui->chooseTask->currentText();//获取要删除的任务名

    QSqlQuery query;

    int ok = QMessageBox::warning(this, tr("删除当前行！"),
        tr("你确定删除当前行吗？"), QMessageBox::Yes, QMessageBox::No);
    // 事务处理
    QSqlDatabase::database().transaction();
    if (ok == QMessageBox::No) {
        // 如果不删除就不做任何处理
        qDebug() << "撤销删除";
    }
    else {//否则提交，在数据库中删除该行
        bool rtn = query.exec(QString("delete from task where name='%1'").arg(task));

        if(rtn){
            QSqlDatabase::database().commit();
            QMessageBox::information(this, tr("提示"),tr("删除成功"),QMessageBox::Ok);
        }
        else{
            QSqlDatabase::database().rollback();
            QMessageBox::information(this, tr("提示"),tr("删除失败"),QMessageBox::Ok);
        }
        qDebug() << "删除成功";
    }


    // 修改ComboBox中的值
    QSqlQueryModel *taskmodel = new QSqlQueryModel(this);
    taskmodel->setQuery("select name from task");
    ui->chooseTask->setModel(taskmodel);

}

// 删除一行记录
void Widget::on_deleteBtn_clicked()
{
    // 获取选中的行
    int curRow = ui->tableView->currentIndex().row();
    // 删除该行
    model->removeRow(curRow);
    int ok = QMessageBox::warning(this, tr("删除当前行！"),
        tr("你确定删除当前行吗？"), QMessageBox::Yes, QMessageBox::No);
    if (ok == QMessageBox::No) {
        // 如果不删除就撤销
        model->revertAll();
        qDebug() << "撤销删除";
    }
    else {//否则提交，在数据库中删除该行
        model->submitAll();
        qDebug() << "成功删除";
    }
    model->select();
}

// 提交修改
void Widget::on_amendBtn_clicked()
{
    // 事务处理
    QSqlDatabase::database().transaction();
    if(model->submitAll()){
        model->database().commit();
    }
    else{
        model->database().rollback();
        QMessageBox::warning(this, tr("studytask"), tr("数据库错误:%1").arg(model->lastError().text()));
    }

}

// 撤销修改
void Widget::on_amendCancelBtn_clicked()
{
     model->revertAll();
}


// 开始学习
void Widget::on_startTaskBtn_clicked()
{
    ui->stopTaskBtn->setEnabled(true);
    ui->addTaskBtn->setEnabled(false);
    ui->chooseTask->setEnabled(false);
    ui->deleteTaskBtn->setEnabled(false);

    timerUpdate();// 显示时间
    timer->start(1000);// 启动定时器，每隔1s发射一次timeout()信号

    // 获取comboBox中的值
    QString task = ui->chooseTask->currentText();
    // 修改任务名为task
    item->amendItemName(task.toStdString());
    item->startStudy();

    ui->startTaskBtn->setEnabled(false);
}

// 结束学习
void Widget::on_stopTaskBtn_clicked()
{
    ui->stopTaskBtn->setEnabled(false);
    ui->addTaskBtn->setEnabled(true);
    ui->chooseTask->setEnabled(true);
    ui->startTaskBtn->setEnabled(true);

    timer->stop();

    item->stopStudy();
    item->countTime();

    // 获取下一行的id
    QSqlQuery query;
    query.exec("select id from studytask");
    query.last();// 指向最后一条数据
    qreal temp = query.value(0).toInt() + 1;
    qDebug() << temp;

    QString id;
    id = QString::number(temp);

    // 获取开始日期
    QString date = ymd2qstring(item->getStartYMD());

    // 获取任务名（comboBox中的值）
    QString task = ui->chooseTask->currentText();

    // 判断开始和结束是否为同一天
    if(item->isSameDay()){
        // 将学习时长保存为QString类型
        QString studytime =  QString::number(item->getItemTime(),'g',3) + "h";
        QString startstudytime = hms2qstring(item->getStartHMS());
        QString stopstudytime = hms2qstring(item->getStopHMS());

        // 事务处理
        QSqlDatabase::database().transaction();
        bool rtn = query.exec(QString("insert into studytask values('%1','%2','%3','%4','%5','%6')")
                              .arg(id).arg(date).arg(task).arg(studytime)
                              .arg(startstudytime).arg(stopstudytime));
        if(rtn){
            QSqlDatabase::database().commit();
            QMessageBox::information(this, tr("提示"),tr("添加成功"),QMessageBox::Ok);
        }
        else{
            QSqlDatabase::database().rollback();
            QMessageBox::information(this, tr("提示"),tr("添加失败"),QMessageBox::Ok);
        }
    }
    else{
        //第一天
        // 将转钟的任务名前面加上一个“#”
        task = '#' + task;

        // 第一天的学习时长
        double h = item->getStartHMS()[2] > 0 ? 24 - item->getStartHMS()[0] - 1 : 24 - item->getStartHMS()[0];
        double m = item->getStartHMS()[2] > 0 ? 60 - item->getStartHMS()[1] - 1 : 60 - item->getStartHMS()[1];
        double s = 60 - item->getStartHMS()[2];
        double totaltime = h + (s / 60.0 + m) / 60.0;

        QString studytime = QString::number(totaltime,'g',3) + 'h';

        //第二天
        // id
        QString stopid;
        stopid = QString::number(temp+1);

        // 日期
        QString stopdate = ymd2qstring(item->getStopYMD());
        // 名字和第一天一样

        // 第二天时长，由于成员变量m_itemTime中保存的时学习的总时长，因此可以直接用总时长减去第一的。
        totaltime = item->getItemTime() - totaltime;

        QString studytime2 = QString::number(totaltime,'g',3) + 'h';

        // 事务处理
        QSqlDatabase::database().transaction();
        // 插入数据
        query.exec(QString("insert into studytask values('%1','%2','%3','%4','%5','%6')")
                   .arg(id).arg(date).arg(task).arg(studytime)
                   .arg(hms2qstring(item->getStartHMS())).arg("00:00:00"));
        bool rtn = query.exec(QString("insert into studytask values('%1','%2','%3','%4,'%5','%6'')")
                              .arg(stopid).arg(stopdate).arg(task).arg(studytime2)
                              .arg("00:00:00").arg(hms2qstring(item->getStopHMS())));
        if(rtn){
            QSqlDatabase::database().commit();// 提交
            QMessageBox::information(this, tr("提示"),tr("添加成功"),QMessageBox::Ok);
        }
        else{
            QSqlDatabase::database().rollback();// 回滚
            QMessageBox::information(this, tr("提示"),tr("添加失败"),QMessageBox::Ok);
        }
    }
    model->select();
}

//更新时间
void Widget::timerUpdate(){
    ui->timeLabel->setText(QTime::currentTime().toString());
}

// 非成员函数的实现
//当数字为单数时在前面加0
QString addZero(const int n){
    if(n < 10)
        return '0' + QString::number(n);
    else return QString::number(n);
}

// 将年月日转换为QString类型
QString ymd2qstring(const int date[]){
    return QString::number(date[0]) + '/'
            + addZero(date[1]) + '/'
            + addZero(date[2]);
}

// 将时间转换为QString类型
QString hms2qstring(const int time[]){
    return addZero(time[0]) + ':'
            + addZero(time[1]) + ':'
            + addZero(time[2]);
}




