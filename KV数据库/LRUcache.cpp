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
    LRUNode* node;//��hashmap��������һ��LRUNode����
    int state=hashmap_.GetNode(key, &node);
    if (state==1)//cache hit
    {
        detach(node);//ɾ����LRUCache�����Ѿ����ڵĽڵ�
        node->key = key;
        node->value = value;
        attach(node);//
    }
    else//update��û�д�����LRUCache
    {
        if (size==capacity)//cache full
        {
            node = tail->pre;
            detach(node);
            hashmap_.SetNode(node->key,node,"erase");// ���һ���ڵ�ɾ��������Ҫ�Ӷ�һ������
        }
        else//δ��
        {
            node = new LRUNode();
            size++;
        }
        node->key = key;
        node->value = value;
        hashmap_.SetNode(key,node,"set");//��������ڵ�
        attach(node);
    }
}
int LRUCache::Get(const string& key,string &value,HashMap &hashmap_)
{
    LRUNode* node;//��ȡ���node
    int state = hashmap_.GetNode(key, &node);
    if (state == 2)
        return 2;//�����������
    else if (state == 0)
        return 0;//�������δ������LRUCache
    else if (state==1)//cache hit
    {
        detach(node);
        attach(node);
        value=node->value;
        return 1;
    }//�ѳɹ��ҵ�����
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