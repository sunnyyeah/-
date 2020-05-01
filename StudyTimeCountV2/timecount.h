#ifndef TIMECOUNT_H
#define TIMECOUNT_H

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>
using namespace std;

class timeCount
{
public:
    timeCount();
    timeCount(const string& name);
    ~timeCount();

    // 成员函数
    void startStudy();		// 开始学习
    void stopStudy();		// 结束学习
    void countTime();		// 计时
    void amendItemName(const string& name);	// 修改任务名
    bool isSameDay();		// 判断开始和结束是否为同一天


    // 内联函数
    int* getStartYMD(){return m_startDate;}
    int* getStopYMD(){return m_stopDate;}
    int* getStartHMS(){return m_start;}
    int* getStopHMS(){return m_stop;}
    double getItemTime(){return m_itemTime;}

private:
    string m_itemName;		// 学习项目名称
    double m_itemTime;		// 本次项目所用时间
    int m_start[3];			// 记录开始学习时间，分别记录时分秒
    int m_stop[3];			// 记录结束学习时间
    int m_startDate[3];		// 记录开始学习的年月日
    int m_stopDate[3];		// 记录结束学习的年月日
    bool isStart;			// 用来标志是否开始学习

};

#endif // TIMECOUNT_H
