#include"item.h"

int main() {
	showMenu();

	char updateScreem = 'a';
	Item task;
	while (true) {
		char select = '0';
		cout << "ѡ�������";
		cin >> select;

		if (select == '1') {
			cout << "������������Ϊ��";
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
time_t now = time(0);		// ��1970�꣬�����ڹ��˶�����
cout << now << endl;

char * dt = ctime(&now);	// ��nowת��Ϊ�ַ�����ʽ
cout << dt << endl;			// �����ǰʱ���ַ�����Sun Apr 26 21:40:42 2020

// ��nowת��Ϊtm���ݽṹ��ʽ
tm *ltm = localtime(&now);
cout << "�꣺" << 1900 + ltm->tm_year << endl;
cout << "�£�" << 1 + ltm->tm_mon << endl;
cout << "�գ�" << ltm->tm_mday << endl;
cout << "ʱ�䣺" << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec << endl;

int hour = ltm->tm_hour;
cout << hour << endl;
*/