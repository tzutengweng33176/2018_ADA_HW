#include<string.h>
#include <stdio.h>
#include<climits>
using namespace std;

typedef long long ll;

//多項式的乘法。不要用hash map 比較i慢，直接開array比較快
//n<50的部分，直接乘。n>=50的部分用多項式的divide and conquer
//keyword: karatsuba polynomial multiplication C++ 

void karatsuba(ll *res, const ll *p, const ll *q, int sz){
    ll t0[sz], t1[sz], r[sz<<1];

    memset(r, 0, (sz<<1) * sizeof(ll));

    if ( sz <= 50 ){ // base case, no recursion, do basic school multiplication
        for ( int i = 0 ; i < sz ; i++ )
            for ( int j = 0 ; j < sz ; j++ ){
                r[i + j] += p[i] * q[j];
            }
    } else {
        // let p = a*x**nSz + b
        //     q = c*x**nSz + d
        //     r = ac*x**sz + ((a+b)*(c+d) - ac - bd)*x**nSz + bd
        int nSz = (sz >> 1);

        for ( int i = 0 ; i < nSz ; i++ ){
            t0[i] = p[i] + p[nSz + i];   // t0 = a + b
            t1[i] = q[i] + q[nSz + i];   // t1 = c + d
            t0[i + nSz] = t1[i + nSz] = 0;  // initialize
        }

        karatsuba(r + nSz, t0, t1, nSz);      // r[nSz...sz] = (a+b) (c+d)
        karatsuba(t0, p, q, nSz);             // t0 = bd
        karatsuba(t1, p + nSz, q + nSz, nSz); // t1 = ac

        for ( int i = 0 ; i < sz ; i++ ){
            r[i] += t0[i];                    // bd
            r[i + nSz] -= t0[i] + t1[i];      // ((a+b)(c+d) - ac - bd) * x**nSz
            r[i + sz] += t1[i];               // ac * x**sz
        }
    }

    memcpy(res, r, (sz<<1) * sizeof(ll));
}

// multiply two polynomials p and q, both of size sz = degree + 1
// save the output in array r
// NOTE: the maximum capacity of p, q, r should be power of two
// NOTE: r should be at least double of p or q in size
void polyMult(ll *r, ll *p, ll *q, int sz){
    if ( sz & (sz - 1) ){ // if size is not power of two
        int k = 1;
        while ( k < sz ) k <<= 1;
        while ( ++sz <= k ) p[sz - 1] = q[sz - 1] = 0;
        sz--;
    }

    karatsuba(r, p, q, sz);
}

int main() {
int n;//the number of piles
int m; //the number of queries


scanf("%d", &n); //input n
int num_of_stones[n];//the number of stones of the 𝑖𝑡ℎ pile
for(int i=0; i<n; i++){
  scanf("%d",&num_of_stones[i]); 
}

scanf("%d", &m);

long long magic_numbers[m]; //the magic number of the i-th query

for(int j=0; j<m; j++){
  scanf("%lld", &magic_numbers[j]); //input a

}


long long array[300000];  //array 如果開太小會run time error
int max_degree=0;
//index of the array is 指數
//value of the array is coefficients
for(int i=0; i<300000; i++){
	array[i]=0;
}
for(int i=0; i<n; i++){
	if(num_of_stones[i]>max_degree){
		max_degree=num_of_stones[i];
}
	
array[num_of_stones[i]]++;

} //count the number of piles of stones
int poly_size=max_degree+1;

long long array2[300000]; //store the multiple of two polynomials
//array2 開太小會run time error 
for(int i=0; i<300000; i++){
	array2[i]=0;
}

polyMult(array2, array, array,poly_size );
//printf("%d ", max_degree); OK
//array storing coefficients OK
//for(int i=0; i<max_degree+1; i++){
//printf("%d ", array2[i]); //OK
//}

for(int i=0; i<m; i++){
if(magic_numbers[i]>200000){
    
		printf("%d ", 0);
}else{
		if(magic_numbers[i]%2==0){ //if magic number is even
	long long	ans= (array2[magic_numbers[i]]-array[magic_numbers[i]/2])/2;
		printf("%lld ", ans);
		}else{
		printf("%lld ", array2[magic_numbers[i]]/2);
		}
}	
}

}

