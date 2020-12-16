#pragma once
#include "CarBST.h"

class NumberNode
{
private:
	int number;
	CarBST * bst;
	NumberNode * pLeft;			// BST Left Pointer
	NumberNode * pRight;		// BST Right Pointer

public:
	NumberNode();
	~NumberNode();

	int			GetNumber() { return number; }						// Get Number
	CarBST *		GetBST() { return bst; }						// Get Car BST
	NumberNode *	GetLeft() { return pLeft; }				// Get BST Left Pointer
	NumberNode *	GetRight() { return pRight; }						// Get BST Right Pointer

	void			SetNumber(int num) { number = num; }			// Set Alphabet
	void			SetLeft(NumberNode * node) { this->pLeft = node; }		// Set BST Left Pointer
	void			SetRight(NumberNode * node) { this->pRight = node; }	// Set BST Right Pointer
	void 			SetBST(CarBST * node) { this->bst = node; }			// Set Car BST
};