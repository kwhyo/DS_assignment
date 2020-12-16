#include "AVLTree.h"

AVLTree::AVLTree(ofstream* fout){
	root=NULL;
	make_heap(vHeap.begin(), vHeap.end(), compare);
	this->fout = fout;
}

AVLTree::~AVLTree(){

}

bool AVLTree::Insert(StockData* pSto){
	
	AVLNode* pNew = new AVLNode;
	pNew->setSD(pSto);	
	char	*pName = pSto->getName();
	int		rotation = 0;

	if(root == NULL){
		root = pNew;
		return true;
	}
	AVLNode *a = root, *pa = NULL, *p = root, *pp = NULL, *subroot = NULL;

	/*들어갈 위치 탐색*/
	while (p != NULL)
	{
		if (p->getBF() != 0) { a = p; pa = pp; }
		if(strcmp(pName,p->getSD()->getName())<0)
		{
			pp = p; p = p->getLeft();
		}
		else if((strcmp(pName, p->getSD()->getName())>0))
		{
			pp = p; p = p->getRight();
		}
	}

	/* 새 노드 삽입 */
	if (strcmp(pName, pp->getSD()->getName()) < 0)
	{
		pp->setLeft(pNew);
	}
	else pp->setRight(pNew);

	int d;//-1이면 왼쪽

	AVLNode *b, *c;
	/* 새 노드로 바뀐 BF 다시 설정 */
	if (strcmp(pName, a->getSD()->getName()) > 0)
	{
		b = p = a->getRight(); d = -1;
	}
	else { b = p = a->getLeft(); d = 1; }

	while (p != pNew) 
	{
		if(strcmp(pName, p->getSD()->getName()) > 0)
		{
			p->setBF(-1); p = p->getRight();
		}
		else 
		{
			p->setBF(1); p = p->getLeft();
		}
	}
	if(a->getBF()==0||a->getBF()+d==0)
	{
		a->setBF(a->getBF() + d);
		return true;
	}

	/*rotate */
	if (d == 1) 
	{
		if (b->getBF() == 1) //LL
		{
			a->setLeft(b->getRight());
			b->setRight(a);
			a->setBF(0);
			b->setBF(0);
			subroot = b;
		}
		else  //LR
		{
			c = b->getRight();
			b->setRight(c->getLeft());
			a->setLeft(c->getRight());
			c->setLeft(b);
			c->setRight(a);
			switch (c->getBF())
			{
			case 0:
				b->setBF(0);a->setBF(0);
				break;
			case 1: 
				a->setBF(-1); b->setBF(0);
				break;
			case -1:
				b->setBF(1); a->setBF(0);
				break;
			}
			c->setBF(0); subroot = c;
		}
	}
	else 
	{
		if (b->getBF() == -1) //RR
		{
			a->setRight(b->getLeft());
			b->setLeft(a);
			a->setBF(0);
			b->setBF(0);
			subroot = b;
		}
		else  //RL
		{
			c = b->getLeft();
			b->setLeft(c->getRight());
			a->setRight(c->getLeft());
			c->setRight(b);
			c->setLeft(a);
			switch (c->getBF())
			{
			case 0:
				b->setBF(0); a->setBF(0);
				break;
			case 1:
				b->setBF(-1); a->setBF(0);
				break;
			case -1:
				a->setBF(1); b->setBF(0);
				break;
			}
			c->setBF(0); subroot = c;
		}
	}
	if (pa == NULL)root = subroot;
	else if (a == pa->getLeft()) pa->setLeft(subroot);
	else pa->setRight(subroot);
	return true;
}

bool AVLTree::Print(){
	
	if (root == NULL)
		return false;
	stack<AVLNode*> s;	 
	AVLNode * temp = root;
	*fout << "==================== PRINT ===================== " << endl;
	while (temp != NULL || s.empty() == false)
	{
		while (temp != NULL) //Move to the end of the left and push on the stack
		{
			s.push(temp);
			temp = temp->getLeft();
		}
		temp = s.top();
		s.pop();
		printStockInfo(temp->getSD()); //Print the top of the stack.
		temp = temp->getRight(); //Move to the right node.
	}
	*fout << "=============================================="<<endl<<endl;
	return true;
}

bool AVLTree::Search(char* name){
	AVLNode *pCur = root; 
	while (pCur != NULL)
	{
		if (strcmp(name, pCur->getSD()->getName()) < 0)
			pCur = pCur->getLeft();
		else if (strcmp(name, pCur->getSD()->getName()) > 0)
			pCur = pCur->getRight();
		else
			break;
	}
	if (pCur == NULL)
		return false;
	*fout << "======= SEARCH ======= " << endl;
	*fout << "SEARCH_AVL " << pCur->getSD()->getName() << endl;
	*fout << pCur->getSD()->getStockID() << " " << pCur->getSD()->getName()<<" ";
	fout->setf(ios::fixed);
	fout->precision(2);
	*fout << pCur->getSD()->getEarning() << endl;
	fout->unsetf(ios::fixed);
	*fout << "=====================" << endl<<endl;
	StockData* pSD = pCur->getSD(); // pCur은 name을 가진 AVL 노드를 가리킴
	vHeap.push_back( make_pair( make_pair(pSD->getEarning(), pSD->getStockID()), pSD));
	push_heap(vHeap.begin(), vHeap.end(), compare);
	return true;
}

bool AVLTree::Rank(){

	if(vHeap.empty())		return false;

	StockData* pSto;
	*fout << "==================== RANK ===================== " << endl;
	while(!vHeap.empty()){
		pSto = vHeap.front().second;
		pop_heap(vHeap.begin(), vHeap.end(), compare);
		vHeap.pop_back();
		printStockInfo(pSto);
	}
	*fout << "==============================================" << endl<<endl;
	return true;
}

void AVLTree::printStockInfo(StockData* pStockData){
	
	
	*fout << pStockData->getStockID() << " " << pStockData->getName() << " ";
	fout->setf(ios::fixed);
	fout->precision(2);
	*fout << pStockData->getEarning() << endl;
	fout->unsetf(ios::fixed);
	*fout << "시가: " << pStockData->getOpening_Price() << endl;
	*fout<< "종가: " << pStockData->getClosing_Price() << endl;
	*fout << "거래량: " << pStockData->getVolume() << endl;
	*fout << "수익률: ";
	fout->setf(ios::fixed);
	fout->precision(2);
	*fout << pStockData->getEarning() << endl<<endl<<endl;
	fout->unsetf(ios::fixed); 
	
}
