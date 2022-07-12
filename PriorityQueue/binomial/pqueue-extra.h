/**********************************************
 * File: pqueue-extra.h
 *
 * Your own custom priority queue class, if you
 * want to build one for extra credit.
 *
 * Please replace these file comments with a
 * description of how your priority queue works.
 */
#ifndef PQueue_Extra_Included
#define PQueue_Extra_Included

#include <string>
#include "vector.h"
using namespace std;

/*
 * TODO: Describe this class!
 */
class ExtraPriorityQueue {
public:
	/* Constructs a new, empty priority queue. */
	ExtraPriorityQueue();
	
	/* Cleans up all memory allocated by this priority queue. */
	~ExtraPriorityQueue();
	
	/* Returns the number of elements in the priority queue. */
	int size();
	
	/* Returns whether or not the priority queue is empty. */
	bool isEmpty();
	
	/* Enqueues a new string into the priority queue. */
	void enqueue(string value);
	
	/* Returns, but does not remove, the lexicographically first string in the
	 * priority queue.
	 */
	string peek();
	
	/* Returns and removes the lexicographically first string in the
	 * priority queue.
	 */
	string dequeueMin();
	

private:


	struct node{
		string data;
		int degree;
		node* parent;
		Vector<node*>children;
	};
	
	int queueSize;
	node* newNode(string value);
	Vector<bool> used;
	Vector<node*> queue;
	void addInQueue(node* newNode);
};

#endif
