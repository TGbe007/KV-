/*#include"LRUcache.h"
LRUCache::LRUCache()
{
    capacity = 10;
    size = 0;
    head = new LRUNode;
    tail = new LRUNode;
    head->next = tail;
    head->pre = NULL;
    tail->pre = head;
    tail->next = NULL;
}
void LRUCache::Put(string key, string value,HashMap &hashmap_)
{
    LRUNode* node;//用hashmap给他返回一个LRUNode对象
    int state=hashmap_.GetNode(key, &node);
    if (state==1)//cache hit
    {
        detach(node);//删除在LRUCache里面已经存在的节点
        node->key = key;
        node->value = value;
        attach(node);//
    }
    else//update并没有存在于LRUCache
    {
        if (size==capacity)//cache full
        {
            node = tail->pre;
            detach(node);
            hashmap_.SetNode(node->key,node,"erase");// 最后一个节点删除，这里要加多一个函数
        }
        else//未满
        {
            node = new LRUNode();
            size++;
        }
        node->key = key;
        node->value = value;
        hashmap_.SetNode(key,node,"set");//设置这个节点
        attach(node);
    }
}
int LRUCache::Get(const string& key,string &value,HashMap &hashmap_)
{
    LRUNode* node;//获取这个node
    int state = hashmap_.GetNode(key, &node);
    if (state == 2)
        return 2;//这个数不存在
    else if (state == 0)
        return 0;//这个数还未被插入LRUCache
    else if (state==1)//cache hit
    {
        detach(node);
        attach(node);
        value=node->value;
        return 1;
    }//已成功找到该数
}
void LRUCache::attach(LRUNode* node)
{
    node->next = head->next;
    head->next = node;
    node->next->pre= node;
    node->pre= head;
}
void LRUCache::detach(LRUNode* node)
{
    node->pre->next = node->next;
    node->next->pre = node->pre;
}*/