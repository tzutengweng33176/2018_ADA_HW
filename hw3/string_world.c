#include<iostream>
#include<utility>
#include<vector>
#include<algorithm>
#include <list> 
#include <stack> 
#include <cstring> 
#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 
using namespace std;  


// Class to represent a graph 
class Graph 
{ 
    int V;    // No. of vertices' 
  
    // Pointer to an array containing adjacency listsList 
    list<int> *adj; 
  
    // A function used by topologicalSort 
    void topologicalSortUtil(int v, bool visited[], stack<int> &Stack); 
public: 
    Graph(int V);   // Constructor 
  
    // function to add an edge to graph 
    void addEdge(int v, int w); 
  
    // prints a Topological Sort of the complete graph 
    void topologicalSort(); 
}; 
  
Graph::Graph(int V) 
{ 
    this->V = V; 
    adj = new list<int>[V]; 
} 
  
void Graph::addEdge(int v, int w) 
{ 
    adj[v].push_back(w); // Add w to v’s list. 
} 
  
// A recursive function used by topologicalSort 
void Graph::topologicalSortUtil(int v, bool visited[], stack<int> &Stack) 
{ 
    // Mark the current node as visited. 
    visited[v] = true; 
  
    // Recur for all the vertices adjacent to this vertex 
    list<int>::iterator i; 
    for (i = adj[v].begin(); i != adj[v].end(); ++i) 
        if (!visited[*i]) 
            topologicalSortUtil(*i, visited, Stack); 
  
    // Push current vertex to stack which stores result 
    Stack.push(v); 
} 
  
// The function to do Topological Sort. It uses recursive topologicalSortUtil() 
void Graph::topologicalSort() 
{ 
    stack<int> Stack; 
  
    // Mark all the vertices as not visited 
    bool *visited = new bool[V]; 
    for (int i = 0; i < V; i++) 
        visited[i] = false; 
  
    // Call the recursive helper function to store Topological Sort 
    // starting from all vertices one by one 
    for (int i = 0; i < V; i++) 
        if (visited[i] == false) 
            topologicalSortUtil(i, visited, Stack); 
  
    // Print contents of stack 
    while (Stack.empty() == false) 
    {    
			  
        cout << (1 + Stack.top()) << " "; 
        Stack.pop(); 
    } 
} 
  
int min(int x, int y) 
{ 
    return (x < y)? x : y; 
} 
  




int main() {

int t; //number of test cases

//scanf("%d", &t);
//declare a vector of vectors, sized t

int n, v;  //v is the number of charactes and also the number of vertices on test case t

scanf("%d %d", &n, &v); //input number of vertices v

int s[n], r[n];  //declare two arrays storing the string and the rank
int map[n+1];  //store the mapping between rank and index(start from string[index])
//use adjacenct list to build the graph
//the graph has to be directed because we need to get the topological order of the characters, if the graph is undirected we can't get the order of the characters correctly
//just add the edge and edge weight

for(int i=0; i<n; i++){
  scanf("%d",&s[i]); //input a string of characters of length n
  }

for(int i=0; i<n; i++){
  scanf("%d",&r[i]); //input a string of characters of length n
  }

for(int i=0; i<n; i++){
  map[r[i]]=i;
}
Graph g(v); //create a graph with v vertices
//from vertex 0 to vertex v-1
//we have to compare the character by rank
for(int i=1; i<n; i++){
int p1, p2; //declare two pointers pointing to the starting index of the suffix
p1=map[i];
p2=map[i+1];
		for(int j=0; j<min(n-p1, n-p2); j++){
		      if(s[p1]!=s[p2]){
					  g.addEdge(s[p1]-1, s[p2]-1);
						break;

					}else{
						p1++;
						p2++;
					}
		
		}
}

 g.topologicalSort(); 
 

return 0;
}


