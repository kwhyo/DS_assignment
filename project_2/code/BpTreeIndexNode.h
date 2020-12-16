#ifndef _BPTREEINDEXNODE_H_
#define _BPTREEINDEXNODE_H_

#include "BpTreeNode.h"

class BpTreeIndexNode : public BpTreeNode{
private:
	map <double, BpTreeNode*> mapIndex;
	
public:
	BpTreeIndexNode(){}
	~BpTreeIndexNode(){}
	
	void insertIndexMap(double n, BpTreeNode* pN)
	{
		mapIndex.insert(map <double, BpTreeNode*>::value_type(n, pN));
	}

	void deleteMap(double n){
		// 코드 작성
	}
	void insertDataMap(double n, vector<pair<int, StockData*> > m) { ; }
	map <double, BpTreeNode*>* getIndexMap()	{ return &mapIndex; }

	map< double, vector<pair<int, StockData*> > > *getDataMap() { return NULL; }

	void setNext(BpTreeNode* pN) { ; }
	void setPrev(BpTreeNode* pN) { ; }
	BpTreeNode* getPrev() { return NULL; }
	BpTreeNode* getNext() { return NULL; }

};

#endif