#include "Tree.h"

int main() {

	/*9개의 노드 선언*/
	TreeNode<char> A('A'), B('B'), C('C'), D('D'), E('E'),
		division('/'), multiplication1('*'), multiplication2('*'), addition('+');

	/*tree선언, root지정*/
	Tree<char> tree(&addition);

	/* 순환자 클래스  선언, tree의 root를 currentNode로 지정*/
	Tree<char>::InorderIterator	lnorder(tree.getRoot());

	/* 트리 구성 */
	addition.setLeft(&multiplication1);
	addition.setRight(&E);
	multiplication1.setLeft(&multiplication2);
	multiplication1.setRight(&D);
	multiplication2.setLeft(&division);
	multiplication2.setRight(&C);
	division.setLeft(&A);
	division.setRight(&B);

	/* 전위 순회 */
	cout << "Preorder: ";
	tree.PreOrder();
	cout << endl;

	/*후위 순회*/
	cout << "Postorder: ";
	tree.PostOrder();
	cout << endl;

	/*비순환 중위 순회*/
	cout << "NonrecInorder: ";
	tree.NonrecInorder();
	cout << endl;

	/* 중위반복자 활용한 중위 순회의 출력 */
	cout << "Inorder_Iterator: ";
	do
	{
		cout << lnorder.Next() << " ";
	} while (lnorder.retrunSize() != 0); //stack의 사이즈가 0이 될때까지 반복
	cout << lnorder.Next(); //남은 하나 출력
	cout << endl;

	/* 레벨 순서 순회 */
	cout << "Levelorder: ";
	tree.LevelOrder();
	cout << endl;

	return 0;
}