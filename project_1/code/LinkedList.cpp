#include "LinkedList.h"
#include <fstream>
LinkedList::LinkedList()//constructor
{
	pHead = NULL;
}

LinkedList::~LinkedList()//destructor
{
	while (pHead != NULL) 
	{
		CarNode* temp = pHead;

		pHead = temp->GetNext();
		temp->SetNext(NULL);
		delete temp;

	}
}

void LinkedList::Insert(CarNode* node)
{
	
	if (pHead == NULL) 
	{
		pHead = node;
	}
	else
	{
		CarNode* temp = pHead;
		while (temp->GetNext() != NULL)
		{
			temp = temp->GetNext();
		}
		temp->SetNext(node);
	}
}

CarNode * LinkedList::Search(int car)
{
	CarNode* temp = pHead;
	while (temp!= NULL)
	{
		if (temp->GetcarNum() == car)
			return temp;
		temp = temp->GetNext();
	}
	return NULL;
}

bool LinkedList::Print()
{
	if (pHead == NULL)
		return false;
	CarNode * temp = pHead;
	ofstream flog;
	flog.open("log.txt", ios::app);
	flog << "======== PRINT ========" << endl;
	while (temp != NULL) 
	{
		flog << temp->GetcarNum() << "	" << temp->GetcarOwner() << "	" << temp->Getstate() << endl;
		temp = temp->GetNext();
	}
	flog << "=======================" << endl << endl;
	flog.close();
	return true;
}

bool LinkedList::Save()
{
	if (pHead == NULL)
		return false;
	CarNode * temp = pHead;
	ofstream total_list;
	total_list.open("total_list_car.txt");
	while (temp != NULL)
	{
		total_list << temp->GetcarNum() << "	" << temp->GetcarOwner() << "	" << temp->Getstate() << endl;
		temp = temp->GetNext();
	}
	total_list.close();
	return true;
}

bool LinkedList::Delete(int Carnum)
{
	CarNode* temp = pHead; //찾는 차
	CarNode* front = pHead; // 찾는 차의 앞 노드
	int i = 0;
	/* 차를 찾는 과정*/
	while (temp->GetNext() != NULL)
	{
		if (temp->GetcarNum() == Carnum)
		{
			break; 
		}
		temp = temp->GetNext();
		if (i != 0)
		{
			front = front->GetNext();
		}
		i = 1;
	}

	if (temp != pHead) 
	{
		front->SetNext(temp->GetNext());
		temp->SetNext(NULL);
	}
	else //찾는차가 head일 경우
	{
		pHead = temp->GetNext();
		temp->SetNext(NULL);
	}
	return true;
}
