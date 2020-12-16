#include "BpTree.h"

BpTree::BpTree(ofstream* fout, int order){
	root = NULL;
	this->order = order;  //order�� ����ų �� �ִ� �ڽ� �� pointer����!
	this->fout = fout;
}

BpTree::~BpTree(){

}

void BpTree::Insert(StockData* pSto){
	
	double key = pSto->getEarning();	// key = Earning
	vector<pair<int, StockData*> > value;			// value = map< id, stock data* >
	value.push_back( make_pair(pSto->getStockID(), pSto) );	
	
	if(root == NULL){ // empty B+ tree
		BpTreeNode* pDataNode = new BpTreeDataNode;	
		pDataNode->insertDataMap(key, value); //���ͷ�, id, data ����
		pDataNode->setParent(NULL);
		pDataNode->setMostLeftChild(NULL);
		pDataNode->setPrev(NULL);
		pDataNode->setNext(NULL);
		root = pDataNode;
		return;
	}
	else 
	{
		
		BpTreeNode* p = root;
	
		map <double, BpTreeNode*> ::iterator it;
		/*���� ���ͷ� ó��*/
		if (searchDataNode(key)->getDataMap()->find(key) != searchDataNode(key)->getDataMap()->end()) 
		{
			
			searchDataNode(key)->getDataMap()->find(key)->second.push_back(make_pair(pSto->getStockID(), pSto));
			sort(searchDataNode(key)->getDataMap()->find(key)->second.begin(), searchDataNode(key)->getDataMap()->find(key)->second.end());
			return;
		}
		
			
		
		while (p->getMostLeftChild() != NULL) //p : data node
		{
			for (it = p->getIndexMap()->begin(); it != p->getIndexMap()->end(); it++)
			{
				if (key < p->getIndexMap()->begin()->first)
				{
					p = p->getMostLeftChild();
					break;
				}
				if (key < it->first) //key�� ���̰��� ���ͷ����� ũ�� p�� ���� ����Ű�� �����ͷ�
				{
					it--;
					p = it->second;
					break;
				}
				
				if (key > it->first&&++it == p->getIndexMap()->end())
				{
					it--;
					p = it->second;
					break;
				}
				else
					it--;
			}
			
		}

		p->insertDataMap(key, value); // ���� insert�� �Ѵ�.
		
		if (exceedDataNode(p) == true) //��ģ ���->���ø�
		{
			splitDataNode(p);

		}
		
		
		
	}
	BpTreeNode* pDataNode = searchDataNode(key);	// seach data node with key
	
	map<double, vector<pair<int, StockData*> > > *m = pDataNode->getDataMap();

	/*
	�ڵ� �ۼ�  (����: if(m->find(key) == m->end()))
	*/
}

BpTreeNode* BpTree::searchDataNode(double n) //�� ��ġ ã�� �Լ�
{


	BpTreeNode* pCur = root;
	map<double, BpTreeNode*>::iterator itIndex;

	while(pCur->getMostLeftChild() != NULL) //������ ������
	{ 
		itIndex = pCur->getIndexMap()->begin(); //index�� pCur�� ó��

		if(n < itIndex->first) //���� ã�� ���� index���� ������
		{ 
			pCur = pCur->getMostLeftChild(); //��������ڽ����� ������
		}
		else{
			while(true) 
			{
				itIndex++; //����� ���� ���ͷ��� �̵�
				if(itIndex == pCur->getIndexMap()->end() || n < itIndex->first) //�� ��� �̰ų� index������ �Է��� �۴�
				{
					itIndex--; //���� index��
					pCur = itIndex->second; //�ڽ����� ������
					break;
				}
			}
		}
	}

	return pCur;
}

