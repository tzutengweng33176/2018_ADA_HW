#include <stdio.h>
#include<climits>
using namespace std;

int main() {
int n;
int array[200000];  //1 ≤ n ≤ 200000
int max_so_far=INT_MIN;
int max_ending_here=0;

scanf("%d", &n); //input n
for(int i=0; i<n; i++){
  scanf("%d",&array[i] ); //input an array
}
for(int i=0; i<n;i++){
  max_ending_here= max_ending_here+array[i];
  if(max_so_far < max_ending_here){
  max_so_far= max_ending_here;
  }

  if(max_ending_here<0){
  max_ending_here=0;
  }
}
printf("%d", max_so_far);

return 0;
}
    
