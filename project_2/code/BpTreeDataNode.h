#ifndef _BPTREEDATANODE_H_
#define _BPTREEDATANODE_H_

#include "BpTreeNode.h"

class BpTreeDataNode : public BpTreeNode
{
private:
	map <double, vector<pair<int, StockData*> > > mapData;
	BpTreeNode* pNext;
	BpTreeNode* pPrev;

public:
	BpTreeDataNode(){
		pNext = NULL;
		pPrev = NULL;
	}

	void setNext(BpTreeNode* pN)	{ pNext = pN; }
	void setPrev(BpTreeNode* pN)	{ pPrev = pN; }
	BpTreeNode* getNext()				{ return pNext; }
	BpTreeNode* getPrev()				{ return pPrev; }	

	void insertDataMap(double n, vector<pair<int, StockData*> > m)
	{
		
		mapData.insert(map<double, vector<pair<int, StockData*> > >::value_type(n, m));

	}
	void insertIndexMap(double n, BpTreeNode* pN)
	{ 
		
	}
	
	void deleteMap(double n)
	{
		// 코드 작성
	}	

	map< double, vector<pair<int, StockData*> > > *getDataMap()		{ return &mapData; }
	map <double, BpTreeNode*>* getIndexMap() { return NULL; }
};

#endif
