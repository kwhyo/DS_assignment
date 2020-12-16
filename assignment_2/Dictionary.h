#pragma once
#include <iostream>;
using namespace std;
template <class K, class E>
class Dictionary
{
public:
	virtual pair<K, E>*Get(const K&) const = 0; 
	virtual void Insert(const pair<K, E>&) = 0; 
	virtual void Delete(const K&) = 0;
	
	Dictionary() { ; }
	~Dictionary() { ; }
};
template <class T>
class TreeNode
{
public:
	T data;
	TreeNode<T> *leftChild;
	TreeNode<T> *rightChild;
	TreeNode(T temp) { data=temp, leftChild=NULL, rightChild=NULL; }

};

template <class K, class E>
class BST: public Dictionary <K,E>
{
public: 
	BST() {
		root = NULL;
	}
	TreeNode<pair<K, E>> *root;

	pair<K, E>* Get(const K&k) const;
	pair<K, E>* Get(TreeNode<pair<K, E> >*p, const K& k)const;

	pair<K, E>* Iterative_Get(const K& k);
	void Insert(const pair<K, E>&thePair);
	void Delete(const K& k);
	void InOrder(TreeNode<pair<K, E>> *t);
};



template <class K, class E>
void BST<K, E>::InOrder(TreeNode<pair<K, E>> *t)
{
	if (t != NULL) 
	{ InOrder(t->leftChild);   
	  cout<<"["<< t->data.first<<","<<t->data.second<<"]";
	  InOrder(t->rightChild); 
	}
}

template <class K, class E> 
pair<K, E>* BST<K, E>::Get(const K& k) const 
{  return Get(root, k); }

template <class K, class E> 
pair<K, E>* BST<K, E>::Get(TreeNode<pair<K, E> >*p, const K& k)const
{ 
	if (p == NULL) 
	{
		cout << "The node you searched does not exist."<<endl;
		return NULL; }
	if(k < p->data.first) return Get(p->leftChild, k);
	if(k > p->data.first) return Get(p->rightChild, k);
	return &p->data; 
}

template <class K, class E>
pair<K, E>* BST<K, E>::Iterative_Get(const K& k)
{
	TreeNode <pair<K, E>> *currentNode = root;
	while (currentNode)
	{
		if (k < currentNode->data.first)
			currentNode = currentNode->leftChild;
		else if (k > currentNode->data.first)
			currentNode = currentNode->rightChild;
		else
			return &currentNode->data;
	}
	
	cout << "The node you searched does not exist." << endl;
	return 0;
}

template<class K,class E>
void BST<K, E>::Insert(const pair<K, E> &thePair) //새로운 페어 입력 
{
	TreeNode<pair<K, E>> *p = root, *pp = NULL; //pp는 p의 부모
	while (p) 
	{
		pp = p;
		if (thePair.first < p->data.first) //새 입력key가 p보다작을때
			p = p->leftChild;//왼쪽자식으로 이동
		else if (thePair.first > p->data.first) //p보다 크면
			p = p->rightChild; //오른쪽자식으로 이동
		else //p와 새 입력의 key가 같으면
		{
		p->data.second = thePair.second; //새 입력으로 element 교체
			return;
		}
	} //loop 다 돌고 나면 pp는 리프노드, p는 null
	p = new TreeNode<pair<K, E>> (thePair); //할당 및 생성
	if (root != NULL)
	{
		if (thePair.first < pp->data.first) //부모보다 작으면
			pp->leftChild = p; //왼쪽
		else
			pp->rightChild = p;
	}
	else root = p;
}



template <class K, class E>
void BST <K, E>::Delete(const K &k)
{
	TreeNode <pair< K, E >> *p = root, *q = 0;
	while (p && k != p->data.first)//p가 루트가 아니고 key와 p의 key가 다른 동안
	{
		q = p; //q는 p 부모
		if (k < p->data.first) //p의 key가 key보다 크면
			p = p->leftChild; //왼쪽자식(더작은)이동
		else p = p->rightChild;
	}
	if (p == 0) return;
	if (p->leftChild == 0 && p->rightChild == 0) //p가 리프노드
	{
		if (q == 0) //p가 루트일때
			root = 0; //삭제할 것이니 루트 지움
		else if (q->leftChild == p)
			q->leftChild = 0; //왼쪽자식 지움
		else
			q->rightChild = 0; //오른쪽자식 지움
		delete p; //p 삭제.
	}
	if (p->leftChild == 0) //p에게 오른쪽자식만 있을때
	{
		if (q == 0)//p가 루트일 때
			root = p->rightChild;
		else if (q->leftChild == p) //p가 왼쪽자식이면
			q->leftChild = p->leftChild; //왼쪽에 p의 왼쪽자식 배치
		else //p가 오른쪽자식
			q->rightChild = p->rightChild; //오른쪽에 p의 오른자식 배치
		delete p; //p삭제
	}
	if (p->rightChild == 0)//p가 왼쪽만 있을때
	{
		if (q == 0)
			root = p->leftChild;
		else if (q->leftChild == p)
			q->leftChild = p->leftChild;
		else
			q->rightChild = p->rightChild;
		delete p;
	}


	//p에게 왼쪽 오른쪽 다있을 때
	TreeNode<pair<K, E>> *prevprev = p, *prev = p->rightChild,
		*curr = p->rightChild->leftChild;

	/*가장 작은 값 찾기 위함.*/
	while (curr)
	{
		prevprev = prev;
		prev = curr; //다 돌고난 후 prev는 p의 오른쪽에서 가장 작은 값.
		curr = curr->leftChild;//다 돌고난 후 curr은 0
	}

	p->data = prev->data;//prev와 p의 데이터 바꿈->이후 prev를 삭제.

	if (prevprev == p) //loop를 돌지 않았으면 prev는 오른쪽 자식이므로.
		prevprev->rightChild = prev->rightChild;
	else //loop를 돌고 난 후 prev는 prevprev의 왼쪽자식이므로.
		prevprev->leftChild = prev->rightChild;
	delete prev; //prev 삭제.
}



