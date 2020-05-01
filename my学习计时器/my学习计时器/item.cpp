#include "item.h"

Item::Item(){
	m_itemName = "Study";
	m_itemTime = 0.0;
	for (int i = 0; i < 3; i++) {
		m_start[i] = 0;
		m_stop[i] = 0;
	}
	time_t now = time(0);		// ��ȡ��ǰʱ��
	tm *date = localtime(&now);	// ��ʽת��
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
	time_t now = time(0);		// ��ȡ��ǰʱ��
	tm *date = localtime(&now);	// ��ʽת��
	m_stopDate[0] = m_startDate[0] = 1900 + date->tm_year;
	m_stopDate[1] = m_startDate[1] = 1 + date->tm_mon;
	m_stopDate[2] = m_startDate[2] = date->tm_mday;
	isStart = false;
}

Item::~Item()
{
}

// ��ʼѧϰ
void Item::startStudy(){
	cout << "\n*** ��ʼѧϰ ***" << endl;
	isStart = true;
	time_t now = time(0);		// ��ȡ��ǰʱ��
	char* stime = ctime(&now);	// תΪ�ַ���
	tm *start = localtime(&now);	// ��ʽת��
	m_start[0] = start->tm_hour;	// ʱ
	m_start[1] = start->tm_min;		// ��
	m_start[2] = start->tm_sec;		// ��
	cout << "��ʼʱ�䣺" << stime << endl;
}

// ����ѧϰ
void Item::stopStudy(){
	cout << "\n*** �ѽ�������ѧϰ ***" << endl;
	isStart = false;
	time_t now = time(0);		// ��ȡ��ǰʱ��
	char* stime = ctime(&now);	// תΪ�ַ���
	tm *stop = localtime(&now);	// ��ʽת��
	m_stop[0] = stop->tm_hour;		// ʱ
	m_stop[1] = stop->tm_min;		// ��
	m_stop[2] = stop->tm_sec;		// ��

	m_stopDate[0] = 1900 + stop->tm_year;	// ��
	m_stopDate[1] = 1 + stop->tm_mon;		// ��
	m_stopDate[2] = stop->tm_mday;			// ��

	cout << "����ʱ�䣺" << stime << endl;
}

// ��ʱ
void Item::countTime(){
	double h = 0, m = 0, s = 0;
	int ch = 0, cm = 0;	// ��λ��־
	s = m_stop[2] - m_start[2];
	// ��s<0��m��Ҫ��һλ
	if (s < 0) {
		s += 60;
		cm -= 1;
	}
	m = cm + m_stop[1] - m_start[1];
	// ��m<0��h��Ҫ��һλ
	if (m < 0) {
		m += 60;
		ch -= 1;
	}
	// �����ʼʱ��ͽ���ʱ����ͬһ��
	if (m_startDate[2] == m_stopDate[2]) 
		h = m_stop[0] - m_start[0] + ch;
	else  // ����
		h = 24 + m_stop[0] - m_start[0] + ch;

	// ��Сʱ����
	m_itemTime = h + (s / 60.0 + m) / 60.0;
	cout << "����ѧϰ��ʱ����" << m_itemTime << "h��";
	// ��ʱ�ּ���(ʡ����)
	int totalHM = h * 60 + m;
	int hour = totalHM / 60;
	int min = totalHM % 60;
	if (hour == 0)
		cout << min << "min��" << endl;
	else
		cout << hour << "h" << min << "min��" << endl;
	cout << endl;
		
}

// �޸�������
void Item::amendItemName(const string& name){
	m_itemName = name;
	// ÿ�޸�һ�������������¿�ʼ��ʱ��
	m_itemTime = 0.0;		
	time_t now = time(0);		// ��ȡ��ǰʱ��
	tm *date = localtime(&now);	// ��ʽת��
	m_startDate[0] = 1900 + date->tm_year;
	m_startDate[1] = 1 + date->tm_mon;
	m_startDate[2] = date->tm_mday;
}

