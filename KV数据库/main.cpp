#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream> 
#include<cstring>
#include<io.h>
#include<stdio.h>
#include<string>
#include<map>
#include"KVDBHandler.h"
using namespace std;
/*int main()
{
	cout << "�������ļ���" << endl;
	string file_name, key, value;
	getline(cin, file_name);
	KVDBHandler database(file_name);

	while (1)
	{
		string order;
		cout << "- - - - - - - - - -" << endl << "����д���������룺Set" << endl << "���ж����������룺Get" << endl << "����ɾ�����������룺Del" << endl << "�����ļ�������:Change_file" << endl;
		cout << "�������ݿ�Ԫ�������룺Display" << endl << "���Ҫ�����ļ�������:Purge" << endl << "�˳����ݿ������룺Exit" << endl << "- - - - - - - - - -" << endl << "������ָ�";
		getline(cin, order);
		if (order == "Set")
		{
			cout << "������Ҫ�����Keyֵ:";
			getline(cin, key);
			cout << "������Ҫ�����Valueֵ:";
			getline(cin, value);
			database.Set(key, value);
			cout << "д��ɹ�����������һ��ָ��" << endl;
		}
		else if (order == "Get")
		{
			string key;
			string value;
			cout << "��������Ѱ�ҵ�Keyֵ";
			getline(cin, key);
			database.Get(key, value);
			if (value.size() != 0)
				cout << "Ŀ��key��ӦvalueֵΪ" << value << endl;
			else
				cout << "�����ݿ�鲻����Ӧ��keyֵ" << endl;
		}
		else if (order == "Change_file")
		{
			cout << "��������Ҫ�������ļ���" << endl;
			getline(cin, file_name);
			database.changefile(file_name);
		}
		else if (order == "Display")
		{
			int result = database.Display();
			if (result == 0)
				cout << "�ļ�Ϊ��" << endl;
			else
			{
				cout << "�Ѿ����ȫ��������" << endl;
			}
		}
		else if (order == "Exit")
		{
			database.Exit();
			break;
		}
		else if (order == "Del")
		{
			cout << "��������Ҫɾ����Keyֵ" << endl;
			string key;
			getline(cin, key);
			database.Del(key);
		}
		else if (order == "Purge")
		{
			int state = database.purge();
			if (state == 1)
			{
				cout << "�ļ��Ѿ��������" << endl;
			}
			else
			{
				cout << "�ļ������ڻ�����ʧ��" << endl;
			}
		}
		else
		{
			cout << "�������ָ����������������" << endl;
		}
		system("pause");
		system("cls");
	}
	return 0;
}*/
