#pragma once
#include "CarNode.h"

class LinkedList
{
public:
	CarNode * pHead;

	LinkedList();
	~LinkedList();
	void SetHeadNull() { pHead = NULL; }
	void Insert(CarNode* node);	//LOAD, ADD
	CarNode * Search(int car);		//SEARCH
	bool Print();	//PRINT
	bool Save();	//SAVE
	bool Delete(int Carnum);
};
