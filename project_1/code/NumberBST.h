#pragma once
#include "NumberNode.h"
#include <iostream>


class NumberBST
{
private:
	NumberNode * root;
	int nodeCnt;

public:
	NumberBST();
	~NumberBST();

	void	SetRootNull() { root = NULL; }
	void		Insert(NumberNode * node);			// LOAD, MOVE
	NumberNode *	Delete(int num);				// COMPLETE
	NumberNode *	Search(int num);				// ADD, COMPLETE, SEARCH
	bool		Print(char * BST);					// PRINT
	bool		Save();								// SAVE
	
	void		Save_preorder(NumberNode *node);
	void		Inorder(NumberNode *node);
	void		Preorder(NumberNode *node);
	void		Postorder(NumberNode *node);

	void		Inorder_I(NumberNode *node);
	void		Preorder_I(NumberNode *node);
	void		Postorder_I(NumberNode *node);
	
	void		Levelorder(NumberNode *node);
	int			getCnt() { return nodeCnt; }
	void		setCnt(int cnt) { nodeCnt = nodeCnt + cnt; }
};