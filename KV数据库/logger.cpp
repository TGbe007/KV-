#include"logger.h"
#include<fstream>
void Log::write_Operation(const string operation)
{
	out.open(name.c_str(), ios::app | ios::out);
	out << " " << operation << "操作";
	out.close();
}
void Log::write_Filesize(int length)
{
	out.open(name.c_str(), ios::app | ios::out);
	out << " 此时文件的大小为" << length;
	out.close();
}
void Log::write_Duration(double duration)
{
	out.open(name.c_str(), ios::app | ios::out);
	out << " 运行花费时间" << duration * 1000 << "ms";
	out.close();
}
void Log::write_Time()
{
	out.open(name.c_str(), ios::app | ios::out);
	time_t timep;
	struct tm* p;
	time(&timep);
	p = gmtime(&timep);
	out << p->tm_year + 1900 << "-" << p->tm_mon + 1 << "-" << p->tm_mday << " " << p->tm_hour + 8 << ":" << p->tm_min << ":" << p->tm_sec;
}
Log::Log()
{
	name = "log.txt";
	if (_access(name.c_str(), 0) == -1)
	{
		ofstream fout(name.c_str(), ios::app);
		fout.close();
	}
}
void Log::write_Error(const string &type)
{
	out.open(name.c_str(), ios::app | ios::out);
	out << "发生错误,类型为" << type << endl;
	out.close();
}