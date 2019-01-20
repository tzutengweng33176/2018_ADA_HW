#include<iostream>
#include<utility>
#include<vector>
#include<algorithm>
using namespace std;

int cal_loneliness(const pair<int, int>&a ,const pair<int, int>&b){ //calculate the loneliness of two points
int length, width;
int lone_value=0;
  if(a.first-b.first>0){// if x1-x2>0
        width=a.first-b.first;
  }else{ //if x1-x2<=0
        width=b.first-a.first;
  };
	if(a.second-b.second>0){
        length=a.second-b.second;
	}else{
        length=b.second-a.second;
	};
	lone_value=((length+width)/3)*2+ (length+width)%3;
	return lone_value;

}


int main() {
int n;

scanf("%d", &n); //input n
int x[n], y[n];  //declare two arrays storing x and y coordiantes
int loneliness[n]; //store the loneliness of each horse


for(int i=0; i<n; i++){
  scanf("%d %d",&x[i], &y[i] ); //input a coordinate x, y

}

vector<pair<int,int>> vect;


for(int i=0; i<n; i++){
 vect.push_back(make_pair(x[i], y[i]));
}

for(int i=0;i<n; i++){
	int temp=0;
	for(int j=0; j<n; j++){
	temp+=cal_loneliness(vect[i], vect[j]);
	
	}
	loneliness[i]=temp;
}

for(int i=0;i<n; i++){

printf("%d\n", loneliness[i]);
}
return 0;
}
