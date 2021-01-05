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
void Createlog(const string& log_file, const string& file_name, const string& warning_log_file);
void write_Filesize(const string& log_name, int length, ofstream& out);
void write_Duration(const string& log_name, double duration, ofstream& out);
void write_Operation(const string& log_name, const string operation, const string key, const string value, ofstream& out);
void write_Time(const string& log_name, ofstream& out);
void write_Error(const string& log_name, const string& type, ofstream& out);
