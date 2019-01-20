//Choose some integer  k = εVmax/ n
// Let v'i= ⌊vi / k⌋ for all vi
// Use the value-based DP algorithm to find
//the value of the optimal solution for the
//problem instance using values v'i  and the
//same weights as before.
//Return k times this value.
//一定要用value-based DP要不然應該會TLE
//DP table的V是reduced value的總和，不是原來的value
#include<iostream>
#include<utility>
#include<algorithm>
#include<vector>
#include<math.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 
using namespace std;  


int main() {
long long int n, W; 

scanf("%lld %lld", &n, &W); //input number of items and knapsack capacity W

long long int v[n], w[n];  //declare two arrays storing values and weights


for(int i=0; i<n; i++){
  scanf("%lld %lld",&v[i], &w[i] ); //input a coordinate x, y
  
}
long long int maxVal=-1; //find max Value
for(int i=0; i<n; i++){
  if(v[i]>maxVal){
    maxVal=v[i];
}
}
//printf("Max value is : %d \n", maxVal);
long double E=0.5;
long double k= (maxVal*E)/n;
long long int v_reduced[n];
//K的話要用greedy算出一個最佳解，然後再算K
//不能用maxVal*E/n
//基本上做法沒問題
for(int i=0; i<n; i++){

v_reduced[i]=floor(v[i]/k);
}

//for(int i=0; i<n; i++){
//printf("%d ", v_reduced[i]);
//}
long long int V=0;
for(int i=0; i<n; i++){
V+=v_reduced[i];
}

//printf("Sum of reduced values V is: %d \n", V);

//long long int** dp = new long long int*[n+1];
//for(int i = 0; i < n+1; ++i)
//    dp[i] = new long long int[V+1];

//int** choice = new int*[n+1];
//for(int i = 0; i < n+1; ++i)
//    choice[i] = new int[V+1];   Still runtime error after using new
vector<vector<long long int>>dp(n+1, vector<long long int>(V+1));
vector<vector<int>>choice(n+1, vector<int>(V+1));
//runtime error when using vectors, don't know why
//dp[0][0]=0;
for(long long int v=1; v<=V; v++){
  dp[0][v]=LLONG_MAX;
}
for(long long int k=1; k<=n; k++){
  for(long long int x=1; x<=V; x++){
	  if(v_reduced[k-1]>x){
		   dp[k][x]=dp[k-1][x];
		  // printf("Skip item %d because its value is too large\n", k);
    	}else{
		
			if(dp[k-1][x]< w[k-1]+dp[k-1][x-v_reduced[k-1]] ){
		    dp[k][x]=dp[k-1][x];
		  }else{
		     if(dp[k-1][x-v_reduced[k-1]]==LLONG_MAX){
				  dp[k][x]=LLONG_MAX;
				 }else{
					dp[k][x]= w[k-1]+dp[k-1][x-v_reduced[k-1]];
				  //printf("Choosing item %d \n", k);
					choice[k][x]=k; //Choose k
				 }
			  //printf("Choosing item %d \n", k);	
			}
		}
	}
} //END of 2 for loops

long long int reduced_answer=0;
for(long long int l=V; l>=0; l--){
 // printf("Iterating dp[n][%lld]= %lld \n",l,dp[n][l]);
	if(dp[n][l]<=W){
		reduced_answer=l;
   // printf("%Lf ",k*l);
    break;
}
}
vector<int> item;
int count=0;
for(int i=n; i>0 && reduced_answer>0;i-- ){
item.push_back(choice[i][reduced_answer]);
reduced_answer=reduced_answer-v_reduced[choice[i][reduced_answer]-1]; 
count++;
}


printf("%d \n", count);
for(int i=0; i<count; i++){
printf("%d ", item.back());
item.pop_back();
}

//printf("Choose item %d \n", choice[n-2][0] ); print 0代表沒選


return 0;

}
