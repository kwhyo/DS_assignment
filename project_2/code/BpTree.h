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
	bool	exceedDataNode(BpTreeNode* pDataNode); //���ƴ��� Ȯ��
	bool	exceedIndexNode(BpTreeNode* pIndexNode); //�ε��� ���ƴ��� Ȯ��
	void	splitDataNode(BpTreeNode* pDataNode); //��ģ ������ �ڸ���
	void	splitIndexNode(BpTreeNode* pIndexNode); //��ģ �ε��� �ڸ���
	BpTreeNode*	searchDataNode(double n); //�׷� ���ͷ� ������ �ֳ� ã��

	bool	Print(); // PRINT_BP
	bool	Search(double a, double b); // SEARCH_BP	


	void	moving_and_print(BpTreeNode* p);
	void	moving_and_print2(BpTreeNode * p, double a, double b,int& check);
	void	printStockInfo(StockData* pStockData);
};

#endif
