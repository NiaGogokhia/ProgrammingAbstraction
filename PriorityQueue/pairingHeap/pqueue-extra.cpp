/*************************************************************
 * File: pqueue-extra.cpp
 *
 * Implementation file for the ExtraPriorityQueue class.  You
 * do not need to implement this class, but we're happy to
 * give you extra credit if you do!
 */
 
#include "pqueue-extra.h"
#include "error.h"
#include "vector.h"
#include<math.h>

ExtraPriorityQueue::ExtraPriorityQueue() {
	queueSize = 0;
	head = NULL;
}

ExtraPriorityQueue::~ExtraPriorityQueue() {
	if(head == NULL)return;
	//deleteNode will recursively remove head node and every node related to it
	deleteNode(head);
}

ExtraPriorityQueue::node* ExtraPriorityQueue::newNode(string value){
	node* newMember = new node;
	newMember->data = value;
	newMember->sibling = NULL;
	newMember->leftChild = NULL;
	return newMember;
}

int ExtraPriorityQueue::size(){
	return queueSize;
}

void ExtraPriorityQueue::deleteNode(node* nodeToRemove){
	if(nodeToRemove == NULL)return;
	//if node does not have child node simply delete
	if(nodeToRemove->leftChild == NULL)delete nodeToRemove;
	//else recursively remove first its child's siblings, then child node and then 
	//starting node itself
	else{
		node* curr = nodeToRemove->leftChild;
		while(curr!=NULL){
			node* nextCurr = curr->sibling;
			deleteNode(curr);
			curr = nextCurr;
		}
		delete nodeToRemove;
	}
}

bool ExtraPriorityQueue::isEmpty() {
	if(queueSize==0)return true;
	return false;
}


void ExtraPriorityQueue::swapNodes(node* newMember, node* head){
	node* newHead;
	if(newMember->data < head->data){
		newHead = newMember;
		newMember = head;
		head = newHead;
	}
}
void ExtraPriorityQueue::enqueue(string value) {
	queueSize++;
	node* newMember = newNode(value);
	if(head == NULL) head = newMember;
	else if(value <= head->data){
		newMember->leftChild = head;
		head = newMember;
	}else{
		node* prevLeftChild = head->leftChild;
		head->leftChild = newMember;
		newMember->sibling = prevLeftChild;
	}
}

string ExtraPriorityQueue::peek() {
	if(size()==0)error("Queue is empty.");
	return head->data;
}

string ExtraPriorityQueue::dequeueMin() {
	if(size()==0)error("Queue is empty.");
	queueSize--;
	string result = head->data;
	if(head->leftChild == NULL) head = NULL;
	else{
		node* tempHead = head->leftChild;
		node* tempHeadSibl = tempHead->sibling;
		while(tempHead != NULL && tempHeadSibl != NULL){
			node* next = tempHeadSibl->sibling;

			if(tempHead->data > tempHeadSibl->data){
				tempHead->sibling = tempHeadSibl->leftChild;
				tempHeadSibl->leftChild = tempHead;
				tempHead = tempHeadSibl;
				tempHead->sibling = next;
			}else{
				tempHeadSibl->sibling = tempHead->leftChild;
				tempHead->leftChild = tempHeadSibl;
				tempHead->sibling = next;
			}
			node* temp = tempHeadSibl;
			tempHeadSibl = next;
		}
		head = tempHead;
	}
	return result;
}