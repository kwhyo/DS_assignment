#pragma once
#include <iostream>
#include <queue>
#include<stack>
#include "TreeNode.h"
using namespace std;


template <class T>
 class Tree
{
private:
	TreeNode <T> *root;

	void Visit(TreeNode<T> *currentNode);
	void PreOrder(TreeNode<T> *currentNode);
	void PostOrder(TreeNode<T> *currentNode);
	
public:
	//tree���� ��ø Ŭ���� InorderIterator����
	class InorderIterator
	{
	private:
		stack <TreeNode<T>*> s;
		TreeNode <T> *currentNode;
	public:
		/* ��Ʈ �޾ƿͼ� �ʱ�ȭ */
		InorderIterator(TreeNode <T> *rootNode) { currentNode = rootNode; }
		T Next();
		unsigned int retrunSize() { return s.size(); }
		~InorderIterator() { ; }

	};
	TreeNode <T> * getRoot() { return root; }
	Tree() { root = NULL;}
	Tree(TreeNode <T>* root) { this->root = root; }
	~Tree() { ; }
	void PreOrder(){ PreOrder(root); }
	void PostOrder() { PostOrder(root); }
	void LevelOrder();
	void NonrecInorder();
	
};

 template <class T>
 T Tree<T>::InorderIterator::Next()
	{
		/* stackä��� */
		 while (currentNode != NULL)
		 {
			 s.push(currentNode);
			 currentNode = currentNode->getLeft();
		 }
		 if (s.empty() != NULL) return 0;

		 /*���� top�� current��*/
		 currentNode = s.top();
		 s.pop();

		 /*return�� ���� ����*/
		 T temp = currentNode->getData();
		 /* ���ο� current */
		 currentNode = currentNode->getRight();

		 return temp;
	}
	

template<class T>
void Tree<T>::NonrecInorder()
{
	stack<TreeNode<T>*> s;
	TreeNode<T>*currentNode = root;

	while (1) {
		/*stack ä���*/
		while (currentNode != NULL) {
			s.push(currentNode);
			currentNode = currentNode->getLeft();
		}

		if (s.empty()) return;
		currentNode = s.top();
		s.pop();
		/* ���� ��� ��� */
		Visit(currentNode);
		currentNode = currentNode->getRight();

	}
}
template<class T>
void Tree<T>::LevelOrder()
{
	queue<TreeNode<T>*> q; 
	TreeNode<T> * currentNode = root;
	/*ť ä��� �� ������ ����*/
	while (currentNode != NULL) {
		Visit(currentNode);
		if (currentNode->getLeft() != NULL) {
			q.push(currentNode->getLeft());
		}
		if (currentNode->getRight() != NULL) {
			q.push(currentNode->getRight());
		}
		if (q.empty()) return;
		currentNode = q.front();
		q.pop();
	}
	if (currentNode != NULL) {
		PostOrder(currentNode->getLeft());
		PostOrder(currentNode->getRight());
		
	}
}

template<class T>
void Tree<T>::PostOrder(TreeNode<T>* currentNode)
{
	/* �̵� �� ��� */
	if (currentNode != NULL) {
		PostOrder(currentNode->getLeft());
		PostOrder(currentNode->getRight());
		Visit(currentNode);
	}
}


template<class T>
void Tree<T>::PreOrder(TreeNode<T>* currentNode)
{
	if (currentNode != NULL) {
		/* ��� �� �̵� */
		Visit(currentNode);
		PreOrder(currentNode->getLeft());
		PreOrder(currentNode->getRight());
	}
}

template<class T>
void Tree<T>::Visit(TreeNode<T> *currentNode)
{
	//����� data ���
	cout << currentNode->getData() << " ";
}
