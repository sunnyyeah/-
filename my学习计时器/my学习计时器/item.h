#pragma once
#ifndef ITEM_H_
#define ITEM_H_

#include<iostream>
#include<string>
#include<vector>
#include<iomanip>
#include<ctime>
#include<fstream>
using namespace std;

// ����һ��ѧϰ��Ŀ����
class Item {
private:
	string m_itemName;		// ѧϰ��Ŀ����
	double m_itemTime;		// ������Ŀ����ʱ��
	int m_start[3];			// ��¼��ʼѧϰʱ�䣬�ֱ��¼ʱ����
	int m_stop[3];			// ��¼����ѧϰʱ��
	int m_startDate[3];		// ��¼��ʼѧϰ��������
	int m_stopDate[3];		// ��¼����ѧϰ��������
	bool isStart;			// ������־�Ƿ�ʼѧϰ

public:
	Item();
	Item(const string& name);
	~Item();

	// ��Ա����
	void startStudy();		// ��ʼѧϰ
	void stopStudy();		// ����ѧϰ
	void countTime();		// ��ʱ
	void amendItemName(const string& name);	// �޸�������

	// ��Ԫ����
	friend void showMenu();		// ��ʾ�˵�
	friend void choiceMenu(char select, Item& task);	// ѡ��˵�
	friend void storeItem(const Item& task);		// �浵
	friend void readItem();		// ����
};
#endif // !ITEM_H_
