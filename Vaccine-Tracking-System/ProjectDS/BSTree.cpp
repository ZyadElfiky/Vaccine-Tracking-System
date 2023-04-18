#include "BSTree.h"
#include<fstream>
#include <iostream>
#include <assert.h>
#include <string>
using namespace std;
Node::Node()
{
	left = right = NULL;
}

Node::Node(User user)
{
	usr = user;
	left = right = NULL;
}

BSTree::BSTree(void)
{
	root = NULL;
}

void BSTree::insert_User(User user)
{
	assert(!contains(user.ID));
	Node* tmp = root;
	Node* new_User = new Node(user);
	if (root == 0)
		root = new_User;
	else
	{
		while (1)
		{
			if (tmp->usr.ID > user.ID)
				if (tmp->left == 0)
				{
					tmp->left = new_User;
					break;
				}
				else
					tmp = tmp->left;
			else
				if (tmp->right == 0)
				{
					tmp->right = new_User;
					break;
				}
				else
					tmp = tmp->right;
		}
	}
	if (!new_User->usr.first_dose)
		FirstWaitingList.Enqueue(new_User->usr);
	else if (!new_User->usr.second_dose)
		SecondWaitingList.Enqueue(new_User->usr);
	increase_stats(new_User->usr.Gender, new_User->usr.first_dose, new_User->usr.second_dose);
}

void BSTree::Register()
{
	system("cls");
	cout << "\t\t**************************************************************************\n\n";
	cout << "\t\t                      WELCOME  TO  REGISTER  PAGE                               \n\n";
	cout << "\t\t**************************************************************************\n\n";
	User usr;
	int vaccinatedStatus;
	
	cout << "\nEnter the first name :\n";
	cin >> usr.F_name;
	cout << "\nEnter the last name  :\n";
	cin >> usr.L_name;
	cout << "\nEnter the ID         :\n";
	cin >> usr.ID;
	while (contains(usr.ID))
	{
		cout << "This ID Already Exist!!.\n";
		cout << "\nEnter the ID         :\n";
		cin >> usr.ID;
	}
		
	cout << "\nEnter the password    :\n";
	cin >> usr.password;
	cout << "\nEnter the E-mail      :\n";
	cin >> usr.Email;
	cout << "\nEnter the Country     :\n";
	cin >> usr.country;
	cout << "\nEnter the Governorate :\n";
	cin >> usr.governorate;
	cout << "\nEnter the Gender      :\n";
	cin >> usr.Gender;
	cout << "\nENTER THE AGE        :\n";
	cin >> usr.age;
	cout << "\nAre you already vaccinated?\n" << endl;
	cout << "1) Yes" << "\n" << "2) No\n" << endl;
	cin >> vaccinatedStatus;
	if (vaccinatedStatus == 1 || vaccinatedStatus == 2)
		usr.first_dose = (vaccinatedStatus == 1) ? true : false;
	if (usr.first_dose)
	{
		cout << "\nDid you take the second dose?\n" << endl;
		cout << "1) Yes" << "\n" << "2) No\n" << endl;
		cin >> vaccinatedStatus;
		if (vaccinatedStatus == 1 || vaccinatedStatus == 2)
			usr.second_dose = (vaccinatedStatus == 1) ? true : false;
	}
	insert_User(usr);
	cout << "\nRegistration Sucessful\n";
	system("cls");
	
}

Node*BSTree::finde_User(ll ID)
{
	Node* tmp = root;
	while (tmp != 0 && tmp->usr.ID != ID)
	{
		if (tmp->usr.ID > ID)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}
	return tmp;
}

bool BSTree::contains(ll ID)
{
	Node* tmp = finde_User(ID);
	return (tmp != NULL);
}

