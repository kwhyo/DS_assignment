#include "NumberBST.h"
#include <queue>
#include <stack>

NumberBST::NumberBST()//constructor
{
	root = NULL;
	nodeCnt = 0;
}


NumberBST::~NumberBST()//destructor
{
	while (root != NULL)
	{
		NumberNode* temp = root;
		delete Delete(temp->GetNumber());
	}
}

void NumberBST::Insert(NumberNode * node)
{
	NumberNode* p = root, *pp = NULL;
	while (p != NULL) // 위치찾기
	{
		pp = p; // pp는 p의 부모
		if (node->GetNumber() < p->GetNumber()) // 숫자비교
			p = p->GetLeft();
		else if (node->GetNumber() > p->GetNumber())
			p = p->GetRight();
		else
			p->SetNumber(node->GetNumber());
	}
	if (root != NULL) //자리에 인서트
	{
		if (node->GetNumber() < pp->GetNumber())
			pp->SetLeft(node);
		else
			pp->SetRight(node);
	}
	else root = node;
	
}

NumberNode * NumberBST::Delete(int num)
{
	if (Search(num) == NULL)
		return NULL;
		NumberNode* p = root, *pp = NULL;
	while (p && num != p->GetNumber())
	{
		pp = p;
		if (num < p->GetNumber())
			p = p->GetLeft();
		else
			p = p->GetRight();
	}
	if (p == 0)
		return NULL;

	// p is leaf
	if (p->GetLeft() == 0 && p->GetRight() == 0)
	{
		if (pp == 0) //p is root
		{
			root = 0;
			return p;
		}
		else if (pp->GetLeft() == p)
		{
			pp->SetLeft(NULL);  //Because it deletes the left child of pp
			return p;
		}
		else
		{
			pp->SetRight(NULL);
			return p;
		}
	}
	//p only has right child
	if (p->GetLeft() == 0)
	{
		if (pp == 0) {
			root = p->GetRight();
			return p;
		}
		else if (pp->GetLeft() == p)
		{
			pp->SetLeft(p->GetRight());
			return p;
		}
		else
		{
			pp->SetRight(p->GetRight());
			return p;
		}
	}
	//p only has left
	if (p->GetRight() == 0)
	{
		if (pp == 0)
		{
			root = p->GetLeft();
			return p;
		}
		else if (pp->GetLeft() == p)
		{
			pp->SetLeft(p->GetLeft());
			return p;
		}
		else
		{
			pp->SetRight(p->GetLeft());
			return p;
		}
	}

	//p has left and right child
	NumberNode* maxChild_parent = p;
	NumberNode* maxChild = p->GetLeft();
	while (maxChild->GetRight() != NULL)
	{
		maxChild_parent = maxChild;
		maxChild = maxChild->GetRight();
	}
	if (maxChild->GetLeft() != NULL)
	{
		if (maxChild_parent->GetLeft() == maxChild)
			maxChild_parent->SetLeft(maxChild->GetLeft());
		else
			maxChild_parent->SetRight(maxChild->GetLeft());
	}
	else
	{
		if (maxChild_parent->GetLeft() == maxChild)
			maxChild_parent->SetLeft(NULL);
		else
			maxChild_parent->SetRight(NULL);
	}
	
	CarBST*tempCarbst = p->GetBST();
	int tempnum = p->GetNumber();
	p->SetNumber(maxChild->GetNumber());
	p->SetBST(maxChild->GetBST());
	

	maxChild->SetNumber(tempnum);
	maxChild->SetBST(tempCarbst);
	return maxChild;
}

NumberNode * NumberBST::Search(int num)
{
	NumberNode *curr = root;
	while (curr)
	{
		if (num < curr->GetNumber())
			curr = curr->GetLeft();
		else if (num > curr->GetNumber())
			curr = curr->GetRight();
		else
			return curr;
	}
}

