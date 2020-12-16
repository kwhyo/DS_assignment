#include "Queue.h"
#include <fstream>
Queue::Queue()//constructor
{
	pHead = NULL;
}


Queue::~Queue()//destructor
{
	while (pHead != NULL)
	{
		Pop();
	}
	pHead = NULL;
}

void Queue::Push(CarNode * node)
{
	CarNode* temp = pHead;
	if (temp == NULL)
	{
		pHead = node;
	}
	else
	{
		while (temp->GetNext()!=NULL)
		{
			temp = temp->GetNext();
		}
		temp->SetNext(node);
	}
}

CarNode * Queue::Pop()
{
	CarNode* temp = pHead; 
		
	pHead = temp->GetNext();
	temp->SetNext(NULL);
	delete temp;
	
	return NULL;
}


CarNode * Queue::Search(int num)
{
	CarNode* temp = pHead;

	while (temp != NULL)
	{
		if (temp->GetcarNum() == num)
			return temp;
		temp = temp->GetNext();
	}
	return NULL;
}

bool Queue::Print()
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

bool Queue::Save()
{
	if (pHead == NULL)
		return false;
	CarNode * temp = pHead;
	ofstream complete_list;
	complete_list.open("complete_list_car.txt");
	while (temp != NULL)
	{
		complete_list << temp->GetcarNum() << "	" << temp->GetcarOwner() << "	" << temp->Getstate() << endl;
		temp = temp->GetNext();
	}
	complete_list.close();
	return true;
}
