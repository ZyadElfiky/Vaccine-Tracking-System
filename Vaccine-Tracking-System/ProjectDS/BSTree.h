#include<string>
#include"LinkedQueue.h"
#define ll long long
using namespace std;

class Node
{
public:
	User usr;
	Node* left, * right;
	Node();
	Node(User user);
};


class BSTree
{
	Node* root;
	LinkedQueue FirstWaitingList;
	LinkedQueue SecondWaitingList;
	float stats[9] = { 0 };

public:
	BSTree(void);
	void insert_User(User user);
	void Register();
	Node* finde_User(ll ID);
	void Login();
	void Display_User_Info(ll ID);
	void Update(ll);
	void Remove(ll ID);
	bool check_Login(ll ID, string pass);
	bool check_Admin_Login(ll ID,string pass);
	void Admin_job();
	void load_file();
	~BSTree(void);

private:
	bool contains(ll ID);
	void inOrder(Node* start);
	void Save();
	void inOrderToSave(Node* start);
	void Display_All(void);
	Node* find_Parent(ll ID);
	Node* find_min(Node* start);
	void statistics();
	void decreasing_stats(string gender, bool first, bool second);
	void increase_stats(string, bool, bool);
	void deleteBST(Node* node);
	
	};