bool NumberBST::Print(char * BST)
{
	if (root == NULL||getCnt()==0)
		return false;
	ofstream flog;
	flog.open("log.txt", ios::app);
	flog << "======== PRINT ========" << endl;
	flog.close();
	if (strcmp(BST, "R_PRE") == 0)
	{
		Preorder(root);
		return true;
	}
	else if (strcmp(BST, "R_POST") == 0)
	{
		Postorder(root);
		return true;
	}
	else if (strcmp(BST, "R_IN") == 0)
	{
		Inorder(root);
		return true;
	}
	else if (strcmp(BST, "I_IN") == 0)
	{
		Inorder_I(root);
		return true;
	}
	else if (strcmp(BST, "I_PRE") == 0)
	{
		Preorder_I(root);
		return true;
	}
	else if (strcmp(BST, "I_POST") == 0)
	{
		Postorder_I(root);
		return true;
	}
	else if (strcmp(BST, "I_LEVEL") == 0)
	{
		Levelorder(root);
		return true;
	}
	flog << "=======================" << endl << endl;
	flog.close();
}

bool NumberBST::Save()
{
	if (root == NULL || getCnt() == 0)
	{
		return false;
	}
	Save_preorder(root);
	return true;
}

void NumberBST::Save_preorder(NumberNode * node)
{
	stack<NumberNode*> s;
	s.push(node);
	ofstream event_list;
	event_list.open("event_list_car.txt");

	while (s.empty() == false)
	{
		NumberNode * temp = s.top();
		temp->GetBST()->Save(event_list);
		s.pop();
		if (temp->GetRight() != NULL)
			s.push(temp->GetRight());
		if (temp->GetLeft() != NULL)
			s.push(temp->GetLeft());

	}
	event_list.close();
}

void NumberBST::Inorder(NumberNode * node)
{
	if (node != NULL)
	{
		Inorder(node->GetLeft());
		node->GetBST()->Print("R_IN");
		Inorder(node->GetRight());
	}
}

void NumberBST::Preorder(NumberNode * node)
{
	if (node != NULL)
	{
		node->GetBST()->Print("R_PRE");
		Preorder(node->GetLeft());
		Preorder(node->GetRight());
	}
}

void NumberBST::Postorder(NumberNode * node)
{
	if (node != NULL) 
	{
		Postorder(node->GetLeft());
		Postorder(node->GetRight());
		node->GetBST()->Print("R_POST");
	}
	
}

void NumberBST::Inorder_I(NumberNode * node)
{
	stack<NumberNode*> s;
	NumberNode * temp = node;

	while (temp != NULL || s.empty() == false)
	{
		while (temp != NULL)
		{
			s.push(temp);
			temp = temp->GetLeft();
		}
		temp = s.top();
		s.pop();
		temp->GetBST()->Print("I_IN");
		temp = temp->GetRight();
	}
}

void NumberBST::Preorder_I(NumberNode * node)
{
	stack<NumberNode*> s;
	s.push(node);

	while (s.empty() == false)
	{
		NumberNode * temp = s.top();
		temp->GetBST()->Print("I_PRE");
		s.pop();
		if (temp->GetRight() != NULL)
			s.push(temp->GetRight());
		if (temp->GetLeft() != NULL)
			s.push(temp->GetLeft());

	}
}

void NumberBST::Postorder_I(NumberNode * node)
{
	stack<NumberNode*> s1, s2;
	s1.push(node);
	NumberNode* temp;

	while (s1.empty() == false)
	{
		temp = s1.top();
		s2.push(temp);
		s1.pop();
		if (temp->GetLeft() != NULL)
			s1.push(temp->GetLeft());
		if (temp->GetRight() != NULL)
			s1.push(temp->GetRight());
	}
	while (s2.empty() == false)
	{
		temp = s2.top();
		s2.pop();
		temp->GetBST()->Print("I_POST");
	}
}

void NumberBST::Levelorder(NumberNode * node)
{
	queue<NumberNode*> q;
	NumberNode* temp;
	q.push(node);
	while (q.empty() == false)
	{
		temp = q.front();
		temp->GetBST()->Print("I_LEVEL");
		q.pop();
		if (temp->GetLeft() != NULL)
			q.push(temp->GetLeft());
		if (temp->GetRight() != NULL)
			q.push(temp->GetRight());
	}
}


