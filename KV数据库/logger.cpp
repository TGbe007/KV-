#include"logger.h"
#include<fstream>
void Createlog(const string& log_file,const string &file_name)
{
	if (_access(log_file.c_str(), 0) == -1)
	{
		ofstream fout(log_file.c_str(), ios::app);
		write_Time(log_file);
		fout << " ����" << file_name << endl;
		fout.close();
	}
}
void write_Operation(const string& log_name, const string operation)
{
	ofstream out;
	out.open(log_name.c_str(), ios::app | ios::out);
	out << " " << operation << "����";
	out.close();
}
void write_Filesize(const string &log_name,int length)
{
	ofstream out;
	out.open(log_name.c_str(), ios::app | ios::out);
	out << " ��ʱ�ļ��Ĵ�СΪ" << length<<endl;
	out.close();
}
void write_Duration(const string& log_name, double duration)
{
	ofstream out;
	out.open(log_name.c_str(), ios::app | ios::out);
	out << " ���л���ʱ��" << duration  << "ms";
	out.close();
}
void write_Time(const string& log_name)
{
	ofstream out;
	out.open( log_name.c_str(),ios::app | ios::out);
	time_t timep;
	struct tm* p;
	time(&timep);
	p = gmtime(&timep);
	out << p->tm_year + 1900 << "-" << p->tm_mon + 1 << "-" << p->tm_mday << " " << p->tm_hour + 8 << ":" << p->tm_min << ":" << p->tm_sec;
	out.close();
}
void write_Error(const string &log_name,const string &type)
{
	ofstream out;
	out.open(log_name.c_str(), ios::app | ios::out);
	out << "��������,����Ϊ" << type << endl;
	out.close();
}