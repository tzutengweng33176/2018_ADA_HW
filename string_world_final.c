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
#include<climits>
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
    bool hasEdge(int v); 
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
bool Graph::hasEdge(int v){
return !this->adj[v].empty();
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
int t;

scanf("%d", &t); //input n

int n[t], v[t];  //v is the number of charactes and also the number of vertices on test case 
//v is also the number of characters in U on that test case
vector<int> s[t], r[t], map[t], ans[t]; 
for(int i=0; i<t; i++){

scanf("%d %d", &n[i], &v[i]); //input number of vertices v

int temp1[n[i]], temp2[n[i]];
int temp3[n[i]+1];
//int s[n][t], r[n][t];  //declare two arrays storing the string and the rank
//int map[n+1][t];  //store the mapping between rank and index(start from string[index])
//use adjacenct list to build the graph
//the graph has to be directed because we need to get the topological order of the characters, if the graph is undirected we can't get the order of the characters correctly
//just add the edge and edge weight

for(int j=0; j<n[i]; j++){
  scanf("%d",&temp1[j]); //input a string of characters of length n
  }

for(int k=0; k<n[i]; k++){
  scanf("%d",&temp2[k]); //input a string of characters of length n
  }

for(int l=0; l<n[i]; l++){
  s[i].push_back(temp1[l]);
	r[i].push_back(temp2[l]);
}  

//calculate  vector map[] on test case i 
//create a vector sized n[i] on map[i]
//store the mapping from rank to index
map[i]=vector<int>(n[i]+1);
for(int x=0; x<n[i];x++){
map[i][r[i][x]]=x;
}
//讓map index從1開始
} //END OF INPUT


//for(int a=1; a<map[0].size(); a++){
//printf("%d ", map[0][a]);
//}
//printf("\n");
//for(int b=1; b<map[1].size(); b++){

//printf("%d ", map[1][b]);
//}
//先把input按照test case number存好

//算t次topological sort
//每一次都要把topological sort的結果存起來


for(int i=0; i<t; i++){

Graph g(v[i]);

int arr[2];
//create a graph with v vertices
//from vertex 0 to vertex v-1
//we have to compare the character by rank
for(int a=1; a<n[i]; a++){
int p1, p2; //declare two pointers pointing to the starting index of the suffix
p1=map[i][a];
p2=map[i][a+1];
		for(int b=0; b<min(n[i]-p1, n[i]-p2); b++){
		      if(s[i][p1]!=s[i][p2]){
					  if(v[i]>2){
						g.addEdge(s[i][p1]-1, s[i][p2]-1);
						}else{
						arr[s[i][p1]-1]=s[i][p2]-1;
						}
						break;

					}else{
						p1++;
						p2++;
					}
		
		}
}

if(v[i]>2){
g.topologicalSort(); 
}else{
if(arr[0]==1){
cout << 1 << " "<<2; 
}else if(arr[1]==0){

cout << 2 << " "<<1; 
}

}
printf("\n"); 
}







//最後再依照test case number輸出結果
return 0;
}