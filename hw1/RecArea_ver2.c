#include<iostream>
#include<utility>
#include<vector>
#include<algorithm>
using namespace std;


int rec_area(const pair<int, int>&a ,const pair<int, int>&b){
int length, width;
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
		return (length*width);

}



bool comparison(const pair<long long int,long long int> &a,const pair<long long int,long long int> &b){
    return a.second<b.second;
}


long long int sum_of_all_rectangles(vector<pair<long long int,long long int>> vec,int n){

if(n==1){
return 0;
}


sort(vec.begin(), vec.end());//sorted by X coordinates, stored in vec
 
//cout << "sorted vector a/c to first " << endl;
//for(int i=0; i<n; i++){
//          cout << vec[i].first << " " << vec[i].second << endl;
//    }
vector<pair<long long int,long long int>> vec1;
for (int i=0; i<vec.size(); i++)  //copy from vec to vec1
       vec1.push_back(vec[i]);

sort(vec1.begin(),vec1.end(), comparison);
//sorted by Y coordinates, stored in vec1
int mid_index= n/2;
long long int left_sum, right_sum=0;

vector<pair<long long int,long long int>> left_sided_pairs;

vector<pair<long long int,long long int>> right_sided_pairs;

//int mid_line=( vec[mid_index-1].first+vec[mid_index].first)/2;

for (int i=0; i<vec.size(); i++)  //copy from vec to left_sided_pairs
     if(i<mid_index){  
	left_sided_pairs.push_back(vec[i]);
	}else{
	right_sided_pairs.push_back(vec[i]);	
	}

left_sum= sum_of_all_rectangles(left_sided_pairs, mid_index);
right_sum= sum_of_all_rectangles(right_sided_pairs, n-mid_index);



//sort left-sided and right-sided pairs by Y-coordinates
//
sort(left_sided_pairs.begin(),left_sided_pairs.end(), comparison);
sort(right_sided_pairs.begin(),right_sided_pairs.end(), comparison);



long long int sum_across_mid=0;

//if right side is higher than left side
long long int sum_of_lx=0;

long long int sum_of_ly=0;
long long int sum_of_lxy=0;

//merge
long long int j=0;
long long int cur=0;
int count=0; //count the number of points that are bottom-left and on the left side

       //we use a sweep line i from bottom to top on the right side	
	 //j is a pointer pointing to the left sided pair from bottom to the top
	 //we want to find points on the left hand side and bottom-left of the right sided point
	 
	
for (int i=0; i<n-mid_index; i++){

long long int ry= right_sided_pairs[i].second;
long long int ly;
	if(j== mid_index){
		ly = left_sided_pairs[mid_index-1].second;
	}else{
		ly= left_sided_pairs[j].second;
	}
	if( ly<ry){	
//if there is an equal sign, there will be segmentation fault	
 	while( left_sided_pairs[j].second < right_sided_pairs[i].second &&j<mid_index){            
		     j++ ;
				 count++;
	}
 
	for(int k=cur; k<j; k++){
		sum_of_lx += left_sided_pairs[k].first;  
		sum_of_ly += left_sided_pairs[k].second;
		sum_of_lxy+= left_sided_pairs[k].first*left_sided_pairs[k].second;
	}
		cur=j;
	}
	
	sum_across_mid +=((count)*right_sided_pairs[i].first*right_sided_pairs[i].second-right_sided_pairs[i].second*sum_of_lx-right_sided_pairs[i].first*sum_of_ly+sum_of_lxy);
} 
	 
//add up the sum that is up-left of the right sided point
//reset sum of lx, ly, lxy to 0
long long int sum_of_lxa=0;
long long int sum_of_lya=0;
long long int sum_of_lxya=0;
int counta=0;
long long int l=mid_index-1;
long long int cura=mid_index-1;
// right_sided_pairs.size() 超大。這邊是錯的
for(int k=n-mid_index-1;k>=0; k--){
	
	long long int ly;
	if(l<0){
	 ly =left_sided_pairs[0].second;
	}else{
	 ly=left_sided_pairs[l].second;
	}
	long long int ry=right_sided_pairs[k].second;


	if(ly>ry){	
	while(left_sided_pairs[l].second>right_sided_pairs[k].second &&l>=0){            
		     l-- ;
				 counta++;
	}	 
	for(int x=cura; x>l; x--){
	sum_of_lxa += left_sided_pairs[x].first;  
	sum_of_lya += left_sided_pairs[x].second;
	sum_of_lxya+= left_sided_pairs[x].first*left_sided_pairs[x].second;
	}


	cura=l;
	}
		sum_across_mid +=(-(counta)*right_sided_pairs[k].first*right_sided_pairs[k].second+right_sided_pairs[k].second*sum_of_lxa+right_sided_pairs[k].first*sum_of_lya-sum_of_lxya);
	} 
	

return  right_sum+left_sum+sum_across_mid;
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
//printf("%f", rec_area(x[0], y[0], x[3], y[3])); correctly print rec_area betweeen x1, y1, x4, y4

vector<pair<long long int,long long int>> vect;

for(int i=0; i<n; i++){
 vect.push_back(make_pair(x[i], y[i]));
}

sum= sum_of_all_rectangles(vect, n);

printf("%lld", sum);

return 0;
}

