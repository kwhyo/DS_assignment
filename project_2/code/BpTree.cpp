#include "BpTree.h"

BpTree::BpTree(ofstream* fout, int order){
	root = NULL;
	this->order = order;  //order는 가리킬 수 있는 자식 수 pointer개수!
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
		pDataNode->insertDataMap(key, value); //수익률, id, data 삽입
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
		/*같은 수익률 처리*/
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
				if (key < it->first) //key가 맵이가진 수익률보다 크면 p는 맵이 가리키는 포인터로
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

		p->insertDataMap(key, value); // 먼저 insert를 한다.
		
		if (exceedDataNode(p) == true) //넘친 경우->스플릿
		{
			splitDataNode(p);

		}
		
		
		
	}
	BpTreeNode* pDataNode = searchDataNode(key);	// seach data node with key
	
	map<double, vector<pair<int, StockData*> > > *m = pDataNode->getDataMap();

	/*
	코드 작성  (참고: if(m->find(key) == m->end()))
	*/
}

BpTreeNode* BpTree::searchDataNode(double n) //들어갈 위치 찾는 함수
{


	BpTreeNode* pCur = root;
	map<double, BpTreeNode*>::iterator itIndex;

	while(pCur->getMostLeftChild() != NULL) //데이터 노드까지
	{ 
		itIndex = pCur->getIndexMap()->begin(); //index는 pCur의 처음

		if(n < itIndex->first) //만약 찾는 수가 index보다 작으면
		{ 
			pCur = pCur->getMostLeftChild(); //가장왼쪽자식으로 내려감
		}
		else{
			while(true) 
			{
				itIndex++; //노드의 다음 수익률로 이동
				if(itIndex == pCur->getIndexMap()->end() || n < itIndex->first) //끝 노드 이거나 index값보다 입력이 작다
				{
					itIndex--; //이전 index의
					pCur = itIndex->second; //자식으로 내려감
					break;
				}
			}
		}
	}

	return pCur;
}

void BpTree::splitDataNode(BpTreeNode* pDataNode){
	
	
	int splitPosition_data = ceil((order-1)/2.0) + 1; //map에서 split position 번째 데이터를 인덱스로 보낸다. 
	
	BpTreeNode* newDataNode = new BpTreeDataNode;
	map <double, vector<pair<int, StockData*> > > ::iterator up_data;
	map <double, vector<pair<int, StockData*> > > ::iterator it;
	int i = 1;
	/*올릴 데이터 찾기*/
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


	//자른 것(up_data) 기준으로 자른것포함 오른쪽에 있는 것 모두 다른 파티션으로 이동시켜야함
	if (pDataNode->getParent() == NULL)//p data노드가 root일때
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
	else //root가 아닐때
	{
		pDataNode->getParent()->insertIndexMap(up_data->first, newDataNode);

		BpTreeNode * indexNode = pDataNode->getParent();
		m = pDataNode->getDataMap();
		m->erase(pDataNode->getDataMap()->find(up_data->first), pDataNode->getDataMap()->end());
		newDataNode->setParent(pDataNode->getParent()); //수정해야할수있다.!
		if (exceedIndexNode(indexNode) == true) // 만약 인덱스 노드도 넘쳤다면
		{
			splitIndexNode(indexNode); //스플릿을 하자

		}
		
	}
	
	
}

void BpTree::splitIndexNode(BpTreeNode* pIndexNode){
	
	
	int splitPosition_index = ceil(order/2.0);  //map에서 split position 번째 데이터를 부모노드로 이동한다.
	if (pIndexNode == root)
	{
		BpTreeNode* newroot = new BpTreeIndexNode; //새로 올라간 루트
		BpTreeNode* newIndexNode = new BpTreeIndexNode; //새로 분리된 인덱스 노드
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
		up_data->second = newIndexNode;//포인터설정
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

	/*루트가 아닐 경우*/
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

	up_data->second = newindexnode;//포인터설정

	map <double, BpTreeNode*>* mm = pIndexNode->getIndexMap();
	pIndexNode->getParent()->insertIndexMap(up_data->first, up_data->second); //올릴 데이터 삽입
	mm->erase(pIndexNode->getIndexMap()->find(up_data->first), pIndexNode->getIndexMap()->end());

	newindexnode->setParent(pIndexNode->getParent());

	if (exceedIndexNode(pIndexNode->getParent()) == true)
		splitIndexNode(pIndexNode->getParent());
	
	
}

bool BpTree::exceedDataNode(BpTreeNode* pDataNode){
	
	map <double, vector<pair<int, StockData*> > > *m = pDataNode->getDataMap();

	if(m->size() > order-1)		return true; //미리 그냥 데이터 넣고 ->데이터가 넘쳤다 -> 스플릿해라.
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

	/*가장 오른쪽 말단 노드로 이동*/
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

	/*가장 오른쪽 말단 노드로 이동*/
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
	/*말단 노드의 가장 오른쪽 : iter*/
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
	/*말단 노드의 가장 오른쪽 : iter*/
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
	*fout << "시가: " << pStockData->getOpening_Price() << endl;
	*fout << "종가: " << pStockData->getClosing_Price() << endl;
	*fout << "거래량: " << pStockData->getVolume() << endl;
	*fout << "수익률: ";
	fout->setf(ios::fixed);
	fout->precision(2);
	*fout << pStockData->getEarning() << endl << endl << endl;
	fout->unsetf(ios::fixed);
}
