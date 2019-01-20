#include<stdio.h>
using namespace std;


int binarySearch(int arr[], int l, int r, int x) //return the index next smallest element 
{
   while (r >= l)
   {
        int mid = (l+r)/2;

        if (arr[mid] == x)//if we found the element in the array, return the index
            return mid;
        if (arr[mid] > x){
						r=mid-1;
				}else{
						l=mid+1;
				}
   }
   return r;
}

int main(){
	
int T; //number of test cases
int arr[200000];
int power_of_2[31];
int power_of_2_minus1[31];


scanf("%d", &T);
for(int i=0; i<T; i++){
scanf("%d", &arr[i]);

}
int ans[T]; //store the answers
for(int i=0; i<T; i++){
ans[i]=0;
}


power_of_2[0]=1;

for(int i=1; i<31; i++){
	power_of_2[i]=power_of_2[i-1]*2;
}
for(int i=1; i<31; i++){
	power_of_2_minus1[i]=power_of_2[i]-1;
}


//for(int j=0; j <31; j++){
//printf("%d ", power_of_2_minus1[j]);

//}// the array is already sorted
//may be we can try binary search

for(int i=0; i<T; i++){
	int nearest_index= binarySearch(power_of_2_minus1, 0, 30,arr[i] );
	ans[i]+=nearest_index;
	int temp= arr[i]-power_of_2_minus1[nearest_index];
	//if temp==0, arr[i]==power_of_2_minus1
	//the answer will be the index of power_of_2_minus1
	//so do nothing
	if(temp!=0){
		int count=0;
		while(temp){
		temp &=(temp-1);
		count++;
		}

		ans[i]+=count;
	}

}

// find the closest value in power_of_2_minus1 
// calculate temp=arr[i]-power_of_2_minus1
// calculate a= the number of 1s in temp(binary representation)
// ans[i]= index of power_of_2_minus1 +a 

for(int i=0; i<T; i++){
printf("%d\n", ans[i]);
}




return 0;
}
