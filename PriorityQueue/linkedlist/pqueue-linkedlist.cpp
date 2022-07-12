/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"

LinkedListPriorityQueue::LinkedListPriorityQueue() {
	head = NULL;
	nodeCount = 0;
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	Node* curr = head;
	while(true){
		if(curr == NULL) break;
		Node* nextNode = curr->next;
		delete curr;
		curr = nextNode;
	}
}

int LinkedListPriorityQueue::size() {
	return nodeCount;
}

bool LinkedListPriorityQueue::isEmpty() {
	if(head != NULL) return false;
	return true;
}

void LinkedListPriorityQueue::enqueue(string value) {
	nodeCount++;
	if(head == NULL){
		head = new Node(value);
	}else{
		//finds new nodes place in linked list
		//prev keeps linked list's part after which new value should be placed
		//new member will be followed with curr
		Node* curr = head;
		Node* prev = NULL;
		while(true){
			if(curr == NULL){
				Node* newMember = new Node(value);
				prev->next = newMember;
				break;
			} 
			else if(value < curr->data){
				Node* newMember = new Node(value);
				if(prev == NULL){
					newMember->next = curr;
					head = newMember;
				}else{
					prev->next = NULL;
					prev->next = newMember;
					newMember->next = curr;
				}
				break;
			}else{
				prev = curr;
				curr = curr->next;
			}
		}
	}
}

string LinkedListPriorityQueue::peek() {
	if(head == NULL) error("Queue is empty.");
	return head->data;
}

string LinkedListPriorityQueue::dequeueMin() {
	if(head == NULL) error("Queue is empty.");
	nodeCount--;
	string res = head->data;
	Node* next = head->next;
	delete head;
	head = next;
	return res;
}

