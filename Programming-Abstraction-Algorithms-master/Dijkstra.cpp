

#include<iostream>

using namespace std;

int main()
{//Easy Dijkstra implementation

//graph[i] gives access to all neighbours of i'th node (pair<int,int> p p.first - neighbour node, p.second - edge weight)
vector<vector<pair<int,int>>>graph(n);
vector<int> dist(n, INT_MAX);

queue<int> q;
q.push(start);
dist[start]=0;
//not using min/max heap slows algorithm
while(!q.empty()){
    int curr = q.front();
    q.pop();
    for(pair<int,int>p:graph[curr]){
        int next = p.first;
        int nextDist = p.second;
        int newDist = dist[curr]+nextDist;
        if(dist[next]>newDist){
            dist[next]=newDist;
            q.push(next);
        }
    }
}
//dist[] contains min distances from starting node, if dist[k]==INT_MAX node is unreachable 

}
