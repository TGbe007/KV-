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
	Warning_log = "KV数据库_warning_log.txt";
	name = db_file + ".txt";
	expires_filename = db_file + "_expires.txt";
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
	if (_access(expires_filename.c_str(), 0) == -1)
	{
		ofstream fout(expires_filename.c_str(), ios::app);
		fout.close();
	}
	Createlog(log_Name,name,Warning_log);	
	Expires_Create();
	Create_hashmaps();
	Getsize_num = 0;
}
void KVDBHandler::modify_maps(const string& order, const string& key, const string& value,const int& offset)
{
	if (order == "Set")
	{
		hash_map.add(key, offset);
	}
	else if (order == "Del")
	{
		hash_map.del(key);
	}
}
void KVDBHandler::modify_time_maps( const string& key,const int&_time,const string&order)
{
	map<string, int>::iterator it = Living_time.begin();
	if (order == "Set")
	{
		if (Living_time.find(key) == Living_time.end())
			Living_time.insert(pair<string, int>(key, _time));
		else
		{
			it = Living_time.find(key);
			(*it).second = _time;
		}
	}
	else if (order == "Del")
	{
		if (Living_time.find(key) != Living_time.end())
			Living_time.erase(key);
	}
}
void KVDBHandler::Create_hashmaps()
{
	ifstream fin(name.c_str(), ios::binary | ios::in);
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
			int offset = fin.tellg();
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
				if (hash_map.get(key) != -1)
					hash_map.del(key);
			}
			else
			{
				hash_map.add(key,offset);
			}
			delete[]value;
			delete[]key;
		}
	}
}
void KVDBHandler::Expires_Create()
{
	ifstream fin(expires_filename.c_str(), ios::binary | ios::in);
	map<string, int>::iterator it = Living_time.begin();
	int length = Get_size(fin);
	int key_length,_time;
	time_t timep;
	time(&timep);
	while (fin.tellg() != length)
	{
		fin.read((char*)(&key_length), sizeof(int));
		char* key = new char[key_length + 1];
		memset(key, 0, key_length + 1);
		fin.read(key, key_length);
		fin.read((char*)(&_time), sizeof(int));
		if (_time != -1)
		{
			string _key;//用来把char*转化为string
			for (int i = 0; i < strlen(key); i++)
				_key.push_back(key[i]);
			modify_time_maps(_key, _time, "Set");
		}
		else
		{
			if (Living_time.find(key) != Living_time.end())
				Living_time.erase(key);
		}//至此完成了记录过期时间的Map表的创建
		delete[]key;
	}
	fin.close();
	//开始对Expires文件进行整理
	ofstream fout(expires_filename.c_str(), ios::trunc);
	fout.close();
	if (!Living_time.empty())
	{
		out.open(name.c_str(), ios::app | ios::binary | ios::out);
		for (it = Living_time.begin(); it != Living_time.end();)
		{
			if ((*it).second < timep)//先判断是否过期，如果过期了就在原文件先删除，同时在map表里删除
			{
				string key = (*it).first;
				Write(name, (*it).first, "0", "Del",out);
				it++;//为防止迭代器被删除，先把里面的key赋值给局部变量key，然后先让it++，在进行erase操作
				Living_time.erase(key);
			}
			else
			{
				Expires_Write((*it).first, (*it).second);//以下三行，同时整理了文件以及创建了优先队列
				Survival_Time S((*it).first, (*it).second);
				Que.push(S);
				it++;
			}
			
		}
		out.close();
	}
}
int KVDBHandler::Set(const string& key, const string& value)
{
	write_Time(log_Name);
	write_Operation(log_Name,"Set",key,value);
	if (key.length() == 0)
	{
		write_Error(log_Name,"KVDB_INVALID_KEY");
		return KVDB_INVALID_KEY;
	}
	else
	{
		start=clock();
		out.open(name.c_str(), ios::app | ios::binary | ios::out);
		int length=Write(name, key, value,"Set",out);
		out.close();
		modify_maps("Set",key,value,length);
		if (Living_time.find(key) != Living_time.end())
		{
			modify_time_maps(key, 0, "Del");//修改记录时间的map
			Expires_Write(key, -1);//修改文件
		}
		//Lc.Put(key, value,hash_map);//LRUCache
		purge_time++;
		if (purge_time == 3000)
		{
			purge();
			purge_time = 0;
		}
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
	write_Operation(log_Name, "purge","0","0");
	int* offset_order = new int[100000];
	memset(offset_order, -1, sizeof(int)*100000);
	hash_map.Get_offset_order(offset_order);
	ifstream fin(name.c_str(), ios::binary | ios::in);
	ofstream fout("temporary.txt", ios::app|ios::binary|ios::out);
	int i = 0;
	while (offset_order[i] != -1)
	{
		Header obj;
		fin.seekg(offset_order[i], ios::beg);
		fin.read((char*)(&obj), sizeof(int) * 2);
		char* key, * value;
		key = new char[obj.key_len + 1];
		value = new char[obj.value_len + 1];
		memset(key, 0, obj.key_len + 1);
		memset(value, 0, obj.value_len + 1);
		fin.read(key, obj.key_len);
		fin.read(value, obj.value_len);
		Write("temporary.txt", key, value, "Set",fout);
		/*cout << key << " " << value << endl;*/
		delete[]key;
		delete[]value;
		i++;
	}
	fin.close();
	fout.close();
	remove(name.c_str());
	rename("temporary.txt", name.c_str());
	write_Operation(log_Name, "purge_finish","0","0");
	delete[]offset_order;
	Create_hashmaps();
	return KVDB_OK;
}
int KVDBHandler::Get(const string& key, string& value)
{
	write_Time(log_Name);
	write_Operation(log_Name, "Get",key,"0");
	clock_t start_get = clock();
	Expires_Del();
	//int state=Lc.Get(key, value,hash_map);//调用LRUCache,判断是否存在于其中
	if (key.length() == 0)
	{
		write_Error(Warning_log,"KVDB_INVALID_KEY");
		return KVDB_INVALID_KEY;
	}
	int offset = hash_map.get(key);
	if (offset != -1)
	{
		ifstream fin(name.c_str(), ios::binary | ios::in);
		fin.seekg(offset, fin.beg);
		Header obj;
		fin.read((char*)(&obj), sizeof(int) * 2);
		fin.seekg(obj.key_len, fin.cur);
		char* _value = new char[obj.value_len + 1];
		memset(_value, 0, obj.value_len + 1);
		fin.read(_value, obj.value_len);
		for (int i = 0; i < obj.value_len; i++)
			value.push_back(_value[i]);
		delete[]_value;
		fin.close();
	}
	//当state==1，value值已改变，写完日志就可以退出，state==2，key不存在;
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
	write_Operation(log_Name, "Del",key,"0");
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
			out.open(name.c_str(), ios::app | ios::binary | ios::out);
			Write(name, key, value, "Del",out);
			out.close();
			cout << "Key值为" << key << "对应的数据已被删除" << endl;
			modify_maps("Del", key, value,0);
			//hash_map.SetNode(key, &LRUNode("0","0"), "erase");
			if (Living_time.find(key) != Living_time.end())
			{
				modify_time_maps(key, 0, "Del");//修改记录时间的map
				Expires_Write(key, -1);//修改文件
			}
		}
		else
			cout << "文件中没有可删除的Key值" << endl;
		finish = clock();
		double  duration = (double)(finish - start);
		write_Duration(log_Name, duration);
		Write_filesize();
		purge_time++;
	    if (purge_time == 3000)
		{	
			purge();
			purge_time = 0;
		}
		return KVDB_OK;
	}

}
int KVDBHandler::expires(const std::string & key, int n)
{
	if (key.length() == 0)
	{
		write_Error(log_Name, "KVDB_INVALID_KEY");
		return KVDB_INVALID_KEY;
	}
	time_t timep;
	time(&timep);
	int survival = timep + n;
	string value;
	this->Get(key, value);
	if (value.length() == 0)
	{
		return KVDB_INVALID_KEY;
	}
	Survival_Time S(key, survival);
	Expires_Write(key, survival);
	modify_time_maps(key, survival, "Set");
	Que.push(S);
	return KVDB_OK;
}
int KVDBHandler::Get_size(ifstream &fin)
{
	fin.seekg(0, fin.end);
	int length = fin.tellg();
	fin.seekg(0, fin.beg);
	return length;
}
void KVDBHandler::Expires_Write(const string& key, const int& _time)//用于对expires_file文件进行写入
{
	out.open(expires_filename.c_str(), ios::app | ios::binary | ios::out);
	int key_len = key.length();
	out.write((char*)(&key_len), sizeof(int));
	out.write(key.c_str(), key.length());
	out.write((char*)(&_time), sizeof(int));
	out.close();
}
int KVDBHandler::Expires_Get(const string& key,int offset)
{
	ifstream fin(name.c_str(), ios::binary | ios::in);
	int length = Get_size(fin);
	fin.seekg(offset, ios::beg);
	int key_length;
	int _time;
	while (fin.tellg() != length)
	{
		fin.read((char*)(&key_length), sizeof(int));
		char* _key = new char[key_length + 1];
		memset(_key, 0, key_length + 1);
		fin.read(_key, key_length);
		fin.read((char*)(&_time), sizeof(int));
		if (strcmp(_key, key.c_str()) == 0)
		{
			return _time;
		}
		delete[]_key;
	}
	fin.close();
	return 1;
}
int Write(const string& name, const string& key, const string& value,string order,ofstream &out)//直接对磁盘进行写操作只有Set和Del，加if区分开即可
{
	ifstream fin(name.c_str(), ios::binary | ios::in);
	fin.seekg(0, fin.end);
	int length = fin.tellg();//获取当前的位置
	fin.close();
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
	return length;
} 
void KVDBHandler::Expires_Del()
{
	time_t timep;
	time(&timep);
	map<string, int>::iterator it = Living_time.begin();
	out.open(name.c_str(), ios::app | ios::binary | ios::out);
	while (!Que.empty()&&Que.top()._time < timep)
	{
		if (Living_time.find(Que.top().key) != Living_time.end())
		{
			it = Living_time.find(Que.top().key);
			if ((*it).second == Que.top()._time)
			{
				Write(name, Que.top().key, "0", "Del",out);//在原文件中删除
				hash_map.del(Que.top().key);//在Hash表中删除
				Living_time.erase(Que.top().key);
				Expires_Write(Que.top().key, -1);
			}
		}
		Que.pop();//从文件中Pop掉
	}
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