void BpTree::splitDataNode(BpTreeNode* pDataNode){
	
	
	int splitPosition_data = ceil((order-1)/2.0) + 1; //map���� split position ��° �����͸� �ε����� ������. 
	
	BpTreeNode* newDataNode = new BpTreeDataNode;
	map <double, vector<pair<int, StockData*> > > ::iterator up_data;
	map <double, vector<pair<int, StockData*> > > ::iterator it;
	int i = 1;
	/*�ø� ������ ã��*/
	for (it = pDataNode->getDataMap()->begin(); it != pDataNode->getDataMap()->end(); it++)
	{
		if (i == splitPosition_data)
		{
			up_data = it;
		}
		if (i >= splitPosition_data)
		{
			newDataNode->insertDataMap(it->first, it->second);

		}
		i++;
	}
	map <double, vector<pair<int, StockData*> > > *m;
	m = pDataNode->getDataMap();
	
	newDataNode->setNext(pDataNode->getNext());
	if(pDataNode->getNext()!=NULL)
		pDataNode->getNext()->setPrev(newDataNode);
	newDataNode->setPrev(pDataNode);
	pDataNode->setNext(newDataNode);


	//�ڸ� ��(up_data) �������� �ڸ������� �����ʿ� �ִ� �� ��� �ٸ� ��Ƽ������ �̵����Ѿ���
	if (pDataNode->getParent() == NULL)//p data��尡 root�϶�
	{
		BpTreeNode* newindexnode = new BpTreeIndexNode;
		newindexnode->insertIndexMap(up_data->first, newDataNode);
		m->erase(pDataNode->getDataMap()->find(up_data->first), pDataNode->getDataMap()->end());
		pDataNode->setParent(newindexnode);
		newDataNode->setParent(newindexnode);
		newindexnode->setMostLeftChild(pDataNode);
		root = newindexnode;
		
		return;
	}
	else //root�� �ƴҶ�
	{
		pDataNode->getParent()->insertIndexMap(up_data->first, newDataNode);

		BpTreeNode * indexNode = pDataNode->getParent();
		m = pDataNode->getDataMap();
		m->erase(pDataNode->getDataMap()->find(up_data->first), pDataNode->getDataMap()->end());
		newDataNode->setParent(pDataNode->getParent()); //�����ؾ��Ҽ��ִ�.!
		if (exceedIndexNode(indexNode) == true) // ���� �ε��� ��嵵 ���ƴٸ�
		{
			splitIndexNode(indexNode); //���ø��� ����

		}
		
	}
	
	
}

void BpTree::splitIndexNode(BpTreeNode* pIndexNode){
	
	
	int splitPosition_index = ceil(order/2.0);  //map���� split position ��° �����͸� �θ���� �̵��Ѵ�.
	if (pIndexNode == root)
	{
		BpTreeNode* newroot = new BpTreeIndexNode; //���� �ö� ��Ʈ
		BpTreeNode* newIndexNode = new BpTreeIndexNode; //���� �и��� �ε��� ���
		map <double, BpTreeNode*> ::iterator up_data;
		map <double, BpTreeNode*>  ::iterator it;
		int i = 1;
		for (it = pIndexNode->getIndexMap()->begin(); it != pIndexNode->getIndexMap()->end(); it++)
		{
			if (i == splitPosition_index)
			{
				up_data = it;
			}
			if (i > splitPosition_index)
			{
				newIndexNode->insertIndexMap(it->first, it->second);
				it->second->setParent(newIndexNode);
			}
			i++;
		}
		
		newIndexNode->setMostLeftChild(up_data->second);
		up_data->second->setParent(newIndexNode);
		up_data->second = newIndexNode;//�����ͼ���
		newroot->insertIndexMap(up_data->first, up_data->second);

		map <double, BpTreeNode*>* mm = pIndexNode->getIndexMap();
		mm->erase(pIndexNode->getIndexMap()->find(up_data->first), pIndexNode->getIndexMap()->end());

		root = newroot;
		root->setParent(NULL);
		newroot->setMostLeftChild(pIndexNode);
		pIndexNode->setParent(newroot);
		newIndexNode->setParent(newroot);
		return;
	}

	/*��Ʈ�� �ƴ� ���*/
	BpTreeNode* newindexnode = new BpTreeIndexNode;
	map <double, BpTreeNode*> ::iterator up_data;
	map <double, BpTreeNode*>  ::iterator it;
	int i = 1;
	for (it = pIndexNode->getIndexMap()->begin(); it != pIndexNode->getIndexMap()->end(); it++)
	{
		if (i == splitPosition_index)
		{
			up_data = it;
		}
		if (i > splitPosition_index)
		{
			newindexnode->insertIndexMap(it->first, it->second);
			pIndexNode->getIndexMap()->find(it->first)->second->setParent(newindexnode);

		}
		i++;
	}
	newindexnode->setMostLeftChild(up_data->second);
	pIndexNode->getIndexMap()->find(up_data->first)->second->setParent(newindexnode);

	up_data->second = newindexnode;//�����ͼ���

	map <double, BpTreeNode*>* mm = pIndexNode->getIndexMap();
	pIndexNode->getParent()->insertIndexMap(up_data->first, up_data->second); //�ø� ������ ����
	mm->erase(pIndexNode->getIndexMap()->find(up_data->first), pIndexNode->getIndexMap()->end());

	newindexnode->setParent(pIndexNode->getParent());

	if (exceedIndexNode(pIndexNode->getParent()) == true)
		splitIndexNode(pIndexNode->getParent());
	
	
}

