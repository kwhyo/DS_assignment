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
	//tree내에 중첩 클래스 InorderIterator선언
	class InorderIterator
	{
	private:
		stack <TreeNode<T>*> s;
		TreeNode <T> *currentNode;
	public:
		/* 루트 받아와서 초기화 */
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
		/* stack채우기 */
		 while (currentNode != NULL)
		 {
			 s.push(currentNode);
			 currentNode = currentNode->getLeft();
		 }
		 if (s.empty() != NULL) return 0;

		 /*현재 top을 current로*/
		 currentNode = s.top();
		 s.pop();

		 /*return할 내용 저장*/
		 T temp = currentNode->getData();
		 /* 새로운 current */
		 currentNode = currentNode->getRight();

		 return temp;
	}
	

template<class T>
void Tree<T>::NonrecInorder()
{
	stack<TreeNode<T>*> s;
	TreeNode<T>*currentNode = root;

	while (1) {
		/*stack 채우기*/
		while (currentNode != NULL) {
			s.push(currentNode);
			currentNode = currentNode->getLeft();
		}

		if (s.empty()) return;
		currentNode = s.top();
		s.pop();
		/* 현재 노드 출력 */
		Visit(currentNode);
		currentNode = currentNode->getRight();

	}
}
template<class T>
void Tree<T>::LevelOrder()
{
	queue<TreeNode<T>*> q; 
	TreeNode<T> * currentNode = root;
	/*큐 채우기 및 현재노드 지정*/
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
	/* 이동 후 출력 */
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
		/* 출력 후 이동 */
		Visit(currentNode);
		PreOrder(currentNode->getLeft());
		PreOrder(currentNode->getRight());
	}
}

template<class T>
void Tree<T>::Visit(TreeNode<T> *currentNode)
{
	//노드의 data 출력
	cout << currentNode->getData() << " ";
}
