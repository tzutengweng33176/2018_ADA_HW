#include <stdio.h>
#include <unordered_map>
using namespace std;

//多項式的乘法。不要用hash map 比較慢，直接開array比較快
//n<50的部分，直接乘。n>=50的部分用多項式的divide and conquer
int main() {
int n;//the number of piles
int m; //the number of queries


scanf("%d", &n); //input n
int num_of_stones[n];//the number of stones of the 𝑖𝑡ℎ pile
for(int i=0; i<n; i++){
  scanf("%d",&num_of_stones[i]); 
}

scanf("%d", &m);

long long int magic_numbers[m]; //the magic number of the i-th query

for(int j=0; j<m; j++){
  scanf("%lld", &magic_numbers[j]); //input a

}
unordered_map<int, int> map; //create a hash table to store (num_of_stones, counts)
for(int i=0; i<n; i++){
  map[num_of_stones[i]]++; // store the count of a given array value
}

long long int count[m];
for (int i=0; i<m; i++){
count[i]=0;
}
// we only want to count complements after num_of_stones[i]
for(int j=0; j<m; j++)
    for(int i=0;i<n; i++){	
	count[j]+=map[magic_numbers[j]-num_of_stones[i]];			  
	if(magic_numbers[j]-num_of_stones[i]==num_of_stones[i]){
	count[j]--;
	}
    }

for(int i=0; i<m; i++)
{
printf("%lld ", count[i]/2);
}

return 0;
}