// �浵
void storeItem(const Item& task){
	// ֻ��ִ����3���ܴ浵
	if (task.m_itemTime == 0) {
		cout << "��Ҫ��ѡ�����3���ܴ浵Ŷ~" << endl;
		cout << endl;
		return;
	}

	ofstream fout;
	fout.open("./task_record.txt", std::ios::app);	// iOS::app��ʾÿ��д�붼��׷�ӵ���β����ʾ��ģʽ��
	if (!fout.is_open()) {
		cout << "��ʧ�ܣ�����" << endl;
		return;
	}

	// ������������
	fout << setfill('0');
	fout << task.m_startDate[0] << "-" 
		<< setw(2) << task.m_startDate[1] << "-"
		<< setw(2) << task.m_startDate[2];
	fout << setw(10) << setiosflags(ios::left) << setfill(' ')<< " ";		// �������ø�ʽ���Ϊ�ո�,�����

	// ���û�����ڿ�ȣ�ֱ�ӱ��汾��ѧϰ��ʱ��
	if (task.m_startDate[2] == task.m_stopDate[2]) {
		fout << setw(20) << task.m_itemName;

		cout << task.m_itemTime << "h" << endl;

		fout << task.m_itemTime << "h";

		fout << setiosflags(ios::right) << setfill('0');
		fout << "��" 
			<< setw(2) << task.m_start[0] << ":" 
			<< setw(2) << task.m_start[1] << ":" 
			<< setw(2) << task.m_start[2] << " - ";
		fout << setw(2) << task.m_stop[0] << ":" 
			<< setw(2) << task.m_stop[1] << ":" 
			<< setw(2) << task.m_stop[2] << "��";
		fout << endl;
	}
	// ��������ڿ�ȣ���Ҫ�ٱ���һ���ڶ���ѧϰ��ʱ��
	else {
		// �ȱ�������ѧϰ���ƺ�ʱ�䣬ͬһ���ѧϰ��ǰ���и�#
		fout << "#" << setw(19) << task.m_itemName;

		double h = task.m_start[2] > 0 ? 24 - task.m_start[0] - 1 : 24 - task.m_start[0];
		double m = task.m_start[2] > 0 ? 60 - task.m_start[1] - 1 : 60 - task.m_start[1];
		double s = 60 - task.m_start[2];

		fout << h + (s / 60.0 + m) / 60.0 << "h";
		fout << setiosflags(ios::right) << setfill('0');
		fout << "��" 
			<< setw(2) << task.m_start[0] << ":" 
			<< setw(2) << task.m_start[1] << ":" 
			<< setw(2) << task.m_start[2] << " - ";
		fout << "00:00:00��";
		fout << endl;

		// �ٱ���ת�ӵ�ѧϰ���ڣ����ƺ�ʱ��
		fout << task.m_stopDate[0] << "-" 
			<< setw(2) << task.m_stopDate[1] << "-";
		fout << setw(2) << task.m_stopDate[2];

		fout << setw(10) << setiosflags(ios::left) << setfill(' ') << " ";
		fout << "#" << setw(19) << task.m_itemName;

		h = task.m_stop[0];
		m = task.m_stop[1];
		s = task.m_stop[2];

		fout << h + (s / 60.0 + m) / 60.0 << "h��00:00:00 - ";
		fout << setiosflags(ios::right) << setfill('0');
		fout << setw(2) << task.m_stop[0] << ":" 
			<< setw(2) << task.m_stop[1] << ":" 
			<< setw(2) << task.m_stop[2] << "��";
		fout << endl;
	}

	fout.close();
	cout << "����ɹ���\n" << endl;
}

// ����
void readItem(){
	ifstream fin;
	fin.open("task_record.txt", std::ios::in);
	if (!fin.is_open()) {
		cout << "��ʧ�ܣ�����" << endl;
		return;
	}string strLine;		// ����ȡ��һ�����ݱ�����strLine��
	while (getline(fin, strLine)) {
		cout << strLine << endl;
	}
	fin.close();
	cout << endl;
}


void showMenu(){
	cout << left;
	cout << "**************************" << endl;
	cout << "** 1.��ʼѧϰ           **" << endl;
	cout << "** 2.ֹͣѧϰ           **" << endl;
	cout << "** 3.��ʾ����ѧϰ��ʱ�� **" << endl;
	cout << "** 4.��ʾ����ѧϰ��ʱ�� **" << endl;
	cout << "** 5.��ʾ����ѧϰ��ʱ�� **" << endl;
	cout << "** 6.��ʾ����ѧϰ��ʱ�� **" << endl;
	cout << "** 7.���汾�μ�¼       **" << endl;
	cout << "** 8.����               **" << endl;
	cout << "** 0.�˳�               **" << endl;
	cout << "** c.��Ļˢ��           **" << endl;
	cout << "**************************" << endl;
	cout << endl;
}

void choiceMenu(char select, Item& task){
	switch (select){
	case '1': //1.��ʼѧϰ
		task.startStudy();
		break;
	case '2':	//2.ֹͣѧϰ
		task.stopStudy();
		break;
	case '3':	//3.��ʾ����ѧϰ��ʱ��
		task.countTime();
		break;
	case '4':	//4.��ʾ����ѧϰ��ʱ��
		break;
	case '5':	//5.��ʾ����ѧϰ��ʱ��
		break;
	case '6':	//6.��ʾ����ѧϰ��ʱ��
		break;
	case '7':	//7.���汾�μ�¼
		storeItem(task);
		break;
	case '8':	//8.����
		readItem();
		break;
	case '0':	//0.�˳�
		cout << "�ܰ�Ŷ~��־���ʤ����" << endl;
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
