#pragma once
#pragma warning(disable:4996)
#include <iostream>
#include <algorithm>
using namespace std;

template <class T>
class MaxHeap
{
private:
	T* heap; //원소 배열
	int heapSize; //히프에 있는 원소 수
	int capacity; //배열 히프의 크기

public:
	MaxHeap(int theCapacity = 10);
	~MaxHeap() { ; };

	bool IsEmpty();
	void ChangeSize1D(T*& a, const int oldSize, const int newSize);
	void Push(const T& e); //최대 히프에 삽입
	void Pop(); //최대 히프에서의 삭제
	void Show();

	T* get_heap() { return heap; }
};

template <class T>
inline MaxHeap<T>::MaxHeap(int theCapacity = 10) //constructor
{
	if (theCapacity < 1) throw "Capacity must be >= 1.";
	capacity = theCapacity;
	heapSize = 0;
	heap = new T[capacity + 1]; //heap[0]은 사용되지 않음
}

template <class T>
inline bool MaxHeap<T>::IsEmpty()
{
	if (heapSize == 0)
		return true;
	else
		return false;
}

/*Change Size 1D function that using in Push function*/
template <class T>
inline void MaxHeap<T>::ChangeSize1D(T*& a, const int oldSize, const int newSize)
{	
	if (newSize < 0) throw "New length must be >= 0";

	T* temp = new T[newSize];
	int number = min(oldSize, newSize); //oldSize와 newSize 중 작은 것
	copy(a, a + number, temp); 
	delete[]a; //deallocate old memory
	a = temp;
}

/*Push function*/
template <class T>
inline void MaxHeap<T>::Push(const T& e)
{
	if (heapSize == capacity) {
		ChangeSize1D(heap, capacity, 2 * capacity);
		capacity *= 2; //change capacity into double capacity
	}

	int currentNode = ++heapSize;
	while (currentNode != 1 && heap[currentNode / 2] < e)
	{
		heap[currentNode] = heap[currentNode / 2]; //move parent down
		currentNode /= 2; //move to parent
	}
	heap[currentNode] = e;
}

/*Pop function*/
template <class T>
inline void MaxHeap<T>::Pop()
{
	if (IsEmpty()) throw "Heap is empty. Cannot delete.";
	heap[1].~T(); //최대 원소 삭제

	
	T lastE = heap[heapSize--];

	int currentNode = 1; //root
	int child = 2; //currentNode의 자식
	while (child <= heapSize)
	{
		//child를 currentNode의 큰 자식으로 결정
		if (child < heapSize && heap[child] < heap[child + 1]) child++;

		if (lastE >= heap[child])break; //we can put lastE in currentNode

		//we cannot put lastE in currentNode
		heap[currentNode] = heap[child]; //move child up
		currentNode = child; 
		child *= 2; //move down a level
	}
	heap[currentNode] = lastE;
}

template <class T>
inline void MaxHeap<T>::Show()
{
	for (int i = 1; i <= heapSize; i++)
	{
		cout << heap[i] << " ";
	}
	cout << endl;
}