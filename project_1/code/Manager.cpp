#include "Manager.h"
#include <stdlib.h>

using namespace std;

Manager::Manager()	//constructor
{
	LinkedList* creatll= new LinkedList();
	ll = creatll;
	NumberBST* creatbst = new NumberBST();
	bst = creatbst;
	Queue* createQueue = new Queue();
	queue = createQueue;


}


Manager::~Manager()//destructor
{
}

void Manager::run(const char * command)
{
	ifstream fin;
	char* cmd;
	

	fin.open(command);
	ofstream flog;
	flog.open("log.txt", ios::app);

	cmd = new char[40];
	
	int numbers[10] = { 7,3,9,1,0,2,5,4,6,8 };
	for (int i = 0; i < 10; i++) 
	{
		NumberNode * newnode = new NumberNode();
		newnode->SetNumber(numbers[i]);
		bst->Insert(newnode);
	}
	char* parameter;
	char* next_parameter;
	while (!fin.eof())
	{
		
		fin.getline(cmd, 40);
		char * tmp = strtok_s(cmd, " ", &parameter);

		if (strcmp(tmp, "LOAD") == 0){
			if (LOAD()) printSuccessCode("LOAD");
			else printErrorCode(100);
		}
		else if (strcmp(tmp, "ADD") == 0) {
			if (ADD()) printSuccessCode("ADD");
			else printErrorCode(200);
		}
		else if (strcmp(tmp, "MOVE") == 0) {
			int intpara = atoi(parameter);
			if (MOVE(intpara)) printSuccessCode("MOVE");
			else printErrorCode(300);
		}
		else if (strcmp(tmp, "SAVE") == 0) {
			if (SAVE()) printSuccessCode("SAVE");
			else printErrorCode(400);
		}
		else if (strcmp(tmp, "SEARCH") == 0) {
			int intpara = atoi(parameter);
			if (SEARCH(intpara)) ;
			else printErrorCode(500);
		}
		else if (strcmp(tmp, "PRINT") == 0) {
			if (PRINT(parameter)) ;
			else printErrorCode(600);
		}
		else if (strcmp(tmp, "COMPLETE") == 0) {
			int intpara = atoi(parameter);
			if (COMPLETE(intpara)) printSuccessCode("COMPLETE");
			else printErrorCode(700);
		}
		else if (strcmp(tmp, "EXIT") == 0) {
			EXIT();
			printSuccessCode("EXIT");
		}
		else	printErrorCode(0);
		
	}
	cmd = NULL;
	delete cmd;

	fin.close();
	flog.close();
	return;
}

