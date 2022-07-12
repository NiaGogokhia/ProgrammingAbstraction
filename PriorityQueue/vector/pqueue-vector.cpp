/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"

VectorPriorityQueue::VectorPriorityQueue() {
	nodeCount = 0;
}

VectorPriorityQueue::~VectorPriorityQueue() {
	nodeCount = 0;
}

int VectorPriorityQueue::size() {
	return nodeCount;
}

bool VectorPriorityQueue::isEmpty() {
	if(queueElements.size() != 0) return false;
	return true;
}

void VectorPriorityQueue::enqueue(string value) {
	queueElements.push_back(value);
	nodeCount++;
}

string VectorPriorityQueue::peek() {
	if(queueElements.size()==0) error("Queue is empty.");
	int min = minIndex();
	return queueElements[min];
}

int VectorPriorityQueue::minIndex(){
	int index = 0;
	string min = queueElements[0];
	for(int i = 0; i < queueElements.size(); i++){
		string temp = queueElements[i];
		if(temp < min) index = i;
	}
	return index;
}
string VectorPriorityQueue::dequeueMin() {
	if(queueElements.size() == 0) error("Queue is empty.");
	nodeCount--;
	int index = minIndex();
	string res = queueElements[index];
	queueElements.remove(index);
	return res;
}

