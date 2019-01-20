//用greedy是錯的
//要用brute force
//exponential time沒關係
//用greedy的方法窮舉
//所以要想要如何窮舉
//不用greedy其實也沒關係
//跟degree無關??!!!!
#include<algorithm>
#include<iostream>
#include<vector>
#include <list>
#include <stdio.h> 
#include <stdlib.h> 
using namespace std;  
// A class that represents an undirected graph
#define MAX_COLORS 1001
vector<int> Color(MAX_COLORS,-1);

bool m_colorable=false;
int max_num_of_A=0;
int count1=0;
class Graph
{
    int maxColors;
	  int V;    // No. of vertices
    list<int> *adj;    // A dynamic array of adjacency lists
public:
    // Constructor and destructor
    Graph(int V, int m)
    {
        this->maxColors=m; 
			  this->V = V;
        adj = new list<int>[V];
    }
    ~Graph()
    {
        delete [] adj;
    }

    // function to add an edge to graph
    void addEdge(int v, int w);
    bool coloring(int u); 
    bool isSafe(int u,int color);
    void printResult();
       // Prints greedy coloring of the vertices
		void greedyColoring();
};

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);  // Note: the graph is undirected
}

bool Graph::isSafe(int u,int color){
    list<int>::iterator it;
    //if any adjacent vertex to u has the same color return false. 
    //else is safe
    for(it=adj[u].begin();it!=adj[u].end();++it){
        if(Color[*it] == color) return false;
    }
    return true;
}

bool Graph::coloring(int u ){
    if(u==this->V) return true;
    for(int i=0;i<this->maxColors;i++){//iterate through color 0, 1, 2
        //i represents the ith color.
        if(isSafe(u,i)){
					// printf("Color vertex %d with color %d.. \n", u, i);
            Color[u] = i; //color of u equals i
          //  if(i==0){
					//	count1++;
					//	}


						if(this->coloring(u+1)) 
						{
							
						  for(int i=0;i<this->V;i++){
	             if(Color[i]==0){
							 count1++;
							 }	
						//	 cout<<"Vertex "<<i<<" has color "<<Color[i]<<endl;
							}
					//		if(Color[0]==1){
					//		return false;
					//		}
				  //     cout<<"Number of color 0 is: "<<count1<<endl;
							if(count1>max_num_of_A){
							  max_num_of_A=count1;
							}
							count1=0;

					
							//cout<<"Num of possible combinations: "<<max_num_of_A<<endl;	
							//	return true;
							m_colorable=true;
						}
					//	cout<<"Count of 0: "<<count<<endl;
	//	if(Color[1]==2){
	//   break;
	//	}
            Color[u] = -1; //Backtrack
				
        }
    } 
    return false;
}
void Graph::printResult(){
    for(int i=0;i<this->V;i++){
        cout << "Vertex " << i << " has color " << Color[i] << endl;
    }
    cout << endl << endl;
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
  //  bool more_than_3=false;
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
	//	if(!more_than_3){
		cout<<count<<endl;
//		}else{
//		cout<<-1<<endl;
//		}
    // print the result
//   for (int u = 0; u < V; u++)
//        cout << "Vertex " << u << " --->  Color "
//             << result[u] << endl;
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
int maxColors=3;
Graph g(v,3);

for(int i=0; i<e; i++){
g.addEdge(x[i]-1, y[i]-1);

}

int vertexColored=0;

if(v<=18){
g.coloring(vertexColored);
if(m_colorable){
        //cout << "Success! " << endl << endl;
        //g.printResult();
		cout<<max_num_of_A<<endl;
}else{
   // cout << "Failed coloring the graph" << endl;
    cout<<-1<<endl;

}
}else{
g.greedyColoring();

}

return 0;
}

