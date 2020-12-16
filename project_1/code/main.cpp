#include "Manager.h"
#include <iostream>
#include <fstream>
using namespace std;
#include <crtdbg.h> 
int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Manager manager;
	manager.run("command.txt");	
	return 0;
}