void BSTree::Login()
{
	string user_name, pass;
	ll ID;
	system("cls");
	cout << "\nENTER YOUR ID     : ";
	cin >> ID;
	cout << "ENTER YOUR PASSWORD : ";
	cin >> pass;
	if (check_Admin_Login(ID, pass))
	{
		cout << endl << "Hallo Admin." << endl;
		Admin_job();
		system("cls");
	}
	else if (check_Login(ID, pass))

	{
		Node* tmp = finde_User(ID);
		user_name = tmp->usr.F_name;
		cout << "\nHello: " << user_name << "\nLOGIN SUCESS\nWe're glad that you're here.\nThanks for logging in\n";
		while (true)
		{
			Display_User_Info(ID);
			int choice;
			cout << "1) Update " << "    " << "2)Remove" << "    " << "3)Logout" << endl;
			cin >> choice;
			if (choice == 1)
				Update(ID);
			else if (choice == 2) {
				Remove(ID);
				break;
			}
			else if (choice == 3) {
				system("cls");
				break;
			}
			system("cls");
		}
	}
	else
	{
		cout << "\nLOGIN ERROR\nPlease check your username and password\n";
		return;
	}

}

void BSTree::inOrderToSave(Node* start)
{
	if (start != NULL)
	{
		inOrderToSave(start->left);
		User usr = start->usr;
		ofstream reg ("Data.txt", ios::app);
		reg << usr.F_name<< ' '<< usr.L_name << ' ' << usr.Email << ' ' << usr.password << ' ' << usr.ID << ' ' << usr.country << ' ' << usr.governorate << ' ' << usr.Gender << ' ' << usr.age << ' ' << usr.first_dose << ' ' << usr.second_dose << endl;
		inOrderToSave(start->right);
	}
}

void BSTree::Save()
{
	inOrderToSave(root);
}

void BSTree::inOrder(Node* start)
{
	if (start != NULL)
	{
		inOrder(start->left);
		cout << "----------------------------------------------------------------------------" << endl;
		cout << "  First Name           : " << start->usr.F_name << endl;
		cout << "  Last Name            : " << start->usr.L_name << endl;
		cout << "  ID                   : " << start->usr.ID << endl;
		cout << "  Password             : " << start->usr.password << endl;
		cout << "  Email                : " << start->usr.Email << endl;
		cout << "  Age                  : " << start->usr.age << endl;
		cout << "  Gender               : " << start->usr.Gender << endl;
		cout << "  Country              : " << start->usr.country << endl;
		cout << "  Governorate          : " << start->usr.governorate << endl;
		cout << "  First Vaccine        : " << start->usr.first_dose << endl;
		cout << "  Second Vaccine       : " << start->usr.second_dose << endl;
		cout << "----------------------------------------------------------------------------" << endl;
		inOrder(start->right);
	}
}

void BSTree::Display_All()
{
	cout << "#----------------------------ALL USERS INFO--------------------------------#" << endl;
	inOrder(root);
}

void BSTree::Display_User_Info(ll ID)
{
	Node* user = finde_User(ID);
	if(user == NULL)
		cout << "User Not Found." << endl;
	else
	{
		cout << "------------------------------------------------------" << "\n";
		cout << "  First Name           : " << user->usr.F_name << endl;
		cout << "  Last Name            : " << user->usr.L_name << endl;
		cout << "  ID                   : " << user->usr.ID << endl;
		cout << "  Password             : " << user->usr.password << endl;
		cout << "  Email                : " << user->usr.Email << endl;
		cout << "  Age                  : " << user->usr.age << endl;
		cout << "  Gender               : " << user->usr.Gender << endl;
		cout << "  Country              : " << user->usr.country << endl;
		cout << "  Governorate          : " << user->usr.governorate << endl;
		cout << "  First Vaccine        : " << user->usr.first_dose << endl;
		cout << "  Second Vaccine       : " << user->usr.second_dose << endl;
		cout << "------------------------------------------------------" << "\n";
	}
}

Node* BSTree::find_Parent(ll ID)
{
	Node* a, * parent;
	a = root;
	parent = NULL;
	while ((a!= NULL )&& (a->usr.ID!=ID))
	{
		parent = a;
		(a->usr.ID > ID) ? a = a->left : a = a->right;
	}
	return parent;
}

