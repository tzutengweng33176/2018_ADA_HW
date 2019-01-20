#include<stdio.h>
using namespace std;

bool is_illuminati_number(unsigned long long n){

if(n%33==0){
	unsigned long long count_3=0;
	unsigned long long count_6=0; 
	unsigned long long count_9=0;
	while(n>0){
		unsigned long long temp=n%10;
		if(temp==3){
			count_3++;
		}else if(temp==6){
			count_6++;
		}else if(temp==9){
			count_9++;
		}
		n=n/10;
	}
	if((count_3%3==0)&&(count_6%3==0)&&(count_9%3==0)){
		return true;
	}else{
		return false;
	}

}else{
	return false;
}

}


int main(){
unsigned long long M = 1000000007;
unsigned long long r, c;
scanf("%llu %llu", &r, &c);

unsigned long long m[r][c];
unsigned long long count[r][c];

for(unsigned long long i=0; i<r; ++i)  //successfully read in a matrix with rows c and columns c
	for(unsigned long long j=0; j<c; ++j)
      {
      scanf("%llu", &m[i][j]);
      }

for(unsigned long long i=0; i<r; ++i)  
	for(unsigned long long j=0; j<c; ++j)
      {
     count[i][j]=0;
      }
unsigned long long ans=0;
if (is_illuminati_number(m[0][0])==true) 	{ 
		//do nothing
}else{
    //Initializing the leftmost column
    
    
		for (unsigned long long i=0; i<r; i++) {
    		{ 
        if (is_illuminati_number(m[i][0] )== false) 
            {count[i][0] = 1;} 
  
        // If we encounter a blocked cell in leftmost 
        // row, there is no way of visiting any cell 
        // directly below it. 
        else
            {break;} 
    		} 
		}  
    // Similarly initialize the topmost row 
    for (unsigned long long i=1; i<c; i++) 
    { 
        if (is_illuminati_number(m[0][i]) == false) 
            {count[0][i] = 1; }
  
        // If we encounter a blocked cell in bottommost 
        // row, there is no way of visiting any cell 
        // directly below it. 
        else
           { break;} 
    } 
  
    // The only difference is that if a cell is -1, 
    // simply ignore it else recursively compute 
    // count value maze[i][j] 
    
    for (unsigned long long i=1; i<r; i++) 
    { 
        for (unsigned long long j=1; j<c; j++) 
        { 
            // If blockage is found, ignore this cell  
            if (is_illuminati_number(m[i][j]) == true) 
                {continue; }
            // If we can reach maze[i][j] from maze[i-1][j] 
            // then increment count. 
            if (count[i-1][j] > 0) 
                {count[i][j] = (count[i][j] + count[i-1][j])%M; 
                }
            // If we can reach maze[i][j] from maze[i][j-1] 
            // then increment count. 
            if (count[i][j-1] > 0) 
                {count[i][j] = (count[i][j] + count[i][j-1])%M;
                }
        } 
    } 
    // If the final cell is blocked, output 0, otherwise 
    // the answer
    
    
    ans= (count[r-1][c-1] > 0)?count[r-1][c-1]%M:0;
								
}
	
printf("%llu\n", ans);
return 0;
}
