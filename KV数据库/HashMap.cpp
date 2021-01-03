#include<iostream>
#include"HashMap.h"
void HashMap::add(const string& key, int offset)
{
		int n = getHash(key.c_str());
		ListNode* N = Hashmap[n];
		while (true)
		{
			if (N->_key == key)
			{
				N->_offset = offset;
				break;
			}
			if (N->next == NULL)
			{
				ListNode* P = new ListNode(key, offset);
				N->next = P;
				break;
			}
			N = N->next;
		}
}
int HashMap::getHash(const char* str)
{
	unsigned int seed = 131;
	unsigned int hash = 0;
	while (*str)
	{
		hash = hash * seed + (*str++);
	}
	return ((hash & 0x7FFFFFFF) % 99991);
}
void HashMap::del(const string& key)
{
	int n = getHash(key.c_str());
	ListNode* N = Hashmap[n];
	while (true)
	{
		if (N ->next->_key == key)
		{
			if (N->next->next == NULL)
			{
				N->next = NULL;
				return;
			}
			else
			{
				N->next = N->next->next;
				return;
			}

		}
		N = N->next;
	}
}
int HashMap::get(const string& key)
{
	int n = getHash(key.c_str());
	ListNode* N = Hashmap[n];
	while (true)
	{
		if (N->_key == key)
		{
			return N->_offset;
		}
		if (N->next == NULL)
		{
			return -1;
		}
		N = N->next;
	}
}
HashMap::HashMap()
{
	Hashmap = new ListNode * [200000];
	for (int i = 0; i < 200000; i++)
	{
		Hashmap[i] = new ListNode();
	}
}
void HashMap::Get_offset_order(int *offset_order)
{
	int j=0,k;
	for (int i = 0; i < 200000; i++)
	{
		if (Hashmap[i]->next != NULL)
		{
			ListNode* T = new ListNode();
			T = Hashmap[i]->next;
			while (T)
			{
				int temp = T->_offset;
				for (k = j - 1; k >= 0; k--)
				{
					if (offset_order[k] <= temp)
						break;
					offset_order[k + 1] = offset_order[k];
				}
				offset_order[k + 1] = temp;
				j++;
				T = T->next;
			}
			
		}
	}
}
HashMap:: ~HashMap()
{
	for (int i = 0; i < 200000; i++)
	{
		if (Hashmap[i])
		{
			while (Hashmap[i]->next)
			{
				ListNode* temp = Hashmap[i]->next;
				if (temp)
				{
					Hashmap[i]->next = temp->next;
				}
				delete temp;
			}
			delete Hashmap[i];
		}
	}
}
/*int HashMap::GetNode(const string &key,LRUNode **node)
{
	int n = getHash(key.c_str());
	ListNode* N = Hashmap[n];
	while (true)
	{
		if (N->_key == key)
		{
			if (N->node == NULL)
			{
				node = NULL;
				return 0;
			}
			else
			{
				(*node) = N->node;
				return 1;
			}
		}
		if (N->next == NULL)
		{
			node = NULL;
			return 2;
		}
		N = N->next;
	}
}
void HashMap::SetNode(const string& key,LRUNode *Node,string order)
{
	int n = getHash(key.c_str());
	ListNode* N = Hashmap[n];
	while (true)
	{
		if (N->_key == key)
		{
			if (order == "erase")
				N->node = NULL;
			else
				N->node = Node;
			break;
		}
		N = N->next;
	}
}*/