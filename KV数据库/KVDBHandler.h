#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream> 
#include<cstring>
#include<io.h>
#include<stdio.h>
#include<string>
#include<map>
#include"logger.h"
#include"HashMap.h"
#include<queue>
using namespace std;
struct Header //���������洢key��value���ȵĽṹ��
{
	int key_len;
	int value_len;
};
struct Survival_Time
{
	int _time;
	string key;
	Survival_Time(string K, int t)
	{
		key = K;
		_time = t;
	}
};
struct cmp
{
	bool operator()(Survival_Time a, Survival_Time b)
	{
		return a._time > b._time;
	}
};
class KVDBHandler
{
private:
	//LRUCache Lc;
	ifstream in;
	ofstream out;
	string name;
	string expires_filename;
	int purge_time;//������¼ִ��purge��ʱ��
	clock_t start, finish;
	string log_Name;
	string Warning_log;
	int Getsize_num;
	HashMap hash_map;
	priority_queue < Survival_Time, vector<Survival_Time>, cmp>Que;
	map<string, int> Living_time;//������¼����ʱ��
public:
	KVDBHandler(const std::string& db_file);
	void Create_hashmaps();
	int Set(const string& key, const string& value);
	int Display();//��������������������Ƿ���ȷ��
	int purge();
	void changefile(const std::string& db_file);
	int Get(const string& key, string& value);
	void Exit();
	int Del(const std::string& key);
	void modify_maps(const string&order,const string&key,const string&value,const int& offset);
	int Get_size(ifstream &fin);
	void Write_filesize();
	int expires(const std::string& key, int n);
	void modify_time_maps(const string& key, const int &_time,const string&order);
	void Expires_Create();//����time_map,Ȼ��������map��ˢ���ļ���ͬʱ�������map���������ȶ���
	void Expires_Write(const string&key,const int&_time);//��expires�ļ�����д��
	int Expires_Get(const string& key, int offset);//��Ҫ������ʼ��ʱ�����ж�Key�Ƿ���Ĺ��ڣ��Դ����ж��Ƿ�Ҫ��ԭ�ļ���ɾ��
	void Expires_Del();//ɾ�����ļ��й��ڵ�Ԫ��
};
int Write(const string& name, const string& key, const string& value,string order,ofstream &out);

