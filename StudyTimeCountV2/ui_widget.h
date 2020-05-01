/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *startTaskBtn;
    QPushButton *stopTaskBtn;
    QComboBox *chooseTask;
    QLineEdit *taskEdit;
    QPushButton *addTaskBtn;
    QPushButton *showTableBtn;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QLabel *label;
    QLabel *timeLabel;
    QWidget *page_3;
    QTableView *tableView;
    QPushButton *deleteBtn;
    QWidget *page_2;
    QPushButton *deleteTaskBtn;
    QPushButton *amendBtn;
    QPushButton *amendCancelBtn;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(716, 484);
        startTaskBtn = new QPushButton(Widget);
        startTaskBtn->setObjectName(QStringLiteral("startTaskBtn"));
        startTaskBtn->setGeometry(QRect(420, 10, 81, 61));
        stopTaskBtn = new QPushButton(Widget);
        stopTaskBtn->setObjectName(QStringLiteral("stopTaskBtn"));
        stopTaskBtn->setGeometry(QRect(510, 10, 81, 61));
        chooseTask = new QComboBox(Widget);
        chooseTask->setObjectName(QStringLiteral("chooseTask"));
        chooseTask->setGeometry(QRect(20, 10, 151, 22));
        taskEdit = new QLineEdit(Widget);
        taskEdit->setObjectName(QStringLiteral("taskEdit"));
        taskEdit->setGeometry(QRect(20, 50, 151, 21));
        addTaskBtn = new QPushButton(Widget);
        addTaskBtn->setObjectName(QStringLiteral("addTaskBtn"));
        addTaskBtn->setGeometry(QRect(190, 10, 101, 61));
        addTaskBtn->setStyleSheet(QStringLiteral(""));
        showTableBtn = new QPushButton(Widget);
        showTableBtn->setObjectName(QStringLiteral("showTableBtn"));
        showTableBtn->setGeometry(QRect(600, 10, 101, 61));
        stackedWidget = new QStackedWidget(Widget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(20, 80, 681, 401));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        label = new QLabel(page);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 10, 671, 38));
        QFont font;
        font.setFamily(QString::fromUtf8("\344\275\240\347\232\204\351\205\222\351\246\206\345\210\253\345\257\271\346\210\221\346\211\223\347\203\212 (\351\235\236\345\225\206\344\270\232\344\275\277\347\224\250)"));
        font.setPointSize(24);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setFrameShape(QFrame::StyledPanel);
        label->setAlignment(Qt::AlignCenter);
        timeLabel = new QLabel(page);
        timeLabel->setObjectName(QStringLiteral("timeLabel"));
        timeLabel->setGeometry(QRect(60, 80, 551, 281));
        QFont font1;
        font1.setPointSize(87);
        font1.setBold(true);
        font1.setWeight(75);
        timeLabel->setFont(font1);
        timeLabel->setAlignment(Qt::AlignCenter);
        stackedWidget->addWidget(page);
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        tableView = new QTableView(page_3);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(10, 70, 661, 331));
        deleteBtn = new QPushButton(page_3);
        deleteBtn->setObjectName(QStringLiteral("deleteBtn"));
        deleteBtn->setGeometry(QRect(360, 0, 91, 61));
        amendBtn = new QPushButton(page_3);
        amendBtn->setObjectName(QStringLiteral("amendBtn"));
        amendBtn->setGeometry(QRect(10, 0, 91, 61));
        amendCancelBtn = new QPushButton(page_3);
        amendCancelBtn->setObjectName(QStringLiteral("amendCancelBtn"));
        amendCancelBtn->setGeometry(QRect(120, 0, 91, 61));
        stackedWidget->addWidget(page_3);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        stackedWidget->addWidget(page_2);
        deleteTaskBtn = new QPushButton(Widget);
        deleteTaskBtn->setObjectName(QStringLiteral("deleteTaskBtn"));
        deleteTaskBtn->setGeometry(QRect(300, 10, 101, 61));

        retranslateUi(Widget);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", Q_NULLPTR));
        startTaskBtn->setText(QApplication::translate("Widget", "\345\274\200\345\247\213\345\255\246\344\271\240", Q_NULLPTR));
        stopTaskBtn->setText(QApplication::translate("Widget", "\347\273\223\346\235\237\345\255\246\344\271\240", Q_NULLPTR));
        addTaskBtn->setText(QApplication::translate("Widget", "\346\267\273\345\212\240\344\273\273\345\212\241", Q_NULLPTR));
        showTableBtn->setText(QApplication::translate("Widget", "\346\230\276\347\244\272\345\255\246\344\271\240\346\203\205\345\206\265", Q_NULLPTR));
        label->setText(QApplication::translate("Widget", "\345\245\275\345\245\275\345\255\246\344\271\240\357\274\214\345\244\251\345\244\251\345\220\221\344\270\212", Q_NULLPTR));
        deleteBtn->setText(QApplication::translate("Widget", "\345\210\240\351\231\244\350\256\260\345\275\225", Q_NULLPTR));
        amendBtn->setText(QApplication::translate("Widget", "\346\217\220\344\272\244\344\277\256\346\224\271", Q_NULLPTR));
        amendCancelBtn->setText(QApplication::translate("Widget", "\346\222\244\351\224\200\344\277\256\346\224\271", Q_NULLPTR));
        deleteTaskBtn->setText(QApplication::translate("Widget", "\345\210\240\351\231\244\344\273\273\345\212\241", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
