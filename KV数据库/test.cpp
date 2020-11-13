#pragma once
#include<stdio.h>
#include<ctime>
#include"KVDBHandler.h"

class KVDBtest
{
private:
	string* key;
	string* value;
	KVDBHandler* handler;
	int len;
	int opcnt;
public:
	KVDBtest()
	{
		handler = new KVDBHandler("test");
		srand((unsigned)time(NULL));
		key = new string[100];
		value = new string[100];
		len = 0;
		opcnt = 0;
	}
	void randomString(string& p)//生成随机字符串
	{
		p.clear();
		int len = rand() % 20 + 1;
		for (int j = 0; j < len; j++)
		{
			int a;
			a = rand() % 3;
			if (a == 0)
			{
				p.push_back(rand() % ('Z' - 'A' + 1) + 'A');
			}
			else if (a == 1)
			{
				p.push_back(rand() % ('z' - 'a' + 1) + 'a');
			}
			else if (a == 2)
			{
				p.push_back(rand() % ('9' - '0' + 1) + '0');
			}
		}
	}
	void test()
	{
		int op = 0;
		while (opcnt < 300 || len < 100)
		{
			if (op == 0)//set
			{
				if (len < 80)
				{
					randomString(key[len]);
				}
				else
				{
					key[len] = key[rand() % len];
				}
				randomString(value[len]);
				printf("set:%s %s\n", key[len].c_str(), value[len].c_str());
				printf("写入第%d个数据\n", ++len);
				handler->Set(key[len - 1], value[len - 1]);
			}
			else if (op == 1)//get
			{
				string testvalue;
				int index = rand() % len;
				handler->Get(key[index], testvalue);//获取数据库中对应的value并赋值给testvalue
				string value_;
				for (int j = 0; j < len; j++)//在已生成的所有数据中找出最后一个对应的value并赋值给value_
				{
					if (key[j] == key[index])
					{
						value_ = value[j];
					}
				}
				if (!(testvalue == value_))//数据库的返回值testvalue与实际对应的value值不符
				{
					printf("错误：key值为%s\nvalue值应为%s\n实际为%s\n", key[index].c_str(), value_.c_str(), testvalue.c_str());
					printf("index=%d\nlen=%d\n", index, len);
					system("pause");
					return;
				}
				if (value_.length() != 0)
				{
					printf("value值为%s\n", testvalue.c_str());
				}
				else
				{
					printf("找不到key值为%s的value值\n", key[index].c_str());
				}
			}
			else if (op == 2)
			{
				int index = rand() % len;
				string value_;
				handler->Get(key[index], value_);
				if (value_.length() != 0)//判断删除是否有效,若有效则把所有对应的value值清空
				{
					for (int i = 0; i < len; i++)
					{
						if (key[i] == key[index])
						{
							value[i].clear();
						}
					}
					printf("删除第%d个数据\n", index + 1);
					handler->Del(key[index]);
				}
				else
				{
					op = randomop();
					continue;
				}
			}
			printf("操作次数：%d\n\n", ++opcnt);
			op = randomop();
		}
		printf("测试成功\n");
	}
	int randomop()
	{
		if (len < 20)
		{
			return 0;
		}
		else if (len < 80)
		{
			return rand() % 3;
		}
		else if (len < 100)
		{
			int result = rand() % 2;
			return result == 0 ? result : result + 1;
		}
		else
		{
			return 1;
		}
	}
	~KVDBtest()
	{
		delete[] key;
		delete[] value;
		delete handler;
	}
};
/*int main()
{
	KVDBtest test;
	test.test();
}*/