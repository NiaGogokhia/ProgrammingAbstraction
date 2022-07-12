/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	head = NULL;
	nodeCount = 0;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	Node* currNode = head;
	while (true) {
		if(currNode == NULL) break;
        Node* nextNode = currNode->next;
		delete currNode;
		currNode = nextNode;
	}
}

int DoublyLinkedListPriorityQueue::size() {
	return nodeCount;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
	if(nodeCount == 0)return true;
	return false;
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
	nodeCount++;
	if(head == NULL){
		head = new Node(value);
		head->previous = NULL;
		head->next = NULL;
	}
	else{
		Node* newNode = new Node(value);
		newNode->next = head;
		head->previous = newNode;
		head = newNode;
	}
}

string DoublyLinkedListPriorityQueue::peek() {
	if(head == NULL) error("Queue is empty.");
	return minElement()->data;
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
	if (head == NULL)error("Queue is empty.");
	Node* minElem = minElement();
	string result = minElem->data;
	nodeCount--;


	Node* prev = NULL;
	Node* nextNodes = NULL;
	//if minElem was somewhere in middle of the list
	if (minElem->next != NULL && minElem->previous != NULL){
		nextNodes = minElem->next;
		prev = minElem->previous;
		nextNodes->previous= prev;
		prev->next = nextNodes;
		delete minElem;
		//if minElem was first in list
	}else if(minElem->next != NULL && minElem->previous == NULL){
		head = minElem->next;
		head->previous = NULL;
		delete minElem;
		//if minElem was last in list
	}else if(minElem->next == NULL && minElem->previous != NULL){
		minElem->previous->next = NULL;
		delete minElem;
		//if minElem was the only node
	}else if(minElem->next == NULL && minElem->previous == NULL){
		delete minElem;
		head = NULL;
	}
	return result;
}

DoublyLinkedListPriorityQueue::Node *DoublyLinkedListPriorityQueue::minElement() {
	Node* result = head;
    Node* currNode = head->next;
	while (true) {
		if(currNode == NULL)break;
        if (currNode->data < result->data)result = currNode;
        currNode = currNode->next;
	}
	return result;
}
