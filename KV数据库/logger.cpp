#include"logger.h"
#include<fstream>
void Createlog(const string& log_file, const string& file_name, const string& warning_log_file)
{
	if (_access(log_file.c_str(), 0) == -1)
	{
		ofstream fout(log_file.c_str(), ios::app);
		write_Time(log_file, fout);
		fout << " 打开了" << file_name << endl;
		fout.close();
	}
	if (_access(warning_log_file.c_str(), 0) == -1)
	{
		ofstream out(warning_log_file.c_str(), ios::app);
		write_Time(warning_log_file, out);
		out << "打开了" << file_name << endl;
		out.close();
	}
}
void write_Operation(const string& log_name, const string operation, const string key, const string value, ofstream& out)
{
	if (operation == "purge")
	{
		out << " 开始进行" << operation << "操作" << endl;
	}
	else if (operation == "purge_finish")
		out << "purge操作已完成" << endl;
	else
		out << " " << operation << "操作";
	if (operation == "Set")
	{
		out << " 写入的Key值为:" << key << " " << " value值为: " << value;
	}
	else if (operation == "Get")
	{
		out << " 读取的Key值为" << key << " ";
	}
	else if (operation == "Del")
	{
		out << " 删除的Key值为" << key << " ";
	}
}
void write_Filesize(const string& log_name, int length, ofstream& out)
{
	if (length == -1)
		out << endl;
	else
		out << " 此时文件的大小为" << length << endl;
}
void write_Duration(const string& log_name, double duration, ofstream& out)
{
	out << " 运行花费时间" << duration << "ms";
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
	out << "发生错误,类型为" << type << endl;
}