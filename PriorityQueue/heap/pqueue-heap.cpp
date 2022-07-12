/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"
#include "vector.h"

HeapPriorityQueue::HeapPriorityQueue() {
	
}

void HeapPriorityQueue::print(Vector<string> allElements)
{
	string vec;
	for(int i= 0; i < allElements.size(); i++) vec+=allElements[i];
	cout << vec << endl;
}

void HeapPriorityQueue::swap(int index1, int index2){
	string temp = allElements[index1];
	allElements[index1] = allElements[index2];
	allElements[index2] = temp;
}

void HeapPriorityQueue::sortUpwards(int index){
	if(index == 0)return;
	int parentIndex;
	if(index%2==0)parentIndex = (index-2)/2;
	else parentIndex = (index-1)/2;
	while(true){
		if(index == 0) break;
		if(allElements[index] < allElements[parentIndex])swap(index, parentIndex);
		else break;
		if(parentIndex == 0)break;
		index = parentIndex;
		if(index%2==0)parentIndex = (index-2)/2;
		else parentIndex = (index-1)/2;
	}
}

void HeapPriorityQueue::sortDownwards(){
	if(allElements.size()==0 || allElements.size()==1)return;
	int parentIndex = 0;
	int childIndex = 1;
	int childIndex2;
	if(allElements.size() >= 3){
		childIndex2 = 2;
		if(allElements[childIndex2] < allElements[childIndex]) childIndex = childIndex2;
	} 
	while(true){
		if(allElements[childIndex] < allElements[parentIndex])swap(childIndex, parentIndex);
		else break;
		parentIndex = childIndex;
		childIndex = parentIndex*2+1;
		childIndex2= parentIndex*2+2;
		if(allElements.size()-1 < childIndex)break;
		if(allElements.size()-1 >= childIndex2){
			if(allElements[childIndex2] < allElements[childIndex]) childIndex = childIndex2;
		}
	}
}


HeapPriorityQueue::~HeapPriorityQueue() {
	allElements.clear();
}

int HeapPriorityQueue::size() {
	return allElements.size();
}

bool HeapPriorityQueue::isEmpty() {
	if(allElements.size()==0)return true;
	return false;
}

void HeapPriorityQueue::enqueue(string value) {
	allElements.add(value);
	sortUpwards(allElements.size()-1);
//	print(allElements);
}

string HeapPriorityQueue::peek() {
	return allElements[0];
}

string HeapPriorityQueue::dequeueMin() {
	string res = allElements[0];
	swap(0, allElements.size()-1);
	allElements.remove(allElements.size()-1);
	sortDownwards();
//	print(allElements);
	return res;
}