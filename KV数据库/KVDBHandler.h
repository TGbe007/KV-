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

using namespace std;
struct Header //定义用来存储key，value长度的结构体
{
	int key_len;
	int value_len;
};

class KVDBHandler
{
private:
	ifstream in;
	ofstream out;
	string name;
	int purge_time;//用来记录执行purge的时间
	clock_t start, finish;
	string log_Name;
	string Warning_log;
	map<string, string>index_maps;
	int Getsize_num;

public:
	KVDBHandler(const std::string& db_file);
	void Create_maps();
	int Set(const string& key, const string& value);
	int Display();//打代码用来检验操作结果是否正确的
	int purge();
	void changefile(const std::string& db_file);
	int Get(const string& key, string& value);
	void Exit();
	int Del(const std::string& key);
	void modify_maps(const string&order,const string&key,const string&value);
	int Get_size(ifstream &fin);
	void Write_filesize();
};
void Write(const string& name, const string& key, const string& value,string order);