bool Manager::LOAD()
{
	int fail_check = 0;
	/* Total List */
	if (ll->pHead == NULL) 
	{
		
		ifstream total_list;
		total_list.open("total_list_car.txt");
		if (total_list.is_open() == true)
		{
			char* ptr = new char[100];
			char * text1 = new char[100];
			while (1)
			{
				char* line = new char[40];
				total_list.getline(line, 40);
				if (line[0] == NULL)
				{
					line = NULL;
					delete line;
					break;
				}
				char* tnum = strtok_s(line, "	", &text1);
				int intnum = atoi(tnum);
				char* tname = strtok_s(text1, "	", &line);
				char* tstate = strtok_s(line, "	", &text1);
				char cState = tstate[0];

				CarNode* NewCar = new CarNode();
				NewCar->SetcarNum(intnum);
				NewCar->SetcarOwner(tname);
				NewCar->Setstate(cState);
				ll->Insert(NewCar);
				line = NULL;
				delete line;
			}
			text1 = NULL;
			ptr = NULL;
			delete text1;
			delete ptr;
			total_list.close();
		}
		else
		{
			total_list.close();
			fail_check++;
		}
	}
	else
	{
		fail_check++;
	}

	/* Event List */
	if (bst->getCnt() == 0)
	{
		
		ifstream event_list;
		event_list.open("event_list_car.txt");
		if (event_list.is_open() == true)
		{
			char* ptr = new char[100];
			char * text1 = new char[100];
			while (1)
			{
				char* line = new char[40];
				event_list.getline(line, 40);
				if (line[0] == NULL)
				{
					line = NULL;
					delete line;
					break;
				}
				char* tnum = strtok_s(line, "	", &text1);
				int intnum = atoi(tnum);
				char* tname = strtok_s(text1, "	", &line);
				char* tstate = strtok_s(line, "	", &text1);
				char cState = tstate[0];

				char charnum = tnum[0];
				int Num = charnum - '0';

				CarNode* NewCar = new CarNode();
				NewCar->SetcarNum(intnum);
				NewCar->SetcarOwner(tname);
				NewCar->Setstate(cState);

				NumberNode* searching_number = bst->Search(Num);
				searching_number->GetBST()->Insert(NewCar);
				bst->setCnt(1);

				line = NULL;
				delete line;
			}
			text1 = NULL;
			ptr = NULL;
			delete text1;
			delete ptr;
		}
		else 
		{
			event_list.close();
			fail_check++;
		}
	
	}
	else
	{
		fail_check++;
	}

	/* Complete List */
	if (queue->pHead == NULL)
	{
		
		ifstream complete_list;
		complete_list.open("complete_list_car.txt");
		if (complete_list.is_open() == true)
		{
			char* ptr = new char[100];
			char * text1 = new char[100];
			while (1)
			{
				char* line = new char[40];
				complete_list.getline(line, 40);
				if (line[0] == NULL)
				{
					line = NULL;
					delete line;
					break;
				}
				char* tnum = strtok_s(line, "	", &text1);
				int intnum = atoi(tnum);
				char* tname = strtok_s(text1, "	", &line);
				char* tstate = strtok_s(line, "	", &text1);
				char cState = tstate[0];

				CarNode* NewCar = new CarNode();
				NewCar->SetcarNum(intnum);
				NewCar->SetcarOwner(tname);
				NewCar->Setstate(cState);
				queue->Push(NewCar);
				line = NULL;
				delete line;
			}
			text1 = NULL;
			ptr = NULL;
			delete text1;
			delete ptr;
		}
		
		complete_list.close();
	}
	else
		fail_check++;

	if (fail_check > 0)
		return false;
	else
		return true;
}

bool Manager::ADD()
{
	ifstream fin;

	fin.open("car.txt");
	if (!fin.is_open()) // If the file does not open
	{
		return false;
	}
	
	char* ptr = new char[100];
	char * text1 = new char[100];
	while (1)
	{
		char* line = new char[40];
		fin.getline(line, 40);
		if (line[0] == NULL)
		{
			line = NULL;
			delete line;
			break;
		}
		char* tnum = strtok_s(line, "	", &text1);
		int intnum = atoi(tnum);
		char* tname = strtok_s(text1, "	", &line);
		char* tstate = strtok_s(line, "	", &text1);
		char cState = tstate[0];

		CarNode* NewCar = new CarNode();
		NewCar->SetcarNum(intnum);
		NewCar->SetcarOwner(tname);
		NewCar->Setstate(cState);
		ll->Insert(NewCar);
		line = NULL;
		delete line;
	}
	text1 = NULL;
	ptr = NULL;
	delete text1;
	delete ptr;

	fin.close();
	
	return true;
}

bool Manager::MOVE(int parameter)
{
	CarNode* temp = ll->pHead;
	int check = 0;
	int before_check = 0;
	if (temp == NULL)
		return false;
	if (parameter + bst->getCnt() > 100)
		return false;
	
	/*Check if there is enough data left by the user.*/
	int total_Y=0;
	CarNode* temp_total_y = ll->pHead;
	while (temp_total_y->GetNext() != NULL)
	{
		if (temp_total_y->Getstate() == 'Y')
			total_Y++;
		temp_total_y = temp_total_y->GetNext();
	}
	if (total_Y < parameter)
		return false;

	/*Run the move operation*/
		while (temp!= NULL)
		{
			if (temp->Getstate() == 'Y')
			{
				/*Get the first number of car*/
				char stringnum[10];
				int i = temp->GetcarNum();
				sprintf(stringnum, "%d", i);
				char charnum = stringnum[0];
				int Num = charnum - '0';
				NumberNode* searching_number = bst->Search(Num);

				/*Create a car bst at the number bst, insert the node.*/
				
				searching_number->GetBST()->Insert(temp);
				bst->setCnt(1);
				check++;
			}
			int deleteCar = temp->GetcarNum();
			if (check == parameter) {
				ll->Delete(deleteCar);
				break;
			}
				
			temp = temp->GetNext();

			if (before_check < check)
			{
				ll->Delete(deleteCar);
				before_check++;
			}
			
		}
	return true;
}

