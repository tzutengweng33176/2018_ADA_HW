#include<stdio.h>
using namespace std;

bool is_illuminati_number(int n){

if(n%33==0){
	int count_3=0, count_6=0, count_9=0;
	while(n>0){
		int temp=n%10;
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
int r, c;
scanf("%d %d", &r, &c);

int m[r][c];
int count[r][c];




for(int i=0; i<r; ++i)  //successfully read in a matrix with rows c and columns c
	for(int j=0; j<c; ++j)
      {
      scanf("%d", &m[i][j]);
      }

for(int i=0; i<r; ++i)  
	for(int j=0; j<c; ++j)
      {
     count[i][j]=0;
      }
int ans=0;
if (is_illuminati_number(m[0][0])==true) 	{ 
		ans=0; 
}else{
    //Initializing the leftmost column 
		for (int i=0; i<r; i++) 
    		{ 
        if (is_illuminati_number(m[i][0] )== false) 
            count[i][0] = 1; 
  
        // If we encounter a blocked cell in leftmost 
        // row, there is no way of visiting any cell 
        // directly below it. 
        else
            break; 
    		} 
  
    // Similarly initialize the topmost row 
    for (int i=1; i<c; i++) 
    { 
        if (is_illuminati_number(m[0][i]) == false) 
            count[0][i] = 1; 
  
        // If we encounter a blocked cell in bottommost 
        // row, there is no way of visiting any cell 
        // directly below it. 
        else
            break; 
    } 
  
    // The only difference is that if a cell is -1, 
    // simply ignore it else recursively compute 
    // count value maze[i][j] 
    for (int i=1; i<r; i++) 
    { 
        for (int j=1; j<c; j++) 
        { 
            // If blockage is found, ignore this cell  
            if (is_illuminati_number(m[i][j]) == true) 
                continue; 
  
            // If we can reach maze[i][j] from maze[i-1][j] 
            // then increment count. 
            if (count[i-1][j] > 0) 
                count[i][j] = (count[i][j] + count[i-1][j]); 
  
            // If we can reach maze[i][j] from maze[i][j-1] 
            // then increment count. 
            if (count[i][j-1] > 0) 
                count[i][j] = (count[i][j] + count[i][j-1]); 
        } 
    } 
  
    // If the final cell is blocked, output 0, otherwise 
    // the answer 
    ans= (count[r-1][c-1] > 0)? count[r-1][c-1] : 0;
								}
	
printf("%d", ans);
//for(int i=0; i<r; ++i)
  //      for(int j=0; j<c; ++j)
    //    {
      //      printf("%d  ", count[i][j]);
     //       if(j == c-1)
     //           printf("\n");
       // }


return 0;
}
