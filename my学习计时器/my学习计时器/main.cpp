#include"item.h"

int main() {
	showMenu();

	char updateScreem = 'a';
	Item task;
	while (true) {
		char select = '0';
		cout << "选择操作：";
		cin >> select;

		if (select == '1') {
			cout << "本次任务名称为：";
			string name;
			cin >> name;
			task.amendItemName(name);
		}
		choiceMenu(select, task);

		cin.get();
		if (select == '0') return 0;
		
	}
	

	return 0;
}

/*
time_t now = time(0);		// 从1970年，到现在过了多少秒
cout << now << endl;

char * dt = ctime(&now);	// 将now转换为字符串形式
cout << dt << endl;			// 输出当前时间字符串：Sun Apr 26 21:40:42 2020

// 将now转换为tm数据结构格式
tm *ltm = localtime(&now);
cout << "年：" << 1900 + ltm->tm_year << endl;
cout << "月：" << 1 + ltm->tm_mon << endl;
cout << "日：" << ltm->tm_mday << endl;
cout << "时间：" << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec << endl;

int hour = ltm->tm_hour;
cout << hour << endl;
*/