bool Manager::SAVE()
{
	int fail_check = 0;
	if (ll->Save() == false)
	{
		fail_check++;
	}
	if (queue->Save() == false)
	{
		fail_check++;
	}
	if (bst->Save() == false)
	{
		fail_check++;
	}

	if (fail_check > 0)
		return false;
	else
		return true;

}

bool Manager::SEARCH(int parameter)
{
	ofstream flog;
	flog.open("log.txt", ios::app);

	if (ll->Search(parameter) != NULL)
	{
		CarNode* temp = ll->Search(parameter);
		flog << "======== SEARCH ========" << endl;
		flog << temp->GetcarNum()<<" "<<temp->GetcarOwner()<<" "<<temp->Getstate() << endl;
		flog << "=======================" << endl << endl;
		return true;
	}
	else if (queue->Search(parameter) != NULL)
	{
		CarNode* temp = queue->Search(parameter);
		flog << "======== SEARCH ========" << endl;
		flog << temp->GetcarNum() << " " << temp->GetcarOwner() << " " << temp->Getstate() << endl;
		flog << "=======================" << endl << endl;
		return true;
	}
	else
	{
		char stringnum[10];
		int i = parameter;
		sprintf(stringnum, "%d", i);
		char charnum = stringnum[0];
		int Num = charnum - '0';
		NumberNode* searching_number = bst->Search(Num);
		CarNode* searching_car = searching_number->GetBST()->Search(parameter);
		if (searching_car != NULL)
		{
			CarNode* temp = searching_car;
			flog << "======== SEARCH ========" << endl;
			flog << temp->GetcarNum() << " " << temp->GetcarOwner() << " " << temp->Getstate() << endl;
			flog << "=======================" << endl << endl;
			return true;
		}
	}
	flog.close();
	return false;
}

bool Manager::PRINT(char * parameter)
{
	char*next_para;
	char*para = strtok_s(parameter, " ",& next_para);
	
	if (strcmp(parameter, "TOTAL_LIST") == 0)
	{
		if (ll->Print() == true)
			return true;
		else
			return false;
	}
	else if (strcmp(parameter, "COMPLETE_LIST") == 0)
	{
		if (queue->Print() == true)
			return true;
		else
			return false;
	}
	else if (strcmp(parameter, "EVENT_LIST") == 0)
	{
		if (bst->Print(next_para) == true)
		{
			return true;
		}
		else
			return false;
		
	}
	
}



bool Manager::COMPLETE(int parameter)
{
	/*Get the first number of car*/
	char stringnum[10];
	int i = parameter;
	sprintf(stringnum, "%d", i);
	char charnum = stringnum[0];
	int Num = charnum - '0';
	NumberNode* searching_number = bst->Search(Num);
	CarNode* searching_car=searching_number->GetBST()->Delete(parameter);
	bst->setCnt(-1);
	if (searching_car == NULL)
		return false;
	searching_car->Setstate('C');
	queue->Push(searching_car);
	
	return true;
}

void Manager::EXIT()
{
	delete ll;
	delete bst;
	delete queue;
	
}

void Manager::printErrorCode(int n) {				//ERROR CODE PRINT 
	ofstream flog;
	flog.open("log.txt", ios::app);
	flog << "======== ERROR ========" << endl;
	flog << n << endl;
	flog << "=======================" << endl << endl;
	flog.close();
}

void Manager::printSuccessCode(const char * cmdname) {//SUCCESS CODE PRINT 
	ofstream flog;
	flog.open("log.txt", ios::app);
	flog << "======== "<<cmdname<<" ========" << endl;
	flog << "Success" << endl;
	flog << "=======================" << endl << endl;
	flog.close();
}