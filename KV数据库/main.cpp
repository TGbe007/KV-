/*#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream> 
#include<cstring>
#include<io.h>
#include<stdio.h>
#include<string>
#include<map>
#include"KVDBHandler.h"
#include"logger.h"
using namespace std;
int main()
{
	cout << "请输入文件名" << endl;
	string file_name, key, value;
	getline(cin, file_name);
	KVDBHandler database(file_name);

	while (1)
	{
		string order;
		cout << "- - - - - - - - - -" << endl << "进行写操作请输入：Set" << endl << "进行读操作请输入：Get" << endl << "进行删除操作请输入：Del" << endl << "更换文件请输入:Change_file" << endl;
		cout << "遍历数据库元素请输入：Display" <<endl<<"给Key值设置生存周期请输入：Expires"<< endl << "如果要整理文件请输入:Purge" << endl << "退出数据库请输入：Exit" << endl << "- - - - - - - - - -" << endl << "请输入指令：";
		getline(cin, order);
	if (order == "Set")
		{
			cout << "请输入要插入的Key值:";
			getline(cin, key);
			cout << "请输入要插入的Value值:";
			getline(cin, value);
			int state=database.Set(key, value);
			if (state == 0)
				cout << "写入成功，请输入下一个指令" << endl;
			else if (state == 2)
				cout << "写入失败，key值不能为空" << endl;
		}
		else if (order == "Get")
		{
			string key;
			string value;
			cout << "请输入所寻找的Key值:";
			getline(cin, key);
			int state=database.Get(key, value);
			if (state == 2)
			{
				cout << "读取失败，Key值不能为空" << endl;
			}
			else if(state==0)
			{
				if (value.size() != 0)
					cout << "目标key对应value值为" << value << endl;
				else
					cout << "在数据库查不到对应的key值" << endl;
			}
			else if (state == 1)
			{
				cout << "读取失败，寻找不到文件" << endl;
			}
			
		}
		else if (order == "Change_file")
		{
			cout << "请输入你要更换的文件名" << endl;
			getline(cin, file_name);
			database.changefile(file_name);
		}
		else if (order == "Display")
		{
			int state = database.Display();
			if (state == 0)
				cout << "已经输出全部数据了" << endl;
			else
			{
				cout << "文件不存在" << endl;
			}
		}
		else if (order == "Exit")
		{
			database.Exit();
			break;
		}
		else if (order == "Del")
		{
			cout << "请输入你要删除的Key值:" ;
			string key;
			getline(cin, key);
			int state=database.Del(key);
			if (state == 2)
			{
				cout << "删除失败，Key值不能为空" << endl;
			}
		}
		else if (order == "Expires")
		{
			cout << "请输入你要设置生存时间的Key值:";
			string key;
			getline(cin, key);
			int n;
			cout << "请输入你要设置的秒数:";
			cin >> n;
			getchar();
			int state = database.expires(key, n);
			if (state == 0)
				cout << "设置成功" << endl;
			else if (state == 2)
				cout << "没有相应的Key值" << endl;
		}
		else if (order == "Purge")
		{
			int state = database.purge();
			if (state == 0)
			{
				cout << "文件已经整理完毕" << endl;
			}
			else if(state==1)
			{
				cout << "文件不存在" << endl;
			}
		}
		else
		{
			cout << "输入操作指令有误，请重新输入" << endl;
		}
		system("pause");
		system("cls");
	}
	return 0;
}*/