// C++ implementation to count number of 
// increasing subsequences of size k 
#include <bits/stdc++.h> 
  
using namespace std; 
  
// function to count number of increasing 
// subsequences of size k 
int numOfIncSubseqOfSizeK(int arr[], int n, int k) 
{ 
    int dp[k][n], sum = 0; 
    memset(dp, 0, sizeof(dp)); 
  
    // count of increasing subsequences of size 1 
    // ending at each arr[i] 
    for (int i = 0; i < n; i++) 
        dp[0][i] = 1; 
  
    // building up the matrix dp[][] 
    // Here 'l' signifies the size of 
    // increassing subsequnce of size (l+1). 
    for (int l = 1; l < k; l++) { 
  
        // for each increasing subsequence of size 'l' 
        // starting with element arr[i] 
        for (int i = n-l-1; i >= 0; i--) { 
  
            // count of increasing subsequnces of size 'l' 
            // ending with element arr[i] 
            dp[l][i] = 0; 
            for (int j = n-l; j > i; j--) { 
                if (arr[j] < arr[i]) 
                    dp[l][i] += dp[l - 1][j]; 
            } 
        } 
    } 
  
    // sum up the count of increasing subsequences of 
    // size 'k' ending at each element arr[i] 
    for (int i =n- k ; i >=0; i--) 
        sum += dp[k - 1][i]; 
  
    // required number of increasing 
    // subsequences of size k 
    return sum; 
} 
  
// Driver program to test above 
int main() 
{ 
    int arr[] = { 1,12, 11, 10, 9 ,16, 20 }; 
    int n = sizeof(arr) / sizeof(arr[0]); 
    int k = 3; 
  
    cout << "Number of Decreasing Subsequences of size "
         << k << " = " << numOfIncSubseqOfSizeK(arr, n, k); 
  
    return 0; 
} 

