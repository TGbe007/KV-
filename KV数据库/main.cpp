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
	cout << "�������ļ���" << endl;
	string file_name, key, value;
	getline(cin, file_name);
	KVDBHandler database(file_name);

	while (1)
	{
		string order;
		cout << "- - - - - - - - - -" << endl << "����д���������룺Set" << endl << "���ж����������룺Get" << endl << "����ɾ�����������룺Del" << endl << "�����ļ�������:Change_file" << endl;
		cout << "�������ݿ�Ԫ�������룺Display" <<endl<<"��Keyֵ�����������������룺Expires"<< endl << "���Ҫ�����ļ�������:Purge" << endl << "�˳����ݿ������룺Exit" << endl << "- - - - - - - - - -" << endl << "������ָ�";
		getline(cin, order);
	if (order == "Set")
		{
			cout << "������Ҫ�����Keyֵ:";
			getline(cin, key);
			cout << "������Ҫ�����Valueֵ:";
			getline(cin, value);
			int state=database.Set(key, value);
			if (state == 0)
				cout << "д��ɹ�����������һ��ָ��" << endl;
			else if (state == 2)
				cout << "д��ʧ�ܣ�keyֵ����Ϊ��" << endl;
		}
		else if (order == "Get")
		{
			string key;
			string value;
			cout << "��������Ѱ�ҵ�Keyֵ:";
			getline(cin, key);
			int state=database.Get(key, value);
			if (state == 2)
			{
				cout << "��ȡʧ�ܣ�Keyֵ����Ϊ��" << endl;
			}
			else if(state==0)
			{
				if (value.size() != 0)
					cout << "Ŀ��key��ӦvalueֵΪ" << value << endl;
				else
					cout << "�����ݿ�鲻����Ӧ��keyֵ" << endl;
			}
			else if (state == 1)
			{
				cout << "��ȡʧ�ܣ�Ѱ�Ҳ����ļ�" << endl;
			}
			
		}
		else if (order == "Change_file")
		{
			cout << "��������Ҫ�������ļ���" << endl;
			getline(cin, file_name);
			database.changefile(file_name);
		}
		else if (order == "Display")
		{
			int state = database.Display();
			if (state == 0)
				cout << "�Ѿ����ȫ��������" << endl;
			else
			{
				cout << "�ļ�������" << endl;
			}
		}
		else if (order == "Exit")
		{
			database.Exit();
			break;
		}
		else if (order == "Del")
		{
			cout << "��������Ҫɾ����Keyֵ:" ;
			string key;
			getline(cin, key);
			int state=database.Del(key);
			if (state == 2)
			{
				cout << "ɾ��ʧ�ܣ�Keyֵ����Ϊ��" << endl;
			}
		}
		else if (order == "Expires")
		{
			cout << "��������Ҫ��������ʱ���Keyֵ:";
			string key;
			getline(cin, key);
			int n;
			cout << "��������Ҫ���õ�����:";
			cin >> n;
			getchar();
			int state = database.expires(key, n);
			if (state == 0)
				cout << "���óɹ�" << endl;
			else if (state == 2)
				cout << "û����Ӧ��Keyֵ" << endl;
		}
		else if (order == "Purge")
		{
			int state = database.purge();
			if (state == 0)
			{
				cout << "�ļ��Ѿ��������" << endl;
			}
			else if(state==1)
			{
				cout << "�ļ�������" << endl;
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