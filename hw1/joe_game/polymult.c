// http://code.geeksforgeeks.org/JuWU7P
// Simple Divide And Conquer C++ program to multiply two polynomials
// Complexity O(n^1.58..)
// Check Results
// http://www.wolframalpha.com/widget/widgetPopup.jsp?p=v&id=11a5b5ef81cff76a0a1f3d042f635df3
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
typedef long long ll;

// polynomial coefficients are saved in increasing order of degree
// coefficient of x**i in polynomial p = p[i]

// multiply polynomials p and q, both of size sz,
// where sz is multiple of 2
void karatsuba(ll *res, const ll *p, const ll *q, int sz){
    ll t0[sz], t1[sz], r[sz<<1];

    memset(r, 0, (sz<<1) * sizeof(ll));

    if ( sz <= 4 ){ // base case, no recursion, do basic school multiplication
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

// print polynomial in descending order of degree
void polyPrint(ll *p, int sz){
    while ( --sz >= 0 ) cout << p[sz] <<" ";
    puts("");
}

int main(){
    ll p[10] = {1, 2, 3, 1, 1, 1, 0, 0 , 0 , 1};
    ll q[10] = {1, 2, 3, 1, 1, 1, 0, 0, 0, 1};
    ll r[20];
    int degree = 9;

    polyMult(r, p, q, degree + 1);
    polyPrint(r, degree * 2 + 1);
    return 0;
}
