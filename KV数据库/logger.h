#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<stdarg.h>
#include<windows.h>
#include<memory.h>
#include<string>
#include<iostream>
#include<fstream>
#include <io.h>
using namespace std;
class Log
{
	private:
		string name;
		ifstream in;
		ofstream out;	
	public:
		Log();
		void write_Filesize(int length);
		void write_Duration(double duration);
		void write_Operation(const string operation);
		void write_Time();
		void write_Error(const string &type);
};