bool BpTree::exceedDataNode(BpTreeNode* pDataNode){
	
	map <double, vector<pair<int, StockData*> > > *m = pDataNode->getDataMap();

	if(m->size() > order-1)		return true; //�̸� �׳� ������ �ְ� ->�����Ͱ� ���ƴ� -> ���ø��ض�.
	else								return false;
}

bool BpTree::exceedIndexNode(BpTreeNode* pIndexNode){
	
	map <double, BpTreeNode*>* m = pIndexNode->getIndexMap();
	
	if(m->size() > order-1)		return true;
	else								return false;
}



bool BpTree::Print(){

	if (root == NULL)
		return false;
	BpTreeNode * p = root;
	map <double, BpTreeNode*> ::iterator it;

	/*���� ������ ���� ���� �̵�*/
	while (p->getMostLeftChild() != NULL) //p : data node
	{
		for (it = p->getIndexMap()->begin(); it != p->getIndexMap()->end(); it++)
		{
			if (++it == p->getIndexMap()->end())
			{
				it--;
				p = it->second;
				break;
			}
			else
				it--;
		}
	}

	p = it->second;
	
	*fout << "==================== PRINT ===================== " << endl;
	while(p != NULL)
	{
		moving_and_print(p);
		p = p->getPrev();
	} 
	*fout << "==============================================" << endl<<endl;
	return true;
}



bool BpTree::Search(double a, double b){
	if (root == NULL)
		return false;
	BpTreeNode * p = root;
	map <double, BpTreeNode*> ::iterator it;

	/*���� ������ ���� ���� �̵�*/
	while (p->getMostLeftChild() != NULL) //p : data node
	{
		for (it = p->getIndexMap()->begin(); it != p->getIndexMap()->end(); it++)
		{
			if (++it == p->getIndexMap()->end())
			{
				it--;
				p = it->second;
				break;
			}
			else
				it--;
		}
	}

	p = it->second;

	int check = 0;
	while (p != NULL)
	{
		moving_and_print2(p,a,b,check);
		p = p->getPrev();
	}
	if (check > 0)
	{
		*fout << "=====================" << endl << endl;
		return true;
	}
	else
		return false;

	
}

void BpTree::moving_and_print2(BpTreeNode * p, double a, double b,int &check)
{
	map <double, vector<pair<int, StockData*> > > ::iterator iter;
	/*���� ����� ���� ������ : iter*/
	for (iter = p->getDataMap()->begin(); iter != p->getDataMap()->end(); iter++)
	{
		if (++iter == p->getDataMap()->end())
		{
			iter--;
			break;
		}
		else
			iter--;
	}
	for (int i = 0; i<p->getDataMap()->size(); i++)
	{
		if (iter->first >= a&&iter->first <= b)
		{
			vector<pair<int, StockData*> > ::iterator Vector = iter->second.begin();
			while (Vector != iter->second.end())
			{
				if (check == 0)
				{
					*fout << "======= SEARCH ======= " << endl;
					check++;
				}
				printStockInfo(Vector->second);
				Vector++;
			}
		}
		iter--;
	}
}
void BpTree::moving_and_print(BpTreeNode * p)
{
	map <double, vector<pair<int, StockData*> > > ::iterator iter;
	/*���� ����� ���� ������ : iter*/
	for (iter = p->getDataMap()->begin(); iter != p->getDataMap()->end(); iter++)
	{
		if (++iter == p->getDataMap()->end())
		{
			iter--;
			break;
		}
		else
			iter--;
	}
	for (int i = 0; i<p->getDataMap()->size(); i++)
	{
		vector<pair<int, StockData*> > ::iterator Vector = iter->second.begin();
		while (Vector != iter->second.end())
		{
			printStockInfo(Vector->second);
			Vector++;
		}
		iter--;
	}
}

void BpTree::printStockInfo(StockData* pStockData)
{
	*fout << pStockData->getStockID() << " " << pStockData->getName() << " ";
	fout->setf(ios::fixed);
	fout->precision(2);
	*fout << pStockData->getEarning() << endl;
	fout->unsetf(ios::fixed);
	*fout << "�ð�: " << pStockData->getOpening_Price() << endl;
	*fout << "����: " << pStockData->getClosing_Price() << endl;
	*fout << "�ŷ���: " << pStockData->getVolume() << endl;
	*fout << "���ͷ�: ";
	fout->setf(ios::fixed);
	fout->precision(2);
	*fout << pStockData->getEarning() << endl << endl << endl;
	fout->unsetf(ios::fixed);
}
