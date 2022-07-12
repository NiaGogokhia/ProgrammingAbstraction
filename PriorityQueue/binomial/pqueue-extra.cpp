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
}

ExtraPriorityQueue::~ExtraPriorityQueue() {
	// TODO: Fill this in!
}

ExtraPriorityQueue::node* ExtraPriorityQueue::newNode(string value){
		node *temp = new node;
		temp->data = value;
		temp->degree = 0;
		temp->parent = NULL;
		return temp;
	}

int ExtraPriorityQueue::size() {
	return queueSize;
}

bool ExtraPriorityQueue::isEmpty() {
	if(queueSize==0)return true;
	return false;
}


void ExtraPriorityQueue::addInQueue(node* newNodeQ){
	int dgr = newNodeQ->degree;
	//if tree of this degree does not exist we just push tree in queue
	if(used.size() <= dgr)queue.add(newNodeQ);
	else if(used[dgr] == false) queue.add(newNodeQ);
	else{
		node* temp = queue[dgr];
		queue[dgr] = NULL;
		
		node* parent;
		node* child;

		if(newNodeQ->data > temp->data){
			parent = newNodeQ;
			child = temp;
		}else{
			parent = temp;
			child = newNodeQ;

		}
		//recursively update queue
		int newdegree = dgr+1;
		Vector<node*> tempVec = parent->children;
		tempVec.add(child);
		parent->children = tempVec;
		if(newdegree > used.size() || used[newdegree] == NULL) queue.add(parent);
		else addInQueue(parent);
		return;
	}
}
void ExtraPriorityQueue::enqueue(string value) {
	node* temp = newNode(value);
	temp->degree = 0;
	temp->parent = NULL;
	Vector<node*>chldr;
	temp->children = chldr;
	addInQueue(temp);
	queueSize++;
}

string ExtraPriorityQueue::peek() {
	if(isEmpty()) error("Queue is empty.");
	// maxvalue maq chasasmeli
	string min = "";
	for(int i = 0; i < queue.size(); i++){
		node* temp = queue[i];
		if(i==0) min = temp->data;
		else if(temp->data < min ) min = temp->data;
	}
	return min;
}

string ExtraPriorityQueue::dequeueMin() {
	if(isEmpty()) error("Queue is empty.");
	string min;
	int index = -1;
	for(int i = 0; i < queue.size(); i++){
		node* temp = queue[i];
		if(i==0){
			min = temp->data;
			index =0;
		}
		else if(temp->data < min ){
			min = temp->data;
			index = i;
		}
	}
	node* temp = queue[index];
	Vector<node*> minChildren = temp->children;
	queue.remove(index);
	for(int i = 0; i < minChildren.size(); i++){
		node* child = minChildren[i];
		addInQueue(child);
	}
	queueSize--;
	return min;
}

