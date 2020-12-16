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
void BST<K, E>::Insert(const pair<K, E> &thePair) //���ο� ��� �Է� 
{
	TreeNode<pair<K, E>> *p = root, *pp = NULL; //pp�� p�� �θ�
	while (p) 
	{
		pp = p;
		if (thePair.first < p->data.first) //�� �Է�key�� p����������
			p = p->leftChild;//�����ڽ����� �̵�
		else if (thePair.first > p->data.first) //p���� ũ��
			p = p->rightChild; //�������ڽ����� �̵�
		else //p�� �� �Է��� key�� ������
		{
		p->data.second = thePair.second; //�� �Է����� element ��ü
			return;
		}
	} //loop �� ���� ���� pp�� �������, p�� null
	p = new TreeNode<pair<K, E>> (thePair); //�Ҵ� �� ����
	if (root != NULL)
	{
		if (thePair.first < pp->data.first) //�θ𺸴� ������
			pp->leftChild = p; //����
		else
			pp->rightChild = p;
	}
	else root = p;
}



template <class K, class E>
void BST <K, E>::Delete(const K &k)
{
	TreeNode <pair< K, E >> *p = root, *q = 0;
	while (p && k != p->data.first)//p�� ��Ʈ�� �ƴϰ� key�� p�� key�� �ٸ� ����
	{
		q = p; //q�� p �θ�
		if (k < p->data.first) //p�� key�� key���� ũ��
			p = p->leftChild; //�����ڽ�(������)�̵�
		else p = p->rightChild;
	}
	if (p == 0) return;
	if (p->leftChild == 0 && p->rightChild == 0) //p�� �������
	{
		if (q == 0) //p�� ��Ʈ�϶�
			root = 0; //������ ���̴� ��Ʈ ����
		else if (q->leftChild == p)
			q->leftChild = 0; //�����ڽ� ����
		else
			q->rightChild = 0; //�������ڽ� ����
		delete p; //p ����.
	}
	if (p->leftChild == 0) //p���� �������ڽĸ� ������
	{
		if (q == 0)//p�� ��Ʈ�� ��
			root = p->rightChild;
		else if (q->leftChild == p) //p�� �����ڽ��̸�
			q->leftChild = p->leftChild; //���ʿ� p�� �����ڽ� ��ġ
		else //p�� �������ڽ�
			q->rightChild = p->rightChild; //�����ʿ� p�� �����ڽ� ��ġ
		delete p; //p����
	}
	if (p->rightChild == 0)//p�� ���ʸ� ������
	{
		if (q == 0)
			root = p->leftChild;
		else if (q->leftChild == p)
			q->leftChild = p->leftChild;
		else
			q->rightChild = p->rightChild;
		delete p;
	}


	//p���� ���� ������ ������ ��
	TreeNode<pair<K, E>> *prevprev = p, *prev = p->rightChild,
		*curr = p->rightChild->leftChild;

	/*���� ���� �� ã�� ����.*/
	while (curr)
	{
		prevprev = prev;
		prev = curr; //�� ���� �� prev�� p�� �����ʿ��� ���� ���� ��.
		curr = curr->leftChild;//�� ���� �� curr�� 0
	}

	p->data = prev->data;//prev�� p�� ������ �ٲ�->���� prev�� ����.

	if (prevprev == p) //loop�� ���� �ʾ����� prev�� ������ �ڽ��̹Ƿ�.
		prevprev->rightChild = prev->rightChild;
	else //loop�� ���� �� �� prev�� prevprev�� �����ڽ��̹Ƿ�.
		prevprev->leftChild = prev->rightChild;
	delete prev; //prev ����.
}



