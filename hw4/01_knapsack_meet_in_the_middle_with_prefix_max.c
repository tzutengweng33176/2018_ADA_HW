//把item分成兩組
//
//先對weight做subset sum
//再找出對應的value
//目前作法理論上不會wrong answer 一定有bug沒找到！
#include<iostream>
#include<utility>
#include<algorithm>
#include<vector>
#include<math.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 
#include<bits/stdc++.h>
using namespace std;  
typedef long long int ll;

vector<pair<ll,ll>> X(1100000);
vector<pair<ll,ll>> Y(1100000);

bool comparison(const pair<ll,ll> &a,const ll &b){
    return a.first<=b; //幹！是小於等於啊！不是小於
		//如果是小於的話，如果weight重複會有bug
}

// Find all possible sum of elements of a[] and store 
// in x[] 
// c is the starting pointer of the original BIG vector
void calcsubarray(vector<pair<ll,ll>> a, vector<pair<ll, ll>>& x, int n, int c) 
{ 
    for (int i=0; i<(1<<n); i++) 
    {   
        ll w = 0; //sum of all possible combinations of weights
				ll p = 0; //sum of all possible combinations of prices
        for (int j=0; j<n; j++){ 
            if (i & (1<<j)){ 
                w += a[j+c].first;
				        p += a[j+c].second;
								//printf("a[%d+c].first= %lld \n",j, a[j+c].first);
						}
				}
				//printf("sum of weights= %lld \n", w);
				//printf("sum of pirces= %lld \n", p);
        x[i]=make_pair(w,p); 
			  //printf("x[%d].first= %lld \n",i ,x[i].first);
    } 
} 
  
ll knapsack(vector<pair<ll,ll>> vect1, ll n, ll maxW){

 // Compute all subset sums of first and second 
 // halves, 先處理偶數的部分，再處理奇數 
int size_X;
int size_Y;

if(n%2==0){
  calcsubarray(vect1, X, n/2, 0); 
  calcsubarray(vect1, Y, n-n/2, n/2); 
  size_X= 1<<(n/2);
  size_Y = 1<<(n-n/2); 
}else{
  calcsubarray(vect1, X, (n-1)/2, 0);
  calcsubarray(vect1, Y, n-(n-1)/2, (n-1)/2);
  size_X = 1<<((n-1)/2);
  size_Y = 1<<((n+1)/2);

}


sort(Y.begin(), Y.begin()+size_Y);//sorted by weights, stored in Y

//for(int i=0; i<size_Y; i++){
//printf("Y[%d]: (weight, price)= (%lld, %lld)\n", i, Y[i].first, Y[i].second);
//}
// To keep track of the maximum sum of a subset 
// such that the maximum sum is less than W 
ll max = 0; 
ll maxValue=0;
ll prefix_max[size_Y];
ll curMax=Y[0].second;
for(int i=0; i<size_Y; i++){
  if(Y[i].second>curMax){
    curMax=Y[i].second;
  }
  prefix_max[i]=curMax;
}
// Traverse all elements of X and do Binary Search 
    // for a pair in Y with maximum sum less than S. 
    for (int i=0; i<size_X; i++) 
    { 
       // printf("X[%d]: (weight, price)= (%lld, %lld)\n", i, X[i].first, X[i].second);
        if (X[i].first <= maxW) 
        {   //if(i==85){
						//	printf("YOU DID CONSIDER THE ANSWER!");			 
						//				 } 
            // lower_bound() returns the first address 
            // which has value greater than or equal to 
            // S-X[i]. 
					  vector<pair<ll,ll>>::iterator low; 	
					  low = lower_bound(Y.begin(), Y.begin()+size_Y, maxW-X[i].first, comparison); 
            int p=distance(Y.begin(), low);
					//	if(i==85){
					//	printf("P is: %d", p);
					//	}
            // If S-X[i] was not in array Y then decrease 
            // p by 1
					//	printf("p is %d \n", p);
            if (p == size_Y || Y[p].first != (maxW-X[i].first)) 
                p--; 
					//	printf("p after -- is %d \n", p);
						 if(prefix_max[p]+X[i].second>maxValue){
								// printf("Pick Y[%d].second and X[%d].second: %lld, %lld \n",p, i, Y[p].second, X[i].second); 
								// printf("Pick Y[%d].first and X[%d].first: %lld, %lld \n",p, i, Y[p].first, X[i].first); 
									maxValue=prefix_max[p]+X[i].second;
								}
                 //不用全部搜，有些很爛的pair可以丟掉
								 //要不然會TLE
								 //calculate the prefix maximum of prices

          //  if ((Y[p].first+X[i].first) > max) 
          //     max = Y[p].first+X[i].first;
									
        } 
    }   
      // printf("Max value is: %lld \n", max);
       //  printf("%lld\n", maxValue);

return maxValue; 

}


int main() {
ll n, W; 

scanf("%lld %lld", &n, &W); //input number of items and knapsack capacity W

ll v[n], w[n];  //declare two arrays storing values and weights


for(ll i=0; i<n; i++){
  scanf("%lld %lld",&v[i], &w[i] ); //input a coordinate x, y
  
}

vector<pair<ll,ll>> vect;

for(ll i=0; i<n; i++){
 vect.push_back(make_pair(w[i], v[i]));  //store weight and value pair in a vector
}
ll ans= knapsack(vect, n, W);
//printf("All possible combinations of weights: \n");
//for(int i=0; i<4; i++){
//printf("%lld ", X[i].first);
//}
//printf("All possible combinations of prices: \n");

//for(int i=0; i<(1<<(n/2)); i++){
//printf("%lld ", X[i].second);
//}
printf("%lld", ans);

return 0;
}
