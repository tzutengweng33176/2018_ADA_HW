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
		vector<vector<int> > adj;
public:
    // Constructor and destructor
    Graph(int V, int m)
    {
        this->maxColors=m; 
			  this->V = V;
				adj.reserve(V);
    }

    // function to add an edge to graph
    void addEdge(int v, int w);
    bool coloring(int u, int); 
    bool isSafe(int u,int color);
		void greedyColoring();
};

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);  // Note: the graph is undirected
}

bool Graph::isSafe(int u,int color){
    vector<int>::iterator it;
    //if any adjacent vertex to u has the same color return false. 
    //else is safe
    for(it=adj[u].begin();it!=adj[u].end();++it){
        if(Color[*it] == color) return false;
    }
    return true;
}

bool Graph::coloring(int u, int cnt ){
    if(u==this->V) {
			max_num_of_A = max(cnt, max_num_of_A);
			return true;
		}
    for(int i=0;i<this->maxColors;i++){//iterate through color 0, 1, 2
        //i represents the ith color.
        if(isSafe(u,i)){ // 20
            cout<<"HAHA"<<endl;
            Color[u] = i; //color of u equals i

						if (i == 0) // the color we want
							cnt++;
						if(this->coloring(u+1, cnt)) 
							m_colorable=true;
            if (i == 0)
							cnt--;
						Color[u] = -1; //Backtrack
				
        }
    } 
    return false;
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

	g.coloring(vertexColored, 0);
	if(m_colorable){
			cout<<max_num_of_A<<endl;
	}
	else{
			cout<<-1<<endl;
	}

	return 0;
}


