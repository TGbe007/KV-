#include<iostream>
using namespace std;
struct Dead
{
	Deadtime time;
	string key;
};
struct Deadtime
{
	int year, month, day, hour, minute, second;
};
class MinHeap
{
private:
	Dead* _minHeap;
	int	_index;
	int _maxSize;
public:
	MinHeap();
	MinHeap(MinHeap& h);
	~MinHeap();
	Dead* GetMinHeap();
	bool IsEmpty();
	bool IsFull();
	bool Add(Dead x);
	void CreatMinHeap();
	void AdjustDown(int index);
	void AdjustUp(int index);
	bool InsertNode(const Dead& v);
	bool DeleteNode(Dead& v);
};
int compare(Deadtime d1, Deadtime d2);
Deadtime add(Deadtime d1, int n);
