#include<vector>
#include <stdio.h>
#include<climits>
using namespace std;

int main() {
int t;

scanf("%d", &t); //input n

int n[t], v[t];  //v is the number of charactes and also the number of vertices on test case 

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











//最後再依照test case number輸出結果
return 0;
}
