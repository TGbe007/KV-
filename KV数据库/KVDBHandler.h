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
struct Header //定义用来存储key，value长度的结构体
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
	ifstream in;
	ofstream out;
	string name;
	string expires_filename;
	int purge_time;//用来记录执行purge的时间
	clock_t start, finish;
	string log_Name;
	string Warning_log;
	int Getsize_num;
	HashMap hash_map;//hash表
	priority_queue < Survival_Time, vector<Survival_Time>, cmp>Que;//优先队列
	map<string, int> Living_time;//用来记录生存时间
public:
	KVDBHandler(const std::string& db_file);
	void Create_hashmaps();//按照原文件创建hash表
	int Set(const string& key, const string& value);
	int Display();//打代码用来检验操作结果是否正确的
	int purge();//整理文件
	void changefile(const std::string& db_file);
	int Get(const string& key, string& value);//获取元素
	void Exit();//退出文件
	int Del(const std::string& key);//删除元素
	void modify_maps(const string& order, const string& key, const string& value, const int& offset);//修改hash表
	int Get_size(ifstream& fin);//获取文件当前大小
	void Write_filesize(ofstream& out);//在日志中写文件大小
	int expires(const std::string& key, int n);//expires操作，设置过期时间
	void modify_time_maps(const string& key, const int& _time, const string& order);
	void Expires_Create();//创建time_map,然后根据这个map来刷新文件，同时根据这个map来创建优先队列
	void Expires_Write(const string& key, const int& _time);//对expires文件进行写入
	void Expires_Del();//删除掉文件中过期的元素
};
int Write(const string& name, const string& key, const string& value, string order, ofstream& out);//写原文件的操作