#include "Dictionary.h"

int main() {
	BST<int, char> tree;
	
	/*�μ�Ʈ ����*/
	cout << "INSERT [key,element]" << endl;
	cout << "-------------------------------" << endl;
	cout << "insert [1,a]" << endl;
	cout << "insert [5,c]" << endl;
	cout << "insert [7,d]" << endl;
	cout << "insert [2,b]" << endl;
	cout << "-------------------------------" << endl<<endl;

	tree.Insert(pair<int, char>(1, 'a'));
	tree.Insert(pair<int, char>(5, 'c'));
	tree.Insert(pair<int, char>(7, 'd'));
	tree.Insert(pair<int, char>(2, 'b'));
	 
	/*�μ�Ʈ �� ������ȸ*/
	cout << "PRINT [key,element]" << endl;
	cout << "-------------------------------" << endl;
	tree.InOrder(tree.root);
	cout << endl;
	cout << "-------------------------------" << endl<<endl;

	/*���� ����*/
	cout << "DELETE [key]" << endl;
	cout << "-------------------------------" << endl;
	cout << "delete [5]" << endl;
	tree.Delete(5);
	cout << "-------------------------------" << endl<<endl;

	/*��� Ž��*/

	cout << "RECURSIVE_GET [key]" << endl;
	cout << "-------------------------------" << endl;
	cout << "get [5]" << endl;
	if (tree.Get(5) != NULL)
		cout << tree.Get(5)->first <<" is exist."<< endl;
	cout << "get [1]" << endl;
	if (tree.Get(1) != NULL)
		cout << tree.Get(1)->first << " is exist." << endl;
	cout << "-------------------------------" << endl<<endl;

	/*������ȸ*/
	cout << "PRINT [key,element]" << endl;
	cout << "-------------------------------" << endl;
	tree.InOrder(tree.root);
	cout << endl;
	cout << "-------------------------------" << endl << endl;

	/*���ȸ ��� Ž��*/

	cout << "Iterative_GET [key]" << endl;
	cout << "-------------------------------" << endl;
	cout << "get [5]" << endl;
	if (tree.Iterative_Get(5) != NULL)
		cout << tree.Iterative_Get(5)->first << " is exist." << endl;
	cout << "get [1]" << endl;
	if (tree.Iterative_Get(1) != NULL)
		cout << tree.Iterative_Get(1)->first << " is exist." << endl;
	cout << "-------------------------------" << endl << endl;
	return 0;
}