#include <iostream>
#include "MaxHeap.h"
using namespace std;

int main()
{
	int capacity; //MaxHeap's capacity
	

	MaxHeap<int>* m_heap = new MaxHeap<int>(5);

	m_heap->Push(9);
	m_heap->Push(3);
	m_heap->Push(2);
	m_heap->Push(10);
	m_heap->Push(7);
	m_heap->Show();

	m_heap->Pop();
	m_heap->Pop();

	m_heap->Show();

	

	return 0;
}