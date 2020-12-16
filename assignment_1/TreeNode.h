#pragma once
template <class T>
class TreeNode
{
private:

	T data;
	TreeNode<T> *leftChild, *rightChild;
		
public:

	//����� ������ �ʱ�ȭ
	TreeNode(T Data) {
		this->data = Data;
		leftChild = rightChild = NULL;
	}
	~TreeNode() { ; }

	/* set, get �Լ��� �¿� �ڽ� ���� �� �������� */
	void setLeft(TreeNode *left) { this->leftChild = left; }
	void setRight(TreeNode *right) { this->rightChild = right; }
	T getData() { return data; }
	TreeNode* getLeft() { return leftChild; }
	TreeNode* getRight() { return rightChild; } 
};

