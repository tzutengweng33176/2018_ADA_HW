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

// Structure for an item which stores weight and corresponding 
// value of Item 
struct Item 
{ 
    long long int value, weight; 
    // Constructor 
}; 

// Comparison function to sort Item according to val/weight ratio 
bool cmp(struct Item a, struct Item b) 
{ 
    long double r1 = (long double)a.value / a.weight; 
    long double r2 = (long double)b.value / b.weight; 
    return r1 > r2; 
} 
  

// Main greedy function to solve problem 
long long int fractionalKnapsack(long long int W, struct Item arr[],long long int n, long long int max) 
{ 
    //    sorting Item on basis of ratio 
    sort(arr, arr + n, cmp); 
  
    //    Uncomment to see new order of Items with their ratio 
    /* 
    for (int i = 0; i < n; i++) 
    { 
        cout << arr[i].value << "  " << arr[i].weight << " : " 
             << ((double)arr[i].value / arr[i].weight) << endl; 
    } 
    */
  
    long long int curWeight = 0;  // Current weight in knapsack 
    long long int finalvalue = 0; // Result (value in Knapsack) 
  
    // Looping through all Items 
    for (int i = 0; i < n; i++) 
    { 
        // If adding Item won't overflow, add it completely 
        if (curWeight + arr[i].weight <= W) 
        { 
            curWeight += arr[i].weight; 
            finalvalue += arr[i].value; 
        } 
  
        // If we can't add current Item, add fractional part of it 
        else
        {   if(finalvalue>max){
															
							return finalvalue;								
															}
				    else{
						
						  return max;  
						}
           // int remain = W - curWeight; 
           // finalvalue += arr[i].value * ((double) remain / arr[i].weight); 
            break; 
        } 
    } 
  
    // Returning final value 
    //return finalvalue; 
} 


int main() {
long long int n, W; 

scanf("%lld %lld", &n, &W); //input number of items and knapsack capacity W

long long int v[n], w[n];  //declare two arrays storing values and weights


for(int i=0; i<n; i++){
  scanf("%lld %lld",&v[i], &w[i] ); //input a coordinate x, y
  
}

Item arr[n];

for(int i=0; i<n; i++){
arr[i]={v[i], w[i]};
}


long long int maxVal=-1; //find max Value

for(int i=0; i<n; i++){
  if(v[i]>maxVal){
    maxVal=v[i];
}
}
long long int greedy_maxValue=0;
greedy_maxValue= fractionalKnapsack(W, arr, n, maxVal);
//printf("Max value is : %d \n", maxVal);
//printf("Greedy Max value is : %lld \n", greedy_maxValue);
long double E=0.1;
long double k= E*greedy_maxValue/n;
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
