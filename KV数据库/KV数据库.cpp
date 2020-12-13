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
#include"Minheap.h"
const int KVDB_OK = 0;
const int KVDB_INVALID_AOF_PATH = 1;
const int KVDB_INVALID_KEY = 2;
const int KVDB_NO_SPACE_LEFT_ON_DEVICES = 3;
using namespace std;
KVDBHandler::KVDBHandler(const std::string& db_file)
{
	purge_time = 0;
	log_Name = "KV数据库_log.txt";
	Warning_log = "KV数据库_warning_log.txt";
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
	Createlog(log_Name,name,Warning_log);
	Create_maps();
	Getsize_num = 0;
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
	int length = Get_size(fin);
	Header obj;
	if (!fin)
	{
		write_Error(Warning_log, "KVDB_INVALID_AOF_PATH");
	}
	else
	{
		while (fin.tellg() != length)
		{
			fin.read((char*)(&obj), sizeof(int) * 2);
			char *key = new char[obj.key_len + 1];
			char* value;
			if (obj.value_len == -1)
			{
				value = new char[1];
				memset(key, 0, obj.key_len + 1);
				memset(value, 0, 1);
				fin.read(key, obj.key_len);
			}
			else
			{
				value = new char[obj.value_len + 1];
				memset(key, 0, obj.key_len + 1);
				memset(value, 0, obj.value_len + 1);
				fin.read(key, obj.key_len);
				fin.read(value, obj.value_len);
			}
			if (obj.value_len == -1)
			{
				if (index_maps.find(key) != index_maps.end())
					index_maps.erase(key);
			}
			else
			{
				if (index_maps.empty())
				{
					index_maps.insert(pair<string, string>(key, value));
				}
				else
				{
					if (index_maps.find(key) == index_maps.end())
						index_maps.insert(pair<string, string>(key, value));
					else
					{
						it = index_maps.find(key);
						(*it).second = value;
					}
				}
			}
			delete[]value;
			delete[]key;
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
		Write(name, key, value,"Set");
		purge_time++;
		if (purge_time == 20)
		{
			purge();
			purge_time = 0;
		}
		modify_maps("Set",key,value);
		finish = clock();
		double  duration = (double)(finish - start);
		write_Duration(log_Name,duration);
		Write_filesize();
		return KVDB_OK;
	}
}
int KVDBHandler::Display()//打代码用来检验操作结果是否正确的
{
	ifstream fin(name.c_str(), ios::binary | ios::in);
	if (!fin)
	{
		write_Error(Warning_log, "KVDB_INVALID_AOF_PATH");
		return KVDB_INVALID_AOF_PATH;
	}
	int length = Get_size(fin);
	while (fin.tellg() != length)
	{
		Header obj;
		fin.read((char*)(&obj), sizeof(int) * 2);
		if (obj.value_len == -1)
		{
			char* key;
			key = new char[obj.key_len + 1];
			memset(key, 0, obj.key_len + 1);
			fin.read(key, obj.key_len);
			cout << "key值为:" << key << " value值为:" << endl;
			delete[]key;
		}
		else
		{
			char *key,*value;
			key = new char[obj.key_len + 1];
			value = new char[obj.value_len + 1];
			memset(key, 0, obj.key_len + 1);
			memset(value, 0, obj.value_len + 1);
			fin.read(key, obj.key_len);
			fin.read(value, obj.value_len);
			cout << "key值为:" << key << " value值为:" << value << endl;
			delete[]key;
			delete[]value;
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
	write_Time(log_Name);
	write_Operation(log_Name, "purge");
	map<string, string>::iterator it = index_maps.begin();
	ofstream fout(name.c_str(), ios::trunc);
	if (!index_maps.empty())
	{
		for (it = index_maps.begin(); it != index_maps.end(); it++)
		{
			this->Set((*it).first, (*it).second);
		}
	}
	write_Operation(log_Name, "purge_finish");
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
		write_Error(Warning_log,"KVDB_INVALID_KEY");
		return KVDB_INVALID_KEY;
	}
	if (index_maps.find(key) != index_maps.end())
	{
		value = index_maps[key];
	}
	clock_t finish_get = clock();
	double  duration = (double)(finish_get - start_get);
	write_Duration(log_Name, duration);
	Write_filesize();
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
	Header obj;
	string value;
	if (key.length() == 0)
	{
		write_Error(Warning_log, "KVDB_INVALID_KEY");
		return KVDB_INVALID_KEY;
	}
		
	else
	{
		this->Get(key, value);
		if (value.size() != 0)
		{
			Write(name, key, value, "Del");
			cout << "Key值为" << key << "对应的数据已被删除" << endl;
		}
		else
			cout << "文件中没有可删除的Key值" << endl;
		finish = clock();
		double  duration = (double)(finish - start);
		write_Duration(log_Name, duration);
		Write_filesize();
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
int KVDBHandler::expires(const std::string & key, int n)
{
	Dead D;
	time_t timep;
	struct tm* p;
	time(&timep);
	p = gmtime(&timep);
	D.key = key;
	D.time.year = p->tm_year + 1900;
	D.time.month = p->tm_mon + 1;
	D.time.day = p->tm_mday;
	D.time.hour = p->tm_hour + 8;
	D.time.minute = p->tm_min;
	D.time.second=p->tm_sec;
	add(D.time, n);
	minHeap.InsertNode(D);
	return 0;
}
int KVDBHandler::Get_size(ifstream &fin)
{
	fin.seekg(0, fin.end);
	int length = fin.tellg();
	fin.seekg(0, in.beg);
	return length;
}
void Write(const string& name, const string& key, const string& value,string order)//直接对磁盘进行写操作只有Set和Del，加if区分开即可
{
	ofstream out;
	out.open(name.c_str(), ios::app | ios::binary | ios::out);
	Header obj;
	obj.key_len = key.length();
	if (order == "Set")
		obj.value_len = value.length();
	else if (order == "Del")
		obj.value_len = -1;
	out.write((char*)(&obj), sizeof(int) * 2);
	out.write(key.c_str(), key.length());
	if(order=="Set")
		out.write(value.c_str(), value.length());
	out.close();
} 
void KVDBHandler::Write_filesize()
{
	if (Getsize_num != 30)
	{
		ifstream fin(name.c_str(), ios::binary | ios::in);
		int length = Get_size(fin);
		write_Filesize(log_Name, length);
		Getsize_num++;
		fin.close();
	}
	else
	{
		write_Filesize(log_Name, -1);
	}
}