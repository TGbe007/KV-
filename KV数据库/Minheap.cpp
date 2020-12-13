#include"Minheap.h"
#include <string>
MinHeap::MinHeap()
{
	_maxSize = 10000;
	_index = -1;
	_minHeap = new Dead[_maxSize];
}
MinHeap::MinHeap(MinHeap& h)
{
	_maxSize = h._maxSize;
	_index = h._index;
	for (int i = 0; i < h._index; i++)
		_minHeap[i] = h._minHeap[i];
}
MinHeap::~MinHeap()
{
	delete[] _minHeap;
}
Dead* MinHeap::GetMinHeap()
{
	return _minHeap;
}
bool MinHeap::IsEmpty()
{
	return _index == -1;
}
bool MinHeap::IsFull()
{
	return _index == _maxSize;
}
bool MinHeap::Add(Dead x)
{
	if (IsFull())
		return false;

	_index++;
	_minHeap[_index] = x;
	return true;
}
void MinHeap::CreatMinHeap()
{
	if (IsEmpty())
		return;

	for (int i = (_index - 1) / 2; i > -1; i--)
	{
		AdjustDown(i);
	}
}

void MinHeap::AdjustDown(int index)
{
	if (IsEmpty())
		return;

	int temp;
	int flag = 0;

	while ((index * 2 + 1) <= _index && flag == 0)
	{
		if (compare(_minHeap[index].time  ,_minHeap[index * 2 + 1].time)) //将此处及以下几处的大于号改成小于号，则最小堆就变成最大堆
			temp = index * 2 + 1;
		else
			temp = index;
		if (index * 2 + 2 <= _index)
		{
			if (compare(_minHeap[temp].time , _minHeap[index * 2 + 2].time))//将此处及以下几处的大于号改成小于号，则最小堆就变成最大堆
				temp = index * 2 + 2;
		}
		if (temp != index)
		{
			Dead t = _minHeap[temp];
			_minHeap[temp] = _minHeap[index];
			_minHeap[index] = t;
			index = temp;
		}
		else
			flag = 1;

	}
}

void MinHeap::AdjustUp(int index)
{
	if (index < 0 || index == 0)
		return;
	int flag = 0;
	while (index != 0 || flag == 0)
	{
		int i = (index - 1) / 2;
		if (compare(_minHeap[i].time , _minHeap[index].time)==1)//将此处及以下几处的大于号改成小于号，则最小堆就变成最大堆
		{
			Dead t = _minHeap[i];
			_minHeap[i] = _minHeap[index];
			_minHeap[index] = t;
		}
		else
			flag = 1;

		index = (index - 1) / 2;
	}
}

bool MinHeap::InsertNode(const Dead& v)
{
	if ((_index + 1) < _maxSize)
	{
		_index++;
		_minHeap[_index] = v;
		AdjustUp(_index);
		return true;
	}
	else
		return false;
}
bool MinHeap::DeleteNode(Dead& v)
{
	if (IsEmpty())
		return false;
	v = _minHeap[0];
	_minHeap[0] = _minHeap[_index];
	_index--;
	AdjustDown(_index);
}
int compare(Deadtime d1, Deadtime d2)
{
	string str1, str2;
	str1 = to_string(d1.year);
	if (d1.month < 10)
	{
		str1.append("0");
		str1.append(to_string(d1.month));
	}
	else
		str1.append(to_string(d1.month));
	if (d1.day < 10)
	{
		str1.append("0");
		str1.append(to_string(d1.month));
	}
	else
		str1.append(to_string(d1.day));
	if (d1.hour < 10)
	{
		str1.append("0");
		str1.append(to_string(d1.hour));
	}
	else
		str1.append(to_string(d1.hour));
	if (d1.minute < 10)
	{
		str1.append("0");
		str1.append(to_string(d1.minute));
	}
	else
		str1.append(to_string(d1.minute));
	if (d1.second < 10)
	{
		str1.append("0");
		str1.append(to_string(d1.second));
	}
	else
		str1.append(to_string(d1.second));
	str2 = to_string(d1.year);
	if (d1.month < 10)
	{
		str2.append("0");
		str2.append(to_string(d1.month));
	}
	else
		str2.append(to_string(d1.month));
	if (d1.day < 10)
	{
		str2.append("0");
		str2.append(to_string(d1.month));
	}
	else
		str2.append(to_string(d1.day));
	if (d1.hour < 10)
	{
		str2.append("0");
		str2.append(to_string(d1.hour));
	}
	else
		str2.append(to_string(d1.hour));
	if (d1.minute < 10)
	{
		str2.append("0");
		str2.append(to_string(d1.minute));
	}
	else
		str2.append(to_string(d1.minute));
	if (d1.second < 10)
	{
		str2.append("0");
		str2.append(to_string(d1.second));
	}
	else
		str2.append(to_string(d1.second));
	if (str1 > str2)
		return 1;
	if (str1 == str2)
		return 0;
	if (str1 < str2)
		return -1;
}
Deadtime add(Deadtime d1, int n)
{
	d1.second = d1.second + n;
	if (d1.second >= 60)
	{
		d1.minute = d1.minute + 1;
		d1.second = d1.second - 60;
		if (d1.minute >= 60)
		{
			d1.hour = d1.hour + 1;
			d1.minute = d1.minute - 60;
			if (d1.hour >= 24)
			{
				d1.hour = d1.hour - 24;
				d1.day = d1.day + 1;
				return d1;
			}
			else
				return d1;
		}
		else
			return d1;
	}
	else
	{
		return d1;
	}
}