void BSTree::Remove(ll ID)
{
	assert(contains(ID));
	Node* node_to_be_deleted = finde_User(ID);
	if (node_to_be_deleted == NULL)
		cout << "User Not Found." << endl;
	else
	{

		if ((node_to_be_deleted->left == 0) && (node_to_be_deleted->right == 0)) 
		{
			if (node_to_be_deleted == root)
				root = 0;
			else
			{
				Node* parent = find_Parent(ID);
				(ID < parent->usr.ID) ? parent->left = 0 : parent->right = 0;
			}
			delete node_to_be_deleted;
		}
		else if ((node_to_be_deleted->left == 0) && (node_to_be_deleted->right != 0))
		{
			Node* parent = find_Parent(ID);
			if (node_to_be_deleted == root)
				root = node_to_be_deleted->right;
			else
			{
				(ID < parent->usr.ID) ? parent->left = node_to_be_deleted->right : parent->right = node_to_be_deleted->right;

			}
			delete node_to_be_deleted;
		}
		else if ((node_to_be_deleted->left != 0) && (node_to_be_deleted->right == 0))
		{
			Node* parent = find_Parent(ID);
			if (node_to_be_deleted == root)
				root = node_to_be_deleted->left;
			else
			{
				(ID < parent->usr.ID) ? parent->left = node_to_be_deleted->left : parent->right = node_to_be_deleted->left;

			}
			delete node_to_be_deleted;
		}
		else
		{
			Node* minNode = find_min(node_to_be_deleted->right);
			Node* parent = find_Parent(minNode->usr.ID);
			node_to_be_deleted->usr.ID = minNode->usr.ID;

			if (parent == node_to_be_deleted)
				parent->right = minNode->right;
			else
				parent->left = minNode->right;
			delete minNode;
		}
	}
}

Node* BSTree::find_min(Node* start)
{
	Node* minNode = start;
	while (minNode->left != NULL)
		minNode = minNode->left;

	return minNode;
}

bool BSTree::check_Login(ll ID, string pass)
{
	Node* tmp = finde_User(ID);
	if (tmp == NULL)
		return false;
	else if (tmp->usr.password == pass)
		return true;
	else
		return false;
}

bool BSTree::check_Admin_Login(ll ID, string pass)
{
	return((ID == 2020 && pass == "123") || (ID == 2021 && pass == "1234") || (ID == 2023 && pass == "12345"));
}

void BSTree::Update(ll ID)
{
	Node* tmp = finde_User(ID);
	if(tmp==NULL)
		cout << "User Not Found." << endl;
	else {
		decreasing_stats(tmp->usr.Gender, tmp->usr.first_dose, tmp->usr.second_dose);
		cout << "Do You Want To Enter Any Update To Your Information ?" << endl;
		cout << "1) Yes" << "\n" << "2) No" << endl;
		int ask;
		cin >> ask;
		while (ask == 1)
		{
			int choice;
			cout << "Enter choice : " << endl;
			cout << "1) Name" << endl;
			cout << "2) Email" << endl;
			cout << "3) Password" << endl;
			cout << "4) Country" << endl;
			cout << "5) Governorate" << endl;
			cout << "6) Gender" << endl;
			cout << "7) Age" << endl;
			cout << "8) Vaccine Status" << endl;
			cin >> choice;

			if (choice == 1)
			{
				cout << "Enter New First Name : ";
				cin >> tmp->usr.F_name;
				cout << "Enter New Last Name : ";
				cin >> tmp->usr.L_name;
			}
			else if (choice == 2)
			{
				cout << "Enter New Email : ";
				cin >> tmp->usr.Email;
			}
			else if (choice == 3)
			{
				cout << "Enter New Password : ";
				cin >> tmp->usr.password;

			}
			else if (choice == 4)
			{
				cout << "Enter New Country : ";
				cin >> tmp->usr.country;

			}
			else if (choice == 5)
			{
				cout << "Enter New Governorate : ";
				cin >> tmp->usr.governorate;

			}
			else if (choice == 6)
			{
				int genderChoice;
				cout << "1) Male" << "\n" << "2) Female" << endl;
				cin >> genderChoice;
				tmp->usr.Gender = (genderChoice == 1) ? "male" : "female";

			}
			else if (choice == 7)
			{
				cout << "Enter New Age : ";
				cin >> tmp->usr.age;

			}
			else if (choice == 8)
			{
				int vaccinatedStatus;
				cout << "Are you already vaccinated?" << endl;
				cout << "1) Yes" << "\n" << "2) No" << endl;
				cin >> vaccinatedStatus;
				if (vaccinatedStatus == 1 || vaccinatedStatus == 2) {
					tmp->usr.first_dose = (vaccinatedStatus == 1) ? true : false;
					(tmp->usr.first_dose) ? FirstWaitingList.leave_list(tmp->usr.ID) : FirstWaitingList.Enqueue(tmp->usr);
				}
				if (tmp->usr.first_dose)
				{
					cout << "Did you take the second dose?" << endl;
					cout << "1) Yes" << "\n" << "2) No" << endl;
					cin >> vaccinatedStatus;
					if (vaccinatedStatus == 1 || vaccinatedStatus == 2) {
						tmp->usr.second_dose = (vaccinatedStatus == 1) ? true : false;
						(tmp->usr.second_dose) ? SecondWaitingList.leave_list(tmp->usr.ID) : SecondWaitingList.Enqueue(tmp->usr);
					}
				}
				else
				{
					tmp->usr.second_dose = false;
					SecondWaitingList.leave_list(tmp->usr.ID);
				}
			}
			cout << "Any Other Update ?" << endl;
			cout << "1) Yes" << "\n" << "2) No" << endl;
			cin >> ask;
		}
		increase_stats(tmp->usr.Gender, tmp->usr.first_dose, tmp->usr.second_dose);
	}
}

