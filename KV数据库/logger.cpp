#include"logger.h"
#include<fstream>
void Createlog(const string& log_file, const string& file_name, const string& warning_log_file)
{
	if (_access(log_file.c_str(), 0) == -1)
	{
		ofstream fout(log_file.c_str(), ios::app);
		write_Time(log_file, fout);
		fout << " ����" << file_name << endl;
		fout.close();
	}
	if (_access(warning_log_file.c_str(), 0) == -1)
	{
		ofstream out(warning_log_file.c_str(), ios::app);
		write_Time(warning_log_file, out);
		out << "����" << file_name << endl;
		out.close();
	}
}
void write_Operation(const string& log_name, const string operation, const string key, const string value, ofstream& out)
{
	if (operation == "purge")
	{
		out << " ��ʼ����" << operation << "����" << endl;
	}
	else if (operation == "purge_finish")
		out << "purge���������" << endl;
	else
		out << " " << operation << "����";
	if (operation == "Set")
	{
		out << " д���KeyֵΪ:" << key << " " << " valueֵΪ: " << value;
	}
	else if (operation == "Get")
	{
		out << " ��ȡ��KeyֵΪ" << key << " ";
	}
	else if (operation == "Del")
	{
		out << " ɾ����KeyֵΪ" << key << " ";
	}
}
void write_Filesize(const string& log_name, int length, ofstream& out)
{
	if (length == -1)
		out << endl;
	else
		out << " ��ʱ�ļ��Ĵ�СΪ" << length << endl;
}
void write_Duration(const string& log_name, double duration, ofstream& out)
{
	out << " ���л���ʱ��" << duration << "ms";
}
void write_Time(const string& log_name, ofstream& out)
{
	time_t timep;
	struct tm* p;
	time(&timep);
	p = gmtime(&timep);
	out << p->tm_year + 1900 << "-" << p->tm_mon + 1 << "-" << p->tm_mday << " " << p->tm_hour + 8 << ":" << p->tm_min << ":" << p->tm_sec;
}
void write_Error(const string& log_name, const string& type, ofstream& out)
{
	out << "��������,����Ϊ" << type << endl;
}