#pragma once
template <class T>
class TreeNode
{
private:

	T data;
	TreeNode<T> *leftChild, *rightChild;
		
public:

	//노드의 데이터 초기화
	TreeNode(T Data) {
		this->data = Data;
		leftChild = rightChild = NULL;
	}
	~TreeNode() { ; }

	/* set, get 함수로 좌우 자식 지정 및 가져오기 */
	void setLeft(TreeNode *left) { this->leftChild = left; }
	void setRight(TreeNode *right) { this->rightChild = right; }
	T getData() { return data; }
	TreeNode* getLeft() { return leftChild; }
	TreeNode* getRight() { return rightChild; } 
};

