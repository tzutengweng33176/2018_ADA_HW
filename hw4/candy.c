//用greedy是錯的
//要用brute force
//exponential time沒關係

#include<iostream>
#include<utility>
#include<vector>
#include<algorithm>
#include <list>
#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 
using namespace std;  
// A class that represents an undirected graph
class Graph
{
    int V;    // No. of vertices
    list<int> *adj;    // A dynamic array of adjacency lists
public:
    // Constructor and destructor
    Graph(int V)
    {
        this->V = V;
        adj = new list<int>[V];
    }
    ~Graph()
    {
        delete [] adj;
    }

    // function to add an edge to graph
    void addEdge(int v, int w);

    // Prints greedy coloring of the vertices
    void greedyColoring();
};

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);  // Note: the graph is undirected
}

struct vertexDegree
{
    int v;
    int degree;
};

bool compareByDegree(const vertexDegree& x, const vertexDegree& y)
{
    return x.degree < y.degree;
}

// Assigns colors (starting from 0) to all vertices and prints
// the assignment of colors
void Graph::greedyColoring()
{
    int result[V];
    // Initialize remaining V-1 vertices as unassigned
    for (int u = 0; u < V; u++)
		{  result[u] = -1;  // no color is assigned to u
     }
    // A temporary array to store the available colors. True
    // value of available[cr] would mean that the color cr is
    // assigned to one of its adjacent vertices
    bool available[V]; 
    bool more_than_3=false;
    for (int cr = 0; cr < V; cr++)
		{ available[cr] = false;
     }
    vertexDegree arr[V];
    for (int i = 0; i < V; i++)
    {
        arr[i].v = i;
        arr[i].degree = adj[i].size();
    }


    sort(arr, arr+V, compareByDegree);

//    cout << "Sorted vertices \n";
 //   for (int i = 0; i <V; i++)
 //   {
 //       cout << arr[i].v << " ";
 //   }
 //   cout << "\n";

    // Assign the first color to first vertex in sorted array
    result[arr[0].v]  = 0;


    // Assign colors to remaining V-1 vertices
    for (int x = 1; x < V; x++)
    {
        int u = arr[x].v;

        // Process all adjacent vertices and flag their colors
        // as unavailable
        list<int>::iterator i;
				i=adj[u].begin();
			//	cout<<*i<<endl;
				 //start from the adjacent vertex
        while( i != adj[u].end())
				{ if (result[*i] != -1){
						//		cout<<"*i="<<*i<<endl;								 
						//		cout<<"result[*i]="<<result[*i]<<endl;								 
                available[result[*i]] = true;
								
															 }
				  ++i;
        }
//        cout<<available[0]<<endl;
				// Find the first available color
        int cr;
        for (cr = 0; cr < V; cr++)
				{ 
					if (available[cr] == false)
                break;
				}

    //    if(available[0]==false){
					//cout<<"NO EXECUTION?"<<endl;
		//		  result[u]=0;
		//		}else{
     //       if(available[1]==false){
						 
		//				 result[u]=1; 
		//				}else if(available[2]==false) {

		//				result[u]=2;
						
	//					}else{
   //       more_than_3=true;
          result[u] = cr; // Assign the found color
	//					}
  //      }
        // Reset the values back to false for the next iteration
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
				{  if (result[*i] != -1)
					{ 
						available[result[*i]] = false;
					}
				}
    }
    int count=0;
		
		for(int u=0; u<V; u++){
		  if(result[u]==0){
			  count++;
			}
     
		}
		if(!more_than_3){
		cout<<count<<endl;
		}else{
		cout<<-1<<endl;
		}
    // print the result
   for (int u = 0; u < V; u++)
        cout << "Vertex " << u << " --->  Color "
             << result[u] << endl;
}


int main() {
int v, e; 

scanf("%d %d", &v, &e); //input number of vertices v and edges e

int x[e], y[e];  //declare two arrays storing x and y coordiantes

//use adjacenct list to build the graph
//just add the edge and edge weight

for(int i=0; i<e; i++){
  scanf("%d %d",&x[i], &y[i]); //input a coordinate x, y
  
}
Graph g(v);

for(int i=0; i<e; i++){
g.addEdge(x[i]-1, y[i]-1);

}

g.greedyColoring();

return 0;
}