void BSTree ::Admin_job() {
	int select, id_num,choice;
	cout << "Please enter :" << endl;
	cout << "1) View a certain record." << endl;
	cout << "2) Delete a certain record." << endl;
	cout << "3) View all records." << endl;
	cout << "4) View the first waiting list." << endl;
	cout << "5) View the second waiting list." << endl;
	cout << "6) Delete all records." << endl;
	cout << "7) Logout." << endl;
	cin >> select;
	while (select == 1 || select == 2 || select == 3 || select==4 || select==5 || select==6 || select==7)
	{
		if (select == 1) {
			cout << "Please enter the ID number : ";
			cin >> id_num;
			Display_User_Info(id_num);
		}

		else if (select == 2) {
			cout << "Please enter the ID number : ";
			cin >> id_num;
			Node* tmp = finde_User(id_num);
			if (tmp == NULL)
				cout << "User Not Found." << endl;
			else
			{
				decreasing_stats(tmp->usr.Gender, tmp->usr.first_dose, tmp->usr.second_dose);
				Remove(id_num);
				cout << "The User Has Been Removed." << endl;
			}

		}

		else if (select == 3)
		{
			Display_All();
			statistics();
		}

		else if (select == 4) {
			FirstWaitingList.Display();
			if (!FirstWaitingList.isEmpty()) {
				cout << "Do you want to remove the first one?" << endl;
				cout << "1) YES." << endl;
				cout << "2) NO." << endl;
				int removeChoice; cin >> removeChoice;
				while (removeChoice == 1 )
				{
					if (FirstWaitingList.isEmpty())
					{
						cout << "Firt Waiting List Is Empty.\n";
						break;
					}
					else
					{

						ll usrID = FirstWaitingList.Dequeue();
						Node* the_User = finde_User(usrID);
						decreasing_stats(the_User->usr.Gender, the_User->usr.first_dose, the_User->usr.second_dose);
						the_User->usr.first_dose = true;
						SecondWaitingList.Enqueue(the_User->usr);
						increase_stats(the_User->usr.Gender, the_User->usr.first_dose, the_User->usr.second_dose);
						Display_User_Info(usrID);
						cout << "The user has been removed from the list." << endl;
						cout << "Do you want to remove another one?" << endl;
						cout << "1) YES." << endl;
						cout << "2) NO." << endl;
						cin >> removeChoice;
					}
				}
			}
		}

		else if (select == 5) {
			SecondWaitingList.Display();
			if (!SecondWaitingList.isEmpty()) {
				cout << "Do you want to remove the first one?" << endl;
				cout << "1) YES." << endl;
				cout << "2) NO." << endl;
				int removeChoice; cin >> removeChoice;
				while (removeChoice == 1 )
				{
					if (SecondWaitingList.isEmpty())
					{
						cout << "Second Waiting List Is Empty.\n";
						break;
					}
					else
					{


						ll usrID = SecondWaitingList.Dequeue();
						Node* the_User = finde_User(usrID);
						decreasing_stats(the_User->usr.Gender, the_User->usr.first_dose, the_User->usr.second_dose);
						the_User->usr.second_dose = true;
						increase_stats(the_User->usr.Gender, the_User->usr.first_dose, the_User->usr.second_dose);
						Display_User_Info(usrID);
						cout << "The user has been removed from the list." << endl;
						cout << "Do you want to remove another one?" << endl;
						cout << "1) YES." << endl;
						cout << "2) NO." << endl;
						cin >> removeChoice;
					}
				}
			}
		}
		else if (select == 6)
			deleteBST(root);
		else if (select == 7)
			return;

		cout << "Do You Want To Take Any Action ?" << endl;
		cout << "1) Yes." << endl;
		cout << "2) No." << endl;
		cin >> choice;
		if (choice==1) {
			//system("cls");
			cout << "Please enter :" << endl;
			cout << "1) View a certain record." << endl;
			cout << "2) Delete a certain record." << endl;
			cout << "3) View all records." << endl;
			cout << "4) View the first waiting list." << endl;
			cout << "5) View the second waiting list." << endl;
			cout << "6) Delete all records." << endl;
			cout << "7) Logout." << endl;
			cin >> select;
		}
		else return;
	}
	cout << "Wrong Choice." << endl;
	Admin_job();
}

