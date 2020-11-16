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
void Createlog(const string &log_file);
void write_Filesize(const string &log_name,int length);
void write_Duration(const string &log_name,double duration);
void write_Operation(const string &log_name,const string operation);
void write_Time(const string &log_name);
void write_Error(const string &log_name,const string &type);

