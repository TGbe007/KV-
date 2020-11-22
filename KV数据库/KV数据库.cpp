#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream> 
#include<cstring>
#include<io.h>
#include<stdio.h>
#include<string>
#include<map>
#include"KVDBHandler.h"
#include<time.h>
const int KVDB_OK = 0;
const int KVDB_INVALID_AOF_PATH = 1;
const int KVDB_INVALID_KEY = 2;
const int KVDB_NO_SPACE_LEFT_ON_DEVICES = 3;
using namespace std;
KVDBHandler::KVDBHandler(const std::string& db_file)
{
	purge_time = 0;
	log_Name = "KV数据库_log.txt";
	name = db_file + ".txt";
	if (_access(name.c_str(), 0) == -1)
	{
		ofstream fout(name.c_str(), ios::app);
		cout << "数据库不存在，已创建数据库" << name << endl;
		fout.close();
	}
	else
	{
		cout << "已打开数据库" << name << endl;
	}
	Createlog(log_Name,name);
	Create_maps();
}
void KVDBHandler::modify_maps(const string& order, const string& key, const string& value)
{
	map<string, string>::iterator it = index_maps.begin();
	if (order == "Set")
	{
		if (index_maps.find(key) == index_maps.end())
			index_maps.insert(pair<string, string>(key, value));
		else
		{
			it = index_maps.find(key);
			(*it).second = value;
		}
	}
	else if (order == "Del")
	{
		if (index_maps.find(key) != index_maps.end())
			index_maps.erase(key);
	}
}
void KVDBHandler::Create_maps()
{
	ifstream fin(name.c_str(), ios::binary | ios::in);
	map<string, string>::iterator it = index_maps.begin();
	fin.seekg(0, fin.end);
	int length = fin.tellg();
	fin.seekg(0, in.beg);
	Object obj;
	if (!fin)
	{
		write_Error(log_Name, "KVDB_INVALID_AOF_PATH");
	}
	else
	{
		while (fin.tellg() != length)
		{
			fin.read((char*)(&obj.len), sizeof(int) * 2);
			obj.key = new char[obj.len.key_len + 1];
			if (obj.len.value_len == -1)
			{
				obj.value = new char[1];
				memset(obj.key, 0, obj.len.key_len + 1);
				memset(obj.value, 0, 1);
				fin.read(obj.key, obj.len.key_len);
			}
			else
			{
				obj.value = new char[obj.len.value_len + 1];
				memset(obj.key, 0, obj.len.key_len + 1);
				memset(obj.value, 0, obj.len.value_len + 1);
				fin.read(obj.key, obj.len.key_len);
				fin.read(obj.value, obj.len.value_len);
			}
			if (obj.len.value_len == -1)
			{
				if (index_maps.find(obj.key) != index_maps.end())
					index_maps.erase(obj.key);
			}
			else
			{
				if (index_maps.empty())
				{
					index_maps.insert(pair<string, string>(obj.key, obj.value));
				}
				else
				{
					if (index_maps.find(obj.key) == index_maps.end())
						index_maps.insert(pair<string, string>(obj.key, obj.value));
					else
					{
						it = index_maps.find(obj.key);
						(*it).second = obj.value;
					}
				}
			}
			delete[]obj.value;
			delete[]obj.key;
		}
	}
}
int KVDBHandler::Set(const string& key, const string& value)
{
	write_Time(log_Name);
	write_Operation(log_Name,"Set");
	if (key.length() == 0)
	{
		write_Error(log_Name,"KVDB_INVALID_KEY");
		return KVDB_INVALID_KEY;
	}
	else
	{
		start=clock();
		out.open(name.c_str(), ios::app | ios::binary | ios::out);
		Object obj;
		obj.key = new char[key.length() + 1];
		obj.value = new char[value.length() + 1];
		obj.len.key_len = key.length();
		obj.len.value_len = value.length();
		strcpy(obj.key, key.c_str());
		strcpy(obj.value, value.c_str());
		out.write((char*)(&obj.len), sizeof(int) * 2);
		out.write(obj.key, key.length());
		out.write(obj.value, value.length());
		out.close();
		delete[]obj.value; //释放new申请的内存
		delete[]obj.key;
		purge_time++;
		if (purge_time == 20)
		{
			purge();
			purge_time = 0;
		}
		modify_maps("Set",key,value);
		ifstream fin(name.c_str(), ios::binary | ios::in);
		fin.seekg(0, fin.end);
		int length = fin.tellg();
		finish = clock();
		double  duration = (double)(finish - start);
		write_Duration(log_Name,duration);
		write_Filesize(log_Name,length);
		fin.close();
		return KVDB_OK;
	}
}
int KVDBHandler::Display()//打代码用来检验操作结果是否正确的
{
	ifstream fin(name.c_str(), ios::binary | ios::in);
	if (!fin)
	{
		return KVDB_INVALID_AOF_PATH;
	}
	fin.seekg(0, fin.end);
	int length = fin.tellg();
	fin.seekg(0, in.beg);
	Object obj;
	while (fin.tellg() != length)
	{
		fin.read((char*)(&obj.len), sizeof(int) * 2);
		if (obj.len.value_len == -1)
		{
			obj.key = new char[obj.len.key_len + 1];
			memset(obj.key, 0, obj.len.key_len + 1);
			fin.read(obj.key, obj.len.key_len);
			cout << "key值为:" << obj.key << " value值为:" << endl;
		}
		else
		{
			obj.key = new char[obj.len.key_len + 1];
			obj.value = new char[obj.len.value_len + 1];
			memset(obj.key, 0, obj.len.key_len + 1);
			memset(obj.value, 0, obj.len.value_len + 1);
			fin.read(obj.key, obj.len.key_len);
			fin.read(obj.value, obj.len.value_len);
			cout << "key值为:" << obj.key << " value值为:" << obj.value << endl;
		}
		if (obj.len.value_len == -1)
		{
			delete[]obj.key;
		}
		else
		{
			delete[]obj.value;
			delete[]obj.key;
		}
	}
	fin.close();
	return KVDB_OK;
}
void KVDBHandler::changefile(const std::string& db_file)
{
	purge(); //在每次切换文件之前，先整理好原文件
	name = db_file + ".txt";
	if (_access(name.c_str(), 0) == -1)
	{
		ofstream fout(name.c_str(), ios::app);
		cout << "数据库不存在，已创建新的数据库" << name << endl;
	}
	else
	{
		cout << "已成功更换数据库" << name << endl;
	}
	out.close();
	in.close();
	out.open(name.c_str(), ios::app | ios::binary | ios::out);
	out.close();
}
int KVDBHandler::purge()
{
	map<string, string>::iterator it = index_maps.begin();
	ofstream fout(name.c_str(), ios::trunc);
	if (!index_maps.empty())
	{
		for (it = index_maps.begin(); it != index_maps.end(); it++)
		{
			this->Set((*it).first, (*it).second);
		}
	}
	fout.close();
	return KVDB_OK;
}
int KVDBHandler::Get(const string& key, string& value)
{
	write_Time(log_Name);
	write_Operation(log_Name, "Get");
	clock_t start_get = clock();
	if (key.length() == 0)
	{
		write_Error(log_Name,"KVDB_INVALID_KEY");
		return KVDB_INVALID_KEY;
	}
	if (index_maps.find(key) != index_maps.end())
	{
		cout << value << endl;
		value = index_maps[key];
		cout << value << endl;
	}
	ifstream fin(name.c_str(), ios::binary | ios::in);
	fin.seekg(0, fin.end);
	int length = fin.tellg();
	fin.close();
	clock_t finish_get = clock();
	double  duration = (double)(finish_get - start_get);
	write_Duration(log_Name, duration);
	write_Filesize(log_Name, length);
	return KVDB_OK;
}
void KVDBHandler::Exit()
{
	out.close();
	in.close();
	cout << "数据库关闭成功，正在退出" << endl;
}
int KVDBHandler::Del(const std::string& key)
{
	write_Time(log_Name);
	write_Operation(log_Name, "Del");
	start = clock();
	out.open(name.c_str(), ios::app | ios::binary | ios::out);
	Object obj;
	string value;
	if (key.length() == 0)
	{
		write_Error(log_Name, "KVDB_INVALID_KEY");
		return KVDB_INVALID_KEY;
	}
		
	else
	{
		this->Get(key, value);
		if (value.size() != 0)
		{
			obj.key = new char[key.length() + 1];
			memset(obj.key, 0, key.length() + 1);
			strcpy(obj.key, key.c_str());
			obj.len.value_len = -1;
			obj.len.key_len = key.length();
			out.write((char*)(&obj.len), sizeof(int) * 2);
			out.write(obj.key, key.length());
			cout << "Key值为" << key << "对应的数据已被删除" << endl;
			delete[]obj.key;
		}
		else
			cout << "文件中没有可删除的Key值" << endl;

		out.close();
		ifstream fin(name.c_str(), ios::binary | ios::in);
		fin.seekg(0, fin.end);
		int length = fin.tellg();
		fin.close();
		finish = clock();
		double  duration = (double)(finish - start);
		write_Duration(log_Name, duration);
		write_Filesize(log_Name, length);
		purge_time++;
		if (purge_time == 20)
		{	
			purge();
			purge_time = 0;
		}
		modify_maps("Del", key, value);
		return KVDB_OK;
	}
}