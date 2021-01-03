#pragma once
#include<iostream>
#include<cstring>
using namespace std;
/*struct LRUNode//为LRU所创设的节点
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
	//LRUNode* node;LRU的节点
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
		//int GetNode(const string& key, LRUNode** node);//用来返回对应的node对象
		//void SetNode(const string& key, LRUNode* Node,string order);
};
