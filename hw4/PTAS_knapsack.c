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
int greedyCount=0;
bool useMAX=false;
// Structure for an item which stores weight and corresponding 
// value of Item 
struct Item 
{ 
    long long int value, weight; 
    int index; //store the item number
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
     
    for (int i = 0; i < n; i++) 
    { 
        cout << arr[i].value << "  " << arr[i].weight << " : " 
             << ((double)arr[i].value / arr[i].weight) << endl; 
    } 
    
  
    long long int curWeight = 0;  // Current weight in knapsack 
    long long int finalvalue = 0; // Result (value in Knapsack) 
  
    // Looping through all Items 
    for (int i = 0; i < n; i++) 
    { 
        // If adding Item won't overflow, add it completely 
        if (curWeight + arr[i].weight <= W) 
        {   greedyCount++;
            curWeight += arr[i].weight; 
            finalvalue += arr[i].value; 
        } 
  
        // If we can't add current Item, add fractional part of it 
        else
        {   if(finalvalue>max){
															
							return finalvalue;								
															}
				    else{
              useMAX=true; 						
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
arr[i]={v[i], w[i], i+1};
}
//for(int i=0; i<n; i++){
//cout<<"Array index:"<<arr[i].index<<" ";
//}
//cout<<endl;

long long int maxVal=-1; //find max Value
int maxIndex=0;
for(int i=0; i<n; i++){
  if(v[i]>maxVal){
    maxVal=v[i]; //lower bound of optimal profit
		maxIndex=i+1;
}
}
long long int greedy_maxValue=0;
greedy_maxValue= fractionalKnapsack(W, arr, n, maxVal);
//printf("Max value is : %d \n", maxVal);
//printf("Greedy Max value is : %lld \n", greedy_maxValue);
//cout<<"GreedyCount: "<<greedyCount<<endl;
//for(int i=0; i<n; i++){
//cout<<"Sorted Array index:"<<arr[i].index<<" ";
//}
//cout<<endl;
//E=1/(2*greedy_maxValue+1)-->RUN TIME ERROR

long double E=0.001;
long double k= E*2*greedy_maxValue/n;
long long int v_reduced[n];
//K的話要用greedy算出一個最佳解，然後再算K
//不能用maxVal*E/n
//基本上做法沒問題
//
if(k<1) { //cannot delete
k=1.0;
cout<<"k=1?"<<endl;
}

//printf("k is %Lf", k);

for(int i=0; i<n; i++){

v_reduced[i]=floor(v[i]/k);
}
//必須reduced，如果沒有reduce就會runtime error
cout<<"Reduced values are: "<<endl;
for(int i=0; i<n; i++){
printf("%lld ", v_reduced[i]);
}
cout<<endl;

long long int V=0;
for(int i=0; i<n; i++){
V+=v_reduced[i];  //this will be an upper bound of the reduced profit
}
//upper bound是這樣用嗎？是！！
//if(V>(2*greedy_maxValue/k)){
V=2*greedy_maxValue/k;
//}
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
dp[0][0]=0;
for(long long int v=1; v<=V; v++){
  dp[0][v]=LLONG_MAX;
}
for(long long int y=1; y<=n; y++){
  for(long long int x=0; x<=V; x++){
	 
	//	for(int i=y; i>1; i--){
		if(v_reduced[y-1]>x){ //if x-v_reduced[y-1]<0
		   dp[y][x]=dp[y-1][x];
		  // printf("Skip item %d because its value is too large\n", k);
   	}else{
		
			if(dp[y-1][x]< w[y-1]+dp[y-1][x-v_reduced[y-1]] ){
		    dp[y][x]=dp[y-1][x];
		  }else{
		     if(dp[y-1][x-v_reduced[y-1]]==LLONG_MAX){
				  dp[y][x]=dp[y-1][x];
				 }else{
					dp[y][x]= w[y-1]+dp[y-1][x-v_reduced[y-1]];
				 // printf("Choosing item %lld \n", y);
					choice[y][x]=y; //Choose k
					
					//可能是backtrack出問題
				 }
			  //printf("Choosing item %d \n", k);	
			}
		}
	//	}
	}
} //END of 2 for loops

 for(int x=0;x<n+1;x++)  // loop 3 times for three lines
    {
        for(int y=0;y<V+1;y++)  // loop for the three elements on the line
        { if(dp[x][y]!=LLONG_MAX){ 
            cout<<dp[x][y]<<" "; 
																 
																 }
				else{
				
				    cout<<-1<<" ";
				}// display the current element out of the array
        }
    cout<<endl;  // when the inner loop is done, go to a new line
    }



long long int reduced_answer=0;
cout<<"dp[2][92]="<<dp[2][92]<<endl;
cout<<"dp[2][149]="<<dp[2][149]<<endl;
cout<<"dp[10][309]="<<dp[10][309]<<endl;
for(long long int l=V; l>=0; l--){
 // printf("Iterating dp[n][%lld]= %lld \n",l,dp[n][l]);
	if(dp[n][l]<=W){
		cout<<"dp["<<n<<"]["<<l<<"]= "<<dp[n][l]<<endl;
		reduced_answer=l;
   // printf("%Lf ",k*l);
    break;
}
}
long long int approx_answer= 0; 

vector<int> item;
int count=0;
for(int i=n; i>=0 && reduced_answer>=0;i-- ){

if(choice[i][reduced_answer]!=0){ //等於0表示沒選，應該要跳過
item.push_back(choice[i][reduced_answer]);
 approx_answer+=v[choice[i][reduced_answer]-1];
reduced_answer=reduced_answer-v_reduced[choice[i][reduced_answer]-1]; 
count++;
	}
}
int greedy_index[greedyCount];
for(int i=0; i<greedyCount; i++){
greedy_index[i]=arr[i].index;
}
sort(greedy_index, greedy_index+greedyCount);


cout<<"Items chosen by approximation algorithm..."<<endl;
printf("%d \n", count);
for(int i=0; i<count; i++){
printf("%d ", item.back());
item.pop_back();
}
cout<<endl;


if(approx_answer>greedy_maxValue){

printf("%d \n", count);
for(int i=0; i<count; i++){
printf("%d ", item.back());
item.pop_back();
}
}else{

if(useMAX){
 printf("%d \n", 1);

 printf("%d ", maxIndex);
}else{
 
 printf("%d \n", greedyCount);
 
 
 for(int i=0; i<greedyCount; i++){
   printf("%d ", greedy_index[i]);
 }
}
}
cout<<"Greedy Max Value is: "<<greedy_maxValue<<endl;
cout<<"Approximate Value is: "<<approx_answer<<endl;

return 0;

}
