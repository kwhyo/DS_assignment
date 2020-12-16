#pragma once
#include "CarNode.h"
#include <iostream>
#include <fstream>// header file declare
using namespace std;
class CarBST
{
public:
	CarNode * root;	

public:
	CarBST();
	~CarBST();

	void		Insert(CarNode * node);			// LOAD, MOVE
	CarNode *	Delete(int num);				// COMPLETE
	CarNode *	Search(int num);				// ADD, COMPLETE, SEARCH
	bool		Print(const char * order);		// PRINT
	bool		Save(ofstream &event_list);							// SAVE


	void		visit(CarNode *node);
	void		Inorder(CarNode *node);
	void		Preorder(CarNode *node);
	void		Postorder(CarNode *node);
	void		Inorder_I(CarNode *node);
	void		Preorder_I(CarNode *node);
	void		Postorder_I(CarNode *node);
	void		Levelorder(CarNode* node);
};

