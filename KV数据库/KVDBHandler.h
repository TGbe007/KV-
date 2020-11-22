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
struct Header //���������洢key��value���ȵĽṹ��
{
	int key_len;
	int value_len;
};
struct Object //�����洢keyֵ��valueֵ������Ӧ���ȵĽṹ��
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
	int purge_time;//������¼ִ��purge��ʱ��
	clock_t start, finish;
	string log_Name;
	map<string, string>index_maps;

public:
	KVDBHandler(const std::string& db_file);
	void Create_maps();
	int Set(const string& key, const string& value);
	int Display();//��������������������Ƿ���ȷ��
	int purge();
	void changefile(const std::string& db_file);
	int Get(const string& key, string& value);
	void Exit();
	int Del(const std::string& key);
	void modify_maps(const string&order,const string&key,const string&value);
};
