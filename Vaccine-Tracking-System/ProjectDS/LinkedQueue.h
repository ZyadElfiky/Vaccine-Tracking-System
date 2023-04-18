#pragma once
#include <string>
using namespace std;

class User {
public:
	string F_name, L_name, Email, password, country, Gender, governorate;
	long long ID;
	int age, doses;
	bool first_dose = false, second_dose = false;
};


class QNode {
public:
	User user;
	QNode* next;
	QNode();
	QNode(User user);
};

class LinkedQueue {
	QNode* front, * rear;
public:
	LinkedQueue(void);
	void Enqueue(User);
	void Display();
	bool isEmpty();
	long long Dequeue();
	void leave_list(long long);
};
