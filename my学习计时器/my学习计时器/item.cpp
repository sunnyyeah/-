#include "item.h"

Item::Item(){
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

Item::Item(const string& name){
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

Item::~Item()
{
}

// 开始学习
void Item::startStudy(){
	cout << "\n*** 开始学习 ***" << endl;
	isStart = true;
	time_t now = time(0);		// 获取当前时间
	char* stime = ctime(&now);	// 转为字符串
	tm *start = localtime(&now);	// 格式转换
	m_start[0] = start->tm_hour;	// 时
	m_start[1] = start->tm_min;		// 分
	m_start[2] = start->tm_sec;		// 秒
	cout << "开始时间：" << stime << endl;
}

// 结束学习
void Item::stopStudy(){
	cout << "\n*** 已结束本次学习 ***" << endl;
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

	cout << "结束时间：" << stime << endl;
}

// 计时
void Item::countTime(){
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
	if (m_startDate[2] == m_stopDate[2]) 
		h = m_stop[0] - m_start[0] + ch;
	else  // 否则
		h = 24 + m_stop[0] - m_start[0] + ch;

	// 按小时计数
	m_itemTime = h + (s / 60.0 + m) / 60.0;
	cout << "本次学习总时长：" << m_itemTime << "h（";
	// 按时分计数(省略秒)
	int totalHM = h * 60 + m;
	int hour = totalHM / 60;
	int min = totalHM % 60;
	if (hour == 0)
		cout << min << "min）" << endl;
	else
		cout << hour << "h" << min << "min）" << endl;
	cout << endl;
		
}

// 修改任务名
void Item::amendItemName(const string& name){
	m_itemName = name;
	// 每修改一次任务名就重新开始计时。
	m_itemTime = 0.0;		
	time_t now = time(0);		// 获取当前时间
	tm *date = localtime(&now);	// 格式转换
	m_startDate[0] = 1900 + date->tm_year;
	m_startDate[1] = 1 + date->tm_mon;
	m_startDate[2] = date->tm_mday;
}

// 存档
void storeItem(const Item& task){
	// 只有执行完3才能存档
	if (task.m_itemTime == 0) {
		cout << "需要先选择操作3才能存档哦~" << endl;
		cout << endl;
		return;
	}

	ofstream fout;
	fout.open("./task_record.txt", std::ios::app);	// iOS::app表示每次写入都是追加到流尾，表示打开模式。
	if (!fout.is_open()) {
		cout << "打开失败！！！" << endl;
		return;
	}

	// 保存今天的日期
	fout << setfill('0');
	fout << task.m_startDate[0] << "-" 
		<< setw(2) << task.m_startDate[1] << "-"
		<< setw(2) << task.m_startDate[2];
	fout << setw(10) << setiosflags(ios::left) << setfill(' ')<< " ";		// 重新设置格式填充为空格,左对齐

	// 如果没有日期跨度，直接保存本次学习的时间
	if (task.m_startDate[2] == task.m_stopDate[2]) {
		fout << setw(20) << task.m_itemName;

		cout << task.m_itemTime << "h" << endl;

		fout << task.m_itemTime << "h";

		fout << setiosflags(ios::right) << setfill('0');
		fout << "（" 
			<< setw(2) << task.m_start[0] << ":" 
			<< setw(2) << task.m_start[1] << ":" 
			<< setw(2) << task.m_start[2] << " - ";
		fout << setw(2) << task.m_stop[0] << ":" 
			<< setw(2) << task.m_stop[1] << ":" 
			<< setw(2) << task.m_stop[2] << "）";
		fout << endl;
	}
	// 如果有日期跨度，需要再保存一个第二天学习的时间
	else {
		// 先保存今天的学习名称和时间，同一天的学习名前面有个#
		fout << "#" << setw(19) << task.m_itemName;

		double h = task.m_start[2] > 0 ? 24 - task.m_start[0] - 1 : 24 - task.m_start[0];
		double m = task.m_start[2] > 0 ? 60 - task.m_start[1] - 1 : 60 - task.m_start[1];
		double s = 60 - task.m_start[2];

		fout << h + (s / 60.0 + m) / 60.0 << "h";
		fout << setiosflags(ios::right) << setfill('0');
		fout << "（" 
			<< setw(2) << task.m_start[0] << ":" 
			<< setw(2) << task.m_start[1] << ":" 
			<< setw(2) << task.m_start[2] << " - ";
		fout << "00:00:00）";
		fout << endl;

		// 再保存转钟的学习日期，名称和时间
		fout << task.m_stopDate[0] << "-" 
			<< setw(2) << task.m_stopDate[1] << "-";
		fout << setw(2) << task.m_stopDate[2];

		fout << setw(10) << setiosflags(ios::left) << setfill(' ') << " ";
		fout << "#" << setw(19) << task.m_itemName;

		h = task.m_stop[0];
		m = task.m_stop[1];
		s = task.m_stop[2];

		fout << h + (s / 60.0 + m) / 60.0 << "h（00:00:00 - ";
		fout << setiosflags(ios::right) << setfill('0');
		fout << setw(2) << task.m_stop[0] << ":" 
			<< setw(2) << task.m_stop[1] << ":" 
			<< setw(2) << task.m_stop[2] << "）";
		fout << endl;
	}

	fout.close();
	cout << "保存成功！\n" << endl;
}

// 读档
void readItem(){
	ifstream fin;
	fin.open("task_record.txt", std::ios::in);
	if (!fin.is_open()) {
		cout << "打开失败！！！" << endl;
		return;
	}string strLine;		// 将读取的一行数据保存在strLine中
	while (getline(fin, strLine)) {
		cout << strLine << endl;
	}
	fin.close();
	cout << endl;
}


void showMenu(){
	cout << left;
	cout << "**************************" << endl;
	cout << "** 1.开始学习           **" << endl;
	cout << "** 2.停止学习           **" << endl;
	cout << "** 3.显示本次学习总时长 **" << endl;
	cout << "** 4.显示今天学习总时长 **" << endl;
	cout << "** 5.显示本周学习总时长 **" << endl;
	cout << "** 6.显示本月学习总时长 **" << endl;
	cout << "** 7.保存本次记录       **" << endl;
	cout << "** 8.读档               **" << endl;
	cout << "** 0.退出               **" << endl;
	cout << "** c.屏幕刷新           **" << endl;
	cout << "**************************" << endl;
	cout << endl;
}

void choiceMenu(char select, Item& task){
	switch (select){
	case '1': //1.开始学习
		task.startStudy();
		break;
	case '2':	//2.停止学习
		task.stopStudy();
		break;
	case '3':	//3.显示本次学习总时长
		task.countTime();
		break;
	case '4':	//4.显示今天学习总时长
		break;
	case '5':	//5.显示本周学习总时长
		break;
	case '6':	//6.显示本月学习总时长
		break;
	case '7':	//7.保存本次记录
		storeItem(task);
		break;
	case '8':	//8.读档
		readItem();
		break;
	case '0':	//0.退出
		cout << "很棒哦~坚持就是胜利！" << endl;
		cout << endl;
		break;
	case 'c':
		system("cls");
		showMenu();
		break;

	default:
		break;
	}
}
