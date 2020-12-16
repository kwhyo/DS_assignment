#ifndef _BPTREE_H_
#define _BPTREE_H_

#include "BpTreeIndexNode.h"
#include "BpTreeDataNode.h"

class BpTree{
private:
	BpTreeNode*	root;
	int					order;	
	ofstream*		fout;

public:
	BpTree(ofstream* fout, int order = 3);
	~BpTree();

	void	Insert(StockData* pStockData);
	bool	exceedDataNode(BpTreeNode* pDataNode); //넘쳤는지 확인
	bool	exceedIndexNode(BpTreeNode* pIndexNode); //인덱스 넘쳤는지 확인
	void	splitDataNode(BpTreeNode* pDataNode); //넘친 데이터 자르기
	void	splitIndexNode(BpTreeNode* pIndexNode); //넘친 인덱스 자르기
	BpTreeNode*	searchDataNode(double n); //그런 수익률 가진게 있나 찾기

	bool	Print(); // PRINT_BP
	bool	Search(double a, double b); // SEARCH_BP	


	void	moving_and_print(BpTreeNode* p);
	void	moving_and_print2(BpTreeNode * p, double a, double b,int& check);
	void	printStockInfo(StockData* pStockData);
};

#endif
