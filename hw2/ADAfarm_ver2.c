#include<iostream>
#include<utility>
#include<vector>

using namespace std;

long long int cal_loneliness(const pair<long long int,long long int>&a ,const pair<long long int,long long int>&b){ //calculate the loneliness of two points
long long int length, width;
long long int lone_value=0;
   
   if(a.first-b.first!=0 && a.second-b.second!=0){
  	
		 if(a.first-b.first>0){// if x1-x2>0
        width=a.first-b.first;
  	 }else{ 
        width=b.first-a.first;
    };
			if(a.second-b.second>0){
        length=a.second-b.second;
			}else{
        length=b.second-a.second;
		};
		double m= double(length)/double(width); 	
    printf("The m is:  %f", m);
		if(m>2||m<0.5){
			if(length>width){
			lone_value= length;
			}else{
			lone_value=width;
			}

		}else{
			lone_value=((length+width)/3)*2+ (length+width)%3;
		};
	 
	 } else if(a.first-b.first==0){ //if x1-x2=0 
       if(a.second-b.second>0){
        lone_value=a.second-b.second;
	}else{
        lone_value=b.second-a.second;
	}; 
   }else if(a.second-b.second==0){ //if y1-y2=0
        if(a.first-b.first>0){
            lone_value=a.first-b.first;
	    }else{
            lone_value=b.first-a.first;
	}; 

   };
	return lone_value;

}


int main() {
long long int n;

scanf("%lld", &n); //input n
long long int x[n], y[n];  //declare two arrays storing x and y coordiantes
long long int loneliness[n]; //store the loneliness of each horse

for(int i=0; i<n; i++){
loneliness[i]=0;
x[i]=0;
y[i]=0;
}


for(long long int i=0; i<n; i++){
  scanf("%lld %lld",&x[i], &y[i] ); //input a coordinate x, y

}

vector<pair<long long int,long long int>> vect;


for(long long int i=0; i<n; i++){
 vect.push_back(make_pair(x[i], y[i]));
}

for(long long int i=0;i<n; i++){
	long long int temp=0;
	for(long long int j=0; j<n; j++){
	
		temp+=cal_loneliness(vect[i], vect[j]);
	
	}
	loneliness[i]=temp;
}

for(long long int i=0;i<n; i++){

printf("%lld\n", loneliness[i]);
}
return 0;
}
