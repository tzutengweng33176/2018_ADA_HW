#include<stdio.h>
using namespace std;
//use divide and conquer 重點是merge!! 兩邊都要照y排序  找出左下角的點
//在爬的過程中就會知道
//右邊爬。看左下角。 用C++ pair<int int> 有sort可以用
//先算右邊的矩形和 再算左邊的矩形和  
long long int rec_area(int x1,int y1, int x2, int y2){
int length, width;
if(x1-x2>0){
	width=x1-x2;
}else{
        width=x2-x1;
};
if(y1-y2>0){
	length=y1-y2; 
}else{
	length=y2-y1;
};
return (length*width);

}




int main() {
int n;
long long int sum=0;

scanf("%d", &n); //input n
int x[n], y[n];  //declare two arrays storing x and y coordiantes

for(int i=0; i<n; i++){
  scanf("%d %d",&x[i], &y[i] ); //input a coordinate x, y
  
}
// printf("%d %d", x[2], y[2]);  correctly print x and y coordinates
//printf("%f", rec_area(x[0], y[0], x[3], y[3])); correctly print rec_area between x1, y1, x4, y4

//if you use 2 for loops, you will exceed the time limits
//so we have to think of other algorithms
for(int i=0; i<n; i++ )
	for(int j=i+1; j<n; j++){
	if(x[i]-x[j]==0 ||y[i]-y[j]==0){
	  
	}else{
	
	sum+= rec_area(x[i], y[i], x[j], y[j]);
	};
	}
printf("%lld", sum);
return 0;
}
