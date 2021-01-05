#include<iostream>
#include<cstring>
using namespace std;
struct ListNode
{
	ListNode* next;
	string _key;
	int _offset;
	ListNode() { next = NULL; }
	ListNode(string const& key, int offset)
	{
		_key = key;
		_offset = offset;
		next = NULL;
	}
};
class HashMap
{
private:
	ListNode** Hashmap;
public:
	HashMap();
	void add(const string& key, int offset);
	void del(const string& key);
	int get(const string& key);
	int getHash(const char* str);
	void Get_offset_order(int* offset_order);
	~HashMap();
};