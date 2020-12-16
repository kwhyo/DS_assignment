#include "Tree.h"

int main() {

	/*9���� ��� ����*/
	TreeNode<char> A('A'), B('B'), C('C'), D('D'), E('E'),
		division('/'), multiplication1('*'), multiplication2('*'), addition('+');

	/*tree����, root����*/
	Tree<char> tree(&addition);

	/* ��ȯ�� Ŭ����  ����, tree�� root�� currentNode�� ����*/
	Tree<char>::InorderIterator	lnorder(tree.getRoot());

	/* Ʈ�� ���� */
	addition.setLeft(&multiplication1);
	addition.setRight(&E);
	multiplication1.setLeft(&multiplication2);
	multiplication1.setRight(&D);
	multiplication2.setLeft(&division);
	multiplication2.setRight(&C);
	division.setLeft(&A);
	division.setRight(&B);

	/* ���� ��ȸ */
	cout << "Preorder: ";
	tree.PreOrder();
	cout << endl;

	/*���� ��ȸ*/
	cout << "Postorder: ";
	tree.PostOrder();
	cout << endl;

	/*���ȯ ���� ��ȸ*/
	cout << "NonrecInorder: ";
	tree.NonrecInorder();
	cout << endl;

	/* �����ݺ��� Ȱ���� ���� ��ȸ�� ��� */
	cout << "Inorder_Iterator: ";
	do
	{
		cout << lnorder.Next() << " ";
	} while (lnorder.retrunSize() != 0); //stack�� ����� 0�� �ɶ����� �ݺ�
	cout << lnorder.Next(); //���� �ϳ� ���
	cout << endl;

	/* ���� ���� ��ȸ */
	cout << "Levelorder: ";
	tree.LevelOrder();
	cout << endl;

	return 0;
}