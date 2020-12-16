#pragma once
#include "CarNode.h"
class Queue
{
public: 		// public member funciton
	Queue();	
	~Queue();
	CarNode * pHead;							// member variable
	void		Push(CarNode * node);			// LOAD
	CarNode *	Pop();							
	CarNode *	Search(int num);				// SEARCH
	bool		Print();						// PRINT
	bool		Save();
};

