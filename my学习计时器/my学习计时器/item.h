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

// 定义一个学习项目的类
class Item {
private:
	string m_itemName;		// 学习项目名称
	double m_itemTime;		// 本次项目所用时间
	int m_start[3];			// 记录开始学习时间，分别记录时分秒
	int m_stop[3];			// 记录结束学习时间
	int m_startDate[3];		// 记录开始学习的年月日
	int m_stopDate[3];		// 记录结束学习的年月日
	bool isStart;			// 用来标志是否开始学习

public:
	Item();
	Item(const string& name);
	~Item();

	// 成员函数
	void startStudy();		// 开始学习
	void stopStudy();		// 结束学习
	void countTime();		// 计时
	void amendItemName(const string& name);	// 修改任务名

	// 友元函数
	friend void showMenu();		// 显示菜单
	friend void choiceMenu(char select, Item& task);	// 选择菜单
	friend void storeItem(const Item& task);		// 存档
	friend void readItem();		// 读档
};
#endif // !ITEM_H_