void BSTree ::statistics() {
	cout << endl;
	cout << "#----------------------------SYSTEM STATISTICS--------------------------------#" << endl;
	cout << "The number of users who took the first dose:\t\t" << (stats[1] / stats[0]) * 100 << "%" << endl;
	cout << "The number of users who took the second dose:\t\t" << (stats[2] / stats[0]) * 100 << "%" << endl;
	cout << "The number of males who took the first dose:\t\t" << (stats[5] / stats[0]) * 100 << "%" << endl;
	cout << "The number of females who took the first dose:\t\t" << (stats[6] / stats[0]) * 100 << "%" << endl;
	cout << "The number of males who took the second dose:\t\t" << (stats[8] / stats[0]) * 100 << "%" << endl;
	cout << "The number of females who took the second dose:\t\t" << (stats[7] / stats[0]) * 100 << "%" << endl;
	cout << "The number of males who took the vaccine:\t\t" << (stats[3] / stats[0]) * 100 << "%" << endl;
	cout << "The number of females who took the vaccine:\t\t" << (stats[4] / stats[0]) * 100 << "%" << endl;
	cout << "#-----------------------------------------------------------------------------#" << endl;
	cout << endl;
}

void BSTree ::decreasing_stats(string gender, bool first, bool second)
{
	stats[0]--;
	if (first)
	{
		stats[1] -= 1;
	}
	if (second) {
		stats[2] -= 1;
	}
	if (gender == "male") {
		stats[3] -= 1;
	}
	if (gender == "female") {
		stats[4] -= 1;
	}
	if (first && gender == "male") {
		stats[5] -= 1;
	}
	if (first && gender == "female") {
		stats[6] -= 1;
	}
	if (second && gender == "female") {
		stats[7] -= 1;
	}
	if (second && gender == "male") {
		stats[8] -= 1;
	}
}

void BSTree::increase_stats(string gender, bool first, bool second) {
	stats[0]++;
	if (first)
	{
		stats[1] += 1;
	}
	if (second) {
		stats[2] += 1;
	}
	if (gender == "male") {
		stats[3] += 1;
	}
	if (gender == "female") {
		stats[4] += 1;
	}
	if (first && gender == "male") {
		stats[5] += 1;
	}
	if (first && gender == "female") {
		stats[6] += 1;
	}
	if (second && gender == "female") {
		stats[7] += 1;
	}
	if (second && gender == "male") {
		stats[8] += 1;
	}
}

void BSTree::load_file() {
	User usr;
	ifstream input("Data.txt");
	while ((input >> usr.F_name >> usr.L_name >> usr.Email >> usr.password >> usr.ID >> usr.country >> usr.governorate >> usr.Gender >> usr.age >> usr.first_dose >> usr.second_dose))
	{
		insert_User(usr);
	}
	input.close();
}

void BSTree::deleteBST(Node* node)
{
	if (!node)
		return;

	Node* currentTreeNode = node;
	Node* leftTreeNode = node->left;
	Node* rightTreeNode = node->right;
	delete(currentTreeNode);
	deleteBST(leftTreeNode);
	deleteBST(rightTreeNode);
}

BSTree::~BSTree(void)
{
	ofstream ofs;
	ofs.open("Data.txt", ofstream::out | ofstream::trunc);
	ofs.close();
	Save();
	deleteBST(root);
}

