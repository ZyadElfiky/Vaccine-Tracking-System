#include "BSTree.h"
#include<iostream>
#include<string>
#define ll long long
using namespace std;
BSTree Tree;
bool file = true;

int main()
{
	if (file) { Tree.load_file(); file = false; }
	int choice;
	cout << "\t\t**************************************************************************\n\n";
	cout << "\t\t                      WELCOME  TO  LOGIN  PAGE                               \n\n";
	cout << "\t\t**********************        MENU        ********************************\n\n";
	cout << "1) LOGIN\n";
	cout << "2) REGISTER\n";
	cout << "3) Exit    \n";
	cout << "\nEnter your choice : ";
	cin >> choice;
	cout << endl;
	

	switch (choice)
	{
	case 1:
	{
		Tree.Login();
		main();
		break;
	}
	case 2:
	{
		Tree.Register();
		main();
		break;
	}
	case 3:
	{
		cout << "Thanks for using this program\n\n";
		break;
	}
	default:
		system("cls");
		cout << "Wrong Choice Intered\n" << endl;
		main();
	}

}
