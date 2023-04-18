#include <iostream>
#include <string>
#include "LinkedQueue.h"
using namespace std;

QNode::QNode() {
	next = NULL;
}

QNode::QNode(User user) {
	next = NULL;
	this->user = user;
}

LinkedQueue::LinkedQueue() {
	front = rear = NULL;
}

bool LinkedQueue::isEmpty() {
	return (front == NULL);
}

void LinkedQueue::Enqueue(User user) {
	QNode* new_User = new QNode(user);
	if (isEmpty())
		front = rear = new_User;
	else
	{
		rear->next = new_User;
		rear = new_User;
	}

}

void LinkedQueue::Display() {
	if (isEmpty())
	{
		cout << "The waiting list is empty.";
		return;
	}
	else
	{
		cout << endl;
		QNode* tmp = front;
		int i = 1;
		cout << "#----------------------------SYSTEM WAITING LIST--------------------------------#" << endl;
		while (tmp != NULL)
		{
			cout << i << ". " << tmp->user.F_name << " " << tmp->user.L_name << "\t\t" << tmp->user.ID << endl;
			tmp = tmp->next;
			i++;
		}
		cout << "---------------------------------------------------------------------------------" << endl;
		cout << endl;
	}
}

long long LinkedQueue::Dequeue() {
	long long ID = -1;
	if (isEmpty())
		return NULL;
	else {
		QNode* tmp = front;
		front = front->next;
		long long ID = tmp->user.ID;
		delete tmp;
		return ID;
	}
}

void LinkedQueue::leave_list(long long ID) {
	if (isEmpty())
		return;
	else
	{
		QNode* tmp = front;
		QNode* delNode = tmp->next;
		if (tmp->user.ID == ID)
		{
			front = delNode;
			delete tmp;
		}
		else
		{
			while (delNode != NULL)
			{
				if (delNode->user.ID == ID)
				{
					tmp->next = delNode->next;
					delete delNode;
					break;
				}
				else
				{
					tmp = tmp->next;
					delNode = delNode->next;
				}
			}
		}
	}
}