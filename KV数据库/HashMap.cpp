#include<iostream>
#include"HashMap.h"
void HashMap::add(const string& key, int offset)
{
	int n = getHash(key.c_str());
	ListNode* N = Hashmap[n];
	while (true)
	{
		if (N->_key == key)//证明本来存在了，就修改offset
		{
			N->_offset = offset;
			break;
		}
		if (N->next == NULL)//证明不存在，就插入
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
	return ((hash & 0x7FFFFFFF) % 99991);//这里取余随着数据大小，找到范围内最大的那一个素数
}
void HashMap::del(const string& key)
{
	int n = getHash(key.c_str());
	ListNode* N = Hashmap[n];
	while (true)
	{
		if (N->next->_key == key)//则找到key了
		{
			if (N->next->next == NULL)//判断key的后一个是否存在，如果不存在则直接删除该节点
			{
				N->next = NULL;
				return;
			}
			else//后一个节点存在，则直接让N->next指向后一个
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
		if (N->_key == key)//key相同即找到了，返回offset
		{
			return N->_offset;
		}
		if (N->next == NULL)//则证明找不到了，返回-1；
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
void HashMap::Get_offset_order(int* offset_order)//用来给Offset排序
{
	int j = 0, k;
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