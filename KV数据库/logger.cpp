#include"logger.h"
#include<fstream>
void Createlog(const string& log_file,const string &file_name,const string &warning_log_file)
{
	if (_access(log_file.c_str(), 0) == -1)
	{
		ofstream fout(log_file.c_str(), ios::app);
		write_Time(log_file);
		fout << " 打开了" << file_name << endl;
		fout.close();
	}
	if (_access(warning_log_file.c_str(), 0) == -1)
	{
		ofstream out(warning_log_file.c_str(), ios::app);
		write_Time(warning_log_file);
		out << "打开了" << file_name << endl;
		out.close();
	}
}
void write_Operation(const string& log_name, const string operation)
{
	ofstream out;
	out.open(log_name.c_str(), ios::app | ios::out);
	if (operation == "purge")
	{
		out << " 开始进行" << operation << "操作" << endl;
	}
	else if (operation == "purge_finish")
		out << "purge操作已完成" << endl;
	else
		out << " " << operation << "操作";
	out.close();
}
void write_Filesize(const string &log_name,int length)
{
	ofstream out;
	out.open(log_name.c_str(), ios::app | ios::out);
	if (length == -1)
		out << endl;
	else
		out << " 此时文件的大小为" << length<<endl;
	out.close();
}
void write_Duration(const string& log_name, double duration)
{
	ofstream out;
	out.open(log_name.c_str(), ios::app | ios::out);
	out << " 运行花费时间" << duration  << "ms";
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
	out << "发生错误,类型为" << type << endl;
	out.close();
}