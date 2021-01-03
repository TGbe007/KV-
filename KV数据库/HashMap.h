#pragma once
#include<iostream>
#include<cstring>
using namespace std;
/*struct LRUNode//ΪLRU������Ľڵ�
{
	string value, key;
	LRUNode* pre, * next;
	LRUNode(string key, string value)
	{
		this->key = key;
		this->value = value;
		pre = NULL;
		next = NULL;
	}
};*/
struct ListNode
{
	ListNode* next;
	//LRUNode* node;LRU�Ľڵ�
	string _key;
	int _offset;
	ListNode() { next = NULL;}
	ListNode(string const& key, int offset)
	{
		_key = key;
		_offset = offset;
		next = NULL;
		//node = NULL;
	}
};
class HashMap
{
	private:
		ListNode **Hashmap;
	public:
		HashMap();
		void add(const string& key, int offset);
		void del(const string& key);
		int get(const string& key);
		int getHash(const char* str);
		void Get_offset_order(int* offset_order);
		void Clear();
		~HashMap();
		//int GetNode(const string& key, LRUNode** node);//�������ض�Ӧ��node����
		//void SetNode(const string& key, LRUNode* Node,string order);
};
