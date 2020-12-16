#pragma once
#include <iostream>

using namespace std;

class CarNode
{
private:
	int carNumber;
	char * name;
	char state;

	CarNode * pLeft;	// BST Left Pointer
	CarNode * pRight;	// BST Right Pointer
	CarNode * pNext;	// Queue Next Pointer, LinkedList Next Pointer


public:
	CarNode();
	~CarNode();

	int GetcarNum() { return carNumber; }		// Get car number
	char * GetcarOwner() { return name; }	// Get car owner
	char Getstate() { return state; }		// Get state

	CarNode * GetLeft() { return pLeft; }	// Get BST Left Pointer
	CarNode * GetRight() { return pRight; }	// Get BST Right Pointer
	CarNode * GetNext() { return pNext; }	// Get Queue Next Pointer

	void SetcarNum(int carNum) { carNumber = carNum; }			// Set car number
	void SetcarOwner(char * carOwner) { name = carOwner; }	// Set car owner
	void Setstate(char state) { this->state = state; }			// Set car state
	void SetLeft(CarNode * node) { this->pLeft = node; }		// Set BST Left Pointer
	void SetRight(CarNode * node) { this->pRight = node; }		// Set BST Right Pointer
	void SetNext(CarNode * node) { this->pNext = node; }		// Set Queue Next Pointer
};

