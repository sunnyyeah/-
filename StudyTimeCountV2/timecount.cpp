#include "timecount.h"

timeCount::timeCount()
{
    m_itemName = "Study";
    m_itemTime = 0.0;
    for (int i = 0; i < 3; i++) {
        m_start[i] = 0;
        m_stop[i] = 0;
    }
    time_t now = time(0);		// 获取当前时间
    tm *date = localtime(&now);	// 格式转换
    m_stopDate[0] = m_startDate[0] = 1900 + date->tm_year;
    m_stopDate[1] = m_startDate[1] = 1 + date->tm_mon;
    m_stopDate[2] = m_startDate[2] = date->tm_mday;
    isStart = false;
}

timeCount::timeCount(const string& name){
    m_itemName = name;
    m_itemTime = 0.0;
    for (int i = 0; i < 3; i++) {
        m_start[i] = 0;
        m_stop[i] = 0;
    }
    time_t now = time(0);		// 获取当前时间
    tm *date = localtime(&now);	// 格式转换
    m_stopDate[0] = m_startDate[0] = 1900 + date->tm_year;
    m_stopDate[1] = m_startDate[1] = 1 + date->tm_mon;
    m_stopDate[2] = m_startDate[2] = date->tm_mday;
    isStart = false;
}

timeCount::~timeCount()
{
}

// 开始学习
void timeCount::startStudy(){
    cout << "\n*** Start Study ***" << endl;
    isStart = true;
    time_t now = time(0);		// 获取当前时间
    char* stime = ctime(&now);	// 转为字符串
    tm *start = localtime(&now);	// 格式转换
    m_start[0] = start->tm_hour;	// 时
    m_start[1] = start->tm_min;		// 分
    m_start[2] = start->tm_sec;		// 秒
    cout << "Start Time: " << stime << endl;
}

// 结束学习
void timeCount::stopStudy(){
    cout << "\n*** Finished Study ***" << endl;
    isStart = false;
    time_t now = time(0);		// 获取当前时间
    char* stime = ctime(&now);	// 转为字符串
    tm *stop = localtime(&now);	// 格式转换
    m_stop[0] = stop->tm_hour;		// 时
    m_stop[1] = stop->tm_min;		// 分
    m_stop[2] = stop->tm_sec;		// 秒

    m_stopDate[0] = 1900 + stop->tm_year;	// 年
    m_stopDate[1] = 1 + stop->tm_mon;		// 月
    m_stopDate[2] = stop->tm_mday;			// 日

   cout << "Finished Time: " << stime << endl;
}

// 计时
void timeCount::countTime(){
    double h = 0, m = 0, s = 0;
    int ch = 0, cm = 0;	// 退位标志
    s = m_stop[2] - m_start[2];
    // 当s<0，m需要退一位
    if (s < 0) {
        s += 60;
        cm -= 1;
    }
    m = cm + m_stop[1] - m_start[1];
    // 当m<0，h需要退一位
    if (m < 0) {
        m += 60;
        ch -= 1;
    }
    // 如果开始时间和结束时间是同一天
    if (isSameDay())
        h = m_stop[0] - m_start[0] + ch;
    else  // 否则
        h = 24 + m_stop[0] - m_start[0] + ch;

    // 按小时计数
    m_itemTime = h + (s / 60.0 + m) / 60.0;
    cout << "Study Total Time: " << m_itemTime << "h(";
    // 按时分计数(省略秒)
    int totalHM = h * 60 + m;
    int hour = totalHM / 60;
    int min = totalHM % 60;
    if (hour == 0)
        cout << min << "min)" << endl;
    else
        cout << hour << "h" << min << "min)" << endl;
    cout << endl;

}


// 修改任务名
void timeCount::amendItemName(const string& name){
    m_itemName = name;
    // 每修改一次任务名就重新开始计时。
    m_itemTime = 0.0;
    time_t now = time(0);		// 获取当前时间
    tm *date = localtime(&now);	// 格式转换
    m_startDate[0] = 1900 + date->tm_year;
    m_startDate[1] = 1 + date->tm_mon;
    m_startDate[2] = date->tm_mday;
}

// 判断开始和结束是否为同一天
bool timeCount::isSameDay(){
    if(m_startDate[2] == m_stopDate[2])
        return true;
    else return false;
}
