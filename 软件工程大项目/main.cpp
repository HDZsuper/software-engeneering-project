#include<iostream>
#include"Menu.h"
#include <thread>
#include<Windows.h>
Menu m;
void check()
{
	while (1)
	{
		m.CheckAllTasks();
		Sleep(1);
	}
}
int main()
{
	m.LoadAll();

	std::thread t(check);
	m.MainMenu();
}