#pragma once
#include "LinkedList.h"
#include "NumberBST.h"
#include "Queue.h"
#include<utility>


class Manager
{
public:
	LinkedList * ll;
	NumberBST * bst;
	Queue * queue;

public:
	Manager();
	~Manager();

	void run(const char * command);
	bool LOAD();
	bool ADD();
	bool MOVE(int parameter);
	bool SAVE();
	bool SEARCH(int parameter);
	bool PRINT(char* parameter);
	bool COMPLETE(int parameter);
	void EXIT();

	void printErrorCode(int n);
	void printSuccessCode(const char * cmdname);

};
