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
struct Object //用来存储key值，value值，和相应长度的结构体
{
	char* value;
	char* key;
	Header len;
};

class KVDBHandler
{
private:
	ifstream in;
	ofstream out;
	string name;
	int time;//用来记录执行purge的时间
	clock_t start, finish;
	Log log;
public:
	KVDBHandler(const std::string& db_file);
	int Set(const string& key, const string& value);
	int Display();//打代码用来检验操作结果是否正确的
	int purge();
	void changefile(const std::string& db_file);
	int Get(const string& key, string& value)const;
	void Exit();
	int Del(const std::string& key);
};
