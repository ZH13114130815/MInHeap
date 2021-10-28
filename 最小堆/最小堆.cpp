#include <cstdlib>
#include <iostream>
using namespace std;
#define DefaultSize 20

template<class T>
class MinHeap
{
public:
	MinHeap(int sz = DefaultSize);
	MinHeap(T arr[], int n);
	~MinHeap() { delete[] heap; }
	bool Insert(const T& x);
	bool Remove(T& x);
	bool IsEmpty() { return currentSize == 0; }
	bool IsFull() { return currentSize == maxHeapSize; }
	void MakeEmpty() { currentSize = 0; }

	void Display()const {
		for (int i = 0; i < currentSize; i++)
			cout << heap[i] << "  ";
		cout << endl;
	}
private:
	T* heap;
	int currentSize;
	int maxHeapSize;
	void siftDown(int start, int m);
	void siftUp(int start);
};


template<class T>
MinHeap<T>::MinHeap(int sz)
{
	maxHeapSize = (sz > DefaultSize) ? sz : DefaultSize;
	heap = new T[maxHeapSize];
	if (heap == NULL)
	{
		cerr << "堆储存分配错误！" << endl;
		exit(1);
	}
	currentSize = 0;
}


template<class T>
MinHeap<T>::MinHeap(T arr[], int n)
{
	maxHeapSize = (n > DefaultSize) ? n : DefaultSize;
	heap = new T[maxHeapSize];
	if (heap == NULL)
	{
		cerr << "堆储存分配错误！" << endl;
		exit(1);
	}
	for (int i = 0; i < n; i++)
		heap[i] = arr[i];
	currentSize = n;
	int currentPos = (currentSize - 2) / 2;
	while (currentPos >= 0)
	{
		siftDown(currentPos, currentSize-1);
		currentPos--;
	}
}


template<class T>
void MinHeap<T>::siftDown(int start, int m)
{
	int i = start;
	int j = 2 * i + 1;
	T temp = heap[i];
	while (j <= m)
	{
		if (j<m && heap[j]>heap[j + 1]) j++;
		if (heap[j] >= temp) break;
		else
		{
			heap[i] = heap[j];
			i = j;
			j = 2 * j + 1;
		}
	}
	heap[i] = temp;
}


template<class T>
void MinHeap<T>::siftUp(int start)
{
	int j = start;
	int i = (j - 1) / 2;
	T temp = heap[j];
	while (j > 0)
	{
		if (temp >= heap[i]) break;
		else
		{
			heap[j] = heap[i];
			j = i;
			i = (i - 1) / 2;
		}
	}
	heap[j] = temp;
}

template<class T>
bool MinHeap<T>::Insert(const T& x)
{
	if (currentSize == maxHeapSize)
	{
		cerr << "Heap Full" << endl;
		return false;
	}
	heap[currentSize] = x;
	siftUp(currentSize);
	currentSize++;
	return true;
}


template<class T>
bool MinHeap<T>::Remove(T& x)
{
	if (currentSize == 0)
	{
		cout << "Heap empty" << endl;
		return false;
	}
	x = heap[0];
	heap[0] = heap[currentSize - 1];
	currentSize--;
	siftDown(0, currentSize - 1);
	return true;
}

int main() {

	MinHeap<int> mp(10);

	int k[] = { 4, 2, 5, 8, 3, 6, 10, 14 };

	int i;
	for (i = 0; i < 8; i++) {
		mp.Insert(k[i]);
		cout << "插入 " << k[i] << " ：\t";
		mp.Display();
	}

	cout << "*******************************************************" << endl;
	int a;
	mp.Remove(a);
	cout << "第 1 次删除的数据为：" << a << "，堆为：";
	mp.Display();

	mp.Remove(a);
	cout << "第 2 次删除的数据为：" << a << "，堆为：";
	mp.Display();


	cout << endl << endl;

	int data[] = { 100, 86, 48, 73, 35, 39, 42, 57, 66, 21 };
	cout << "调整前次序：";
	for (i = 0; i < 10; i++) {
		cout << data[i] << "  ";
	}
	cout << endl;

	MinHeap<int> mp1(data, 10);
	cout << "放入堆后次序：";
	mp1.Display();
	cout << endl;

	system("pause");
}