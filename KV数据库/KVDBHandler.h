#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream> 
#include<cstring>
#include<io.h>
#include<stdio.h>
#include<string>
#include<map>

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
public:
	KVDBHandler(const std::string& db_file);
	void Set(const string& key, const string& value);
	int Display();//打代码用来检验操作结果是否正确的
	int purge();
	/*int purge()
	{
		ifstream fin(name.c_str(), ios::binary | ios::in);
		ofstream fout("ozq.txt", ios::app|ios::binary|ios::out);
		fin.seekg(0, fin.end);
		int length = fin.tellg();
		fin.seekg(0, in.beg);
		Object obj;
		if (!fin)
		{
			return 0;
		}
		else
		{
			while (fin.tellg() != length)
			{
				fin.read((char*)(&obj.len), sizeof(int) * 2);
				obj.key = new char[obj.len.key_len + 1];
				obj.value = new char[obj.len.value_len + 1];
				memset(obj.key, 0, obj.len.key_len + 1);
				memset(obj.value, 0, obj.len.value_len + 1);
				fin.read(obj.key, obj.len.key_len);
				fin.read(obj.value, obj.len.value_len);
				string value = obj.value;
				string key = obj.key;
				Get(obj.key, value);
				if (strcmp(value.c_str(),obj.value) == 0)
				{
					fout.write((char*)(&obj.len), sizeof(int) * 2);
					fout.write(obj.key, key.length());
					fout.write(obj.value, value.length());
				}
				delete[]obj.key;
				delete[]obj.value;
			}
			fin.close();
			fout.close();
			remove(name.c_str());
			rename("ozq.txt", name.c_str());
		}
		return 1;
	}*/
	void changefile(const std::string& db_file);
	void Get(const string& key, string& value)const;
	void Exit();
	void Del(const std::string& key);
};
