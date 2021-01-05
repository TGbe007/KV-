/*#pragma once
#include<iostream>
#include"HashMap.h"
using namespace std;
struct LRUNode
{
	string value, key;
	LRUNode* pre, * next;
	LRUNode()
	{
		this->key = "0";
		this->value = "0";
		pre = NULL;
		next = NULL;
	}
};
class LRUCache
{
	private:
		int capacity;
		int size;
		LRUNode* head, * tail;
		void attach(LRUNode *node);
		void detach(LRUNode* node);
	public:
		LRUCache();
		void Put(string key, string value, HashMap& hashmap_);
		int Get(const string& key, string& value, HashMap& hashmap_);
};*/
#pragma once
