/******************************************************************************
 * File: Trailblazer.cpp
 *
 * Implementation of the graph algorithms that comprise the Trailblazer
 * assignment.
 */

#include "Trailblazer.h"
#include "TrailblazerGraphics.h"
#include "TrailblazerTypes.h"
#include "random.h"
#include "TrailblazerPQueue.h"
using namespace std;


void colorMap(Grid<Node>&map, Loc start){
	for(int i = 0; i < map.nRows; i++){
		for(int j = 0; j < map.nCols; j++){
			map[i][j].col = GRAY;
		}
	}
	//start color-yellow, cost-0
	int r = start.row;
	int c = start.col;
	map[r][c].col=YELLOW;
	map[r][c].cost=0.0;
}

/* Function: shortestPath
 * 
 * Finds the shortest path between the locations given by start and end in the
 * specified world.	 The cost of moving from one edge to the next is specified
 * by the given cost function.	The resulting path is then returned as a
 * Vector<Loc> containing the locations to visit in the order in which they
 * would be visited.	If no path is found, this function should report an
 * error.
 *
 * In Part Two of this assignment, you will need to add an additional parameter
 * to this function that represents the heuristic to use while performing the
 * search.  Make sure to update both this implementation prototype and the
 * function prototype in Trailblazer.h.
 */
 Vector<Loc> finalPath(Grid<Node> &map, Loc start, Loc end){
	  Vector<Loc> res;
				 Loc curr = end;
				 while(true){
					 if(curr==start){
						 res+=curr;
						 break;
					 }
					res+=curr;
					curr=map[curr.row][curr.col].parent;
				 }
				 res+=start; 	
				 //reverse
				 Vector<Loc> final;
				 for(int i = res.size()-1; i >=0; i--){
					 final.add(res[i]);
				 }
				 return final;
}
Vector<Loc> shortestPath(Loc start,
             Loc end,
             Grid<double>& world,
             double costFn(Loc from, Loc to, Grid<double>& world),
			 double heuristic(Loc start, Loc end, Grid<double>& world)) {

				 Grid<Node> map(world.numRows(), world.numCols());
				 colorMap(map, start);

				 TrailblazerPQueue<Loc> queue;
				 //enqueue startNode into pq with priority 0
				 queue.enqueue(start, 0.0);

				 while(true){
					 if(queue.isEmpty())break;
					 Loc curr = queue.dequeueMin();
					 int r = curr.row;
					 int c = curr.col;
					 map[r][c].col=GREEN;
					 colorCell(world, curr, GREEN);
					 if(curr==end)break;

					 for(int i = r-1; i <= r+1; i++){
						 for(int k = c-1; k <= c+1; k++){
							 //if same cell continue
							 if(i==r && k==c)continue;
							 //if in bounds
							 if(i>=0 && k>=0 && i <= world.nRows-1 && k<= world.nCols-1){
								 Loc currNeigh = makeLoc(i, k);
								 double newCost = map[curr.row][curr.col].cost+costFn(curr, currNeigh, world);
								 if(map[i][k].col==GREEN)continue;
								 else if(map[i][k].col==GRAY){
									 map[i][k].col=YELLOW;
									 colorCell(world, currNeigh, YELLOW);
									 map[i][k].parent=curr;
									 map[i][k].cost=newCost;
									 queue.enqueue(currNeigh, newCost+heuristic(currNeigh, end, world));
								 }else{
									 if(map[i][k].cost > newCost){
										 map[i][k].cost=newCost;
										 map[i][k].parent=curr;
										 queue.decreaseKey(currNeigh, newCost+heuristic(currNeigh, end, world));
									 }
								 }
							 }
						 }
					 }
				 }	
				 Vector<Loc> res = finalPath(map, start, end);
    return res;
}

void createEdge(Loc onePoint, int r, int c, Set<Edge>&edgeSet){
	Loc secPoint;
	secPoint.row=r;
	secPoint.col=c;

	Edge one;
	one.start=onePoint;
	one.end=secPoint;
	
	Edge two;
	two.start=secPoint;
	two.end=onePoint;

	edgeSet.insert(one);
	edgeSet.insert(two);
}
void insertIntoPQ(Set<Edge>&edgeSet, TrailblazerPQueue<Edge> &edges){
	foreach(Edge edg in edgeSet){
		edges.enqueue(edg, randomReal(0, 1));
	}
}
void pushEdges(int numRows, int numCols, TrailblazerPQueue<Edge>&edges, Set<Edge> &edgeSet){
	for(int i = 0; i < numRows; i++){
		for(int k = 0; k < numCols; k++){
			Loc onePoint; onePoint.row=i; onePoint.col=k;
			if(i!=0){
				createEdge(onePoint, i-1, k, edgeSet);
			}
			if(k!=0){
				createEdge(onePoint, i, k-1, edgeSet);
			}
			if(i!=numRows-1){
				createEdge(onePoint, i+1, k, edgeSet);
			}
			if(k!=numCols-1){
				createEdge(onePoint, i, k+1, edgeSet);
			}
		}
	}
	insertIntoPQ(edgeSet, edges);
}

//call recursively until reaches Loc which is parent of itself
Loc findParent(Loc l, Grid<Loc>&parents){
	Loc parent = parents[l.row][l.col];
	if(parent==l)return parent;
	return parent = findParent(parent, parents);
}

bool sameCluster(Loc one, Loc two, Grid<Loc>&parents, Grid<int>&sizes){
	Loc onePar = findParent(one, parents);
	Loc twoPar = findParent(two, parents);
	if(onePar==twoPar)return true;
	one=onePar;
	two=twoPar;
	if(sizes[one.row][one.col] <= sizes[two.row][two.col])swap(one, two);
	parents[two.row][two.col]=one;
	int sizeToAdd = sizes[two.row][two.col];
	sizes[one.row][one.col]+=sizeToAdd;
	//returns false if one and two were not from came cluster but are combined now and we have 1 less cluster than before
	return false;
}

Set<Edge> createMaze(int numRows, int numCols) {
	//to insert in queue
	TrailblazerPQueue<Edge> edges;
	Set<Edge> edgeSet;
	pushEdges(numRows, numCols, edges, edgeSet);

	Grid<Loc>parent(numRows, numCols);
	Grid<int>sizes(numRows, numCols);
	//each node is parent of itself; size=1; single member in each cluster
	for(int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			Loc curr; curr.row=i; curr.col=j;
			//parent of itself
			parent[i][j]=curr;
			sizes[i][j]=1;
		}
	}

	Set<Edge> res;
	int clusters = numRows*numCols;
	while(clusters > 1){
		Edge curr = edges.dequeueMin();
		//if endpoints are in the same cluster just dequeued and continue
		if(sameCluster(curr.start, curr.end, parent, sizes))continue;
		//if endpoints were from different clusters
		clusters--;
		res.add(curr);
	}
    return res;
}
