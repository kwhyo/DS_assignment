#include "CarBST.h"
#include <queue>
#include <stack>


CarBST::CarBST()//constructor
{
	root = NULL;
}


CarBST::~CarBST()//destructor
{
	while (root != NULL)
	{
		CarNode*temp = root;
		Delete(temp->GetcarNum());
		delete temp;
	}
}

void CarBST::Insert(CarNode * node)
{
	CarNode* p = root ,*pp = NULL;

	while (p)
	{
		pp = p;
		if (node->GetcarNum() < p->GetcarNum())
			p = p->GetLeft();
		else if (node->GetcarNum() > p->GetcarNum())
			p = p->GetRight();
	}
	if (root != NULL)
	{
		if (node->GetcarNum() < pp->GetcarNum())
			pp->SetLeft(node);
		else
			pp->SetRight(node);
	}
	else
		root = node;
	
}

CarNode * CarBST::Delete(int num)
{
	if (Search(num) == NULL)
		return NULL;
	CarNode* p = root, *pp = NULL;
	while (p!=NULL && num != p->GetcarNum())
	{
		pp = p;
		if (num < p->GetcarNum())
			p = p->GetLeft();
		else
			p = p->GetRight();
	}
	if (p == NULL)
		return NULL;

	// p is leaf
	if (p->GetLeft() ==	NULL && p->GetRight() == NULL)
	{
		if (pp == NULL) //p is root
		{
			root = NULL;
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
	if (p->GetLeft() == NULL)
	{
		if (pp == NULL) {
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
	if (p->GetRight() == NULL) 
	{
		if (pp == NULL) 
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
	CarNode* maxChild_parent = p;
	CarNode* maxChild = p->GetLeft();
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
		if(maxChild_parent->GetLeft() == maxChild)
			maxChild_parent->SetLeft(NULL);
		else
			maxChild_parent->SetRight(NULL);
	}
	CarNode* temp = p;
	int tempCarnum = p->GetcarNum();
	char* tempCarowner = p->GetcarOwner();
	char tempCarstate = p->Getstate();
	p->SetcarNum(maxChild->GetcarNum()); 
	p->SetcarOwner(maxChild->GetcarOwner());
	p->Setstate(maxChild->Getstate());

	maxChild->SetcarNum(tempCarnum);
	maxChild->SetcarOwner(tempCarowner);
	maxChild->Setstate(tempCarstate);

	return maxChild;
}

CarNode * CarBST::Search(int num)
{
	CarNode *curr = root;
	while (curr)
	{
		if (num < curr->GetcarNum())
			curr = curr->GetLeft();
		else if (num > curr->GetcarNum())
			curr = curr->GetRight();
		else
			return curr;
	}
	return NULL;

}

bool CarBST::Print(const char * order)
{
	if (strcmp(order, "R_PRE")==0)
	{
		if (root == NULL)
			return false;
		else
		{ 
			Preorder(root);
			return true;
		}
	}
	else if (strcmp(order, "R_IN") == 0)
	{
		if (root == NULL)
			return false;
		else
		{
			Inorder(root);
			return true;
		}
	}
	else if (strcmp(order, "R_POST") == 0)
	{
		if (root == NULL)
			return false;
		else
		{
			Postorder(root);
			return true;
		}
	}
	else if (strcmp(order, "I_IN") == 0)
	{
		if (root == NULL)
			return false;
		else
		{
			Inorder_I(root);
			return true;
		}
	}
	else if (strcmp(order, "I_PRE") == 0)
	{
		if (root == NULL)
			return false;
		else
		{
			Preorder_I(root);
			return true;
		}
	}
	else if (strcmp(order, "I_POST") == 0)
	{
		if (root == NULL)
			return false;
		else
		{
			Postorder_I(root);
			return true;
		}
	}
	else if (strcmp(order, "I_LEVEL") == 0)
	{
		if (root == NULL)
			return false;
		else
		{
			Levelorder(root);
			return true;
		}
	}
}

bool CarBST::Save(ofstream &event_list)
{
	if (root == NULL)
		return false;
	else
	{
		stack<CarNode*> s;
		s.push(root);
		while (s.empty() == false)
		{
			CarNode * temp = s.top();
			event_list << temp->GetcarNum() << "	" << temp->GetcarOwner() << "	" << temp->Getstate() << endl;
			s.pop();
			if (temp->GetRight() != NULL)
				s.push(temp->GetRight());
			if (temp->GetLeft() != NULL)
				s.push(temp->GetLeft());
		}
	}
}


void CarBST::visit(CarNode * node)
{
	ofstream flog;
	flog.open("log.txt", ios::app);
	flog << node->GetcarNum() << "	" << node->GetcarOwner() << "	" << node->Getstate() << endl;
	flog.close();
}

void CarBST::Inorder(CarNode * node)
{
	if (node != NULL)
	{
		Inorder(node->GetLeft());
		visit(node);
		Inorder(node->GetRight());

	}
}

void CarBST::Preorder(CarNode * node)
{	
	if (node != NULL)
	{
		visit(node);
		Preorder(node->GetLeft());
		Preorder(node->GetRight());
	}
}

void CarBST::Postorder(CarNode * node)
{
	if (node != NULL)
	{
		Postorder(node->GetLeft());
		Postorder(node->GetRight());
		visit(node);
	}
}

void CarBST::Inorder_I(CarNode * node)
{
	stack<CarNode*> s;
	CarNode * temp = node;

	while (temp != NULL || s.empty() == false)
	{
		while (temp != NULL)
		{
			s.push(temp);
			temp = temp->GetLeft();
		}
		temp = s.top();
		s.pop();
		visit(temp);
		temp = temp->GetRight();
	}
}

void CarBST::Preorder_I(CarNode * node)
{
	stack<CarNode*> s;
	s.push(node);

	while (s.empty() == false)
	{
		CarNode * temp = s.top();
		visit(temp);
		s.pop();
		if (temp->GetRight() != NULL)
			s.push(temp->GetRight());
		if (temp->GetLeft() != NULL)
			s.push(temp->GetLeft());

	}
}

void CarBST::Postorder_I(CarNode * node)
{
	stack<CarNode*> s1, s2;
	s1.push(node);
	CarNode* temp;

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
		visit(temp);
	}
}

void CarBST::Levelorder(CarNode * node)
{
	queue<CarNode*> q;
	CarNode* temp;
	q.push(node);
	while (q.empty() == false)
	{
		temp = q.front();
		visit(temp);
		q.pop();
		if (temp->GetLeft() != NULL)
			q.push(temp->GetLeft());
		if (temp->GetRight() != NULL)
			q.push(temp->GetRight());
	}
}
