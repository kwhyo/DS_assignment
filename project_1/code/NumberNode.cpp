#include "NumberNode.h"


NumberNode::NumberNode()//constructor
{
	CarBST* newBST = new CarBST();
	bst = newBST;
	bst->root = NULL;
	pLeft = NULL;
	pRight = NULL;
	
}

NumberNode::~NumberNode()//destructor
{
	delete bst;

}
