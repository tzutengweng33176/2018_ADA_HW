#include<iostream>
#include<utility>
#include<vector>
#include<algorithm>
using namespace std;

// An interval has start time and end time 
struct Interval 
{ 
   long long int start, end;
   long long int back_pt=0; 
}; 

long long int power_of_interval(Interval i)
{
  long long int num=i.end-i.start;
	long long int sq=0;
	for(long long int i=0; i<num; i++){
	sq+=num;
	}
	
	return sq; 
}


// Compares two intervals according to their staring time. 
// This is needed for sorting the intervals using library 
// function std::sort(). See http://goo.gl/iGspV 
bool compareInterval(Interval i1, Interval i2) 
{ 
    return (i1.start < i2.start); 
} 


bool doesIntersect(Interval a, Interval b)
{
    if (min(a.end, b.end) < max(a.start, b.start))
        return false;
    return true;
}
//input vector must be sorted in order of start times
vector<Interval> insert(vector<Interval> &input, Interval given, long long int power[],long long int day)
{
    long long int sz = input.size();
    vector<Interval> result; 

    // check corner cases
    // Case : Empty input array
    if (sz == 0)
    {
        result.push_back(given);
		power[day]=power_of_interval(given);
        return result;
    }
    // Case : given comes at the beginning or at the end without overlap 
    if (given.start > input[sz - 1].end)
    {
    
        for (long long int i = 0; i < sz; i++)
        {
            result.push_back(input[i]);
        }
        if (given.start > input[sz - 1].end)
        {
           given.back_pt=day; 
					 result.push_back(given);
        }
		power[day]=power[day-1]+power_of_interval(given);
        return result;
    }

    for (long long int i = 0; i < sz; i++)
    {
        bool intersect = doesIntersect(input[i], given);
        if (!intersect)  // if NOT overlap
        {
            result.push_back(input[i]);

            continue;
        }else{
        // Now we know the pair overlaps. Lets find out how many input overlap. 
        if(i!=0){
				power[day]+=power[input[i-1].back_pt];
			}

		long long int st = i; 

        // Now all input from st to i overlap. 
        Interval toInsert{min(given.start, input[st].start), given.end, day};
        result.push_back(toInsert);
				power[day]+=power_of_interval(toInsert);
				break;
				}
    }
    return result;
}


int main() {
long long int n;//number of vertices

scanf("%lld", &n); //input n
long long int x[n], y[n];  //declare two arrays storing l and r
long long int power[n]; //store the power of each day

for(long long int i=0; i<n; i++){
  scanf("%lld %lld",&x[i], &y[i] ); //input a coordinate x, y

}
Interval arr[n]; //an array of Interval, from day 1 to day n

for(long long int i=0; i<n; i++){
 arr[i]={x[i], y[i]}; 
 power[i]=0;
// printf("%d %d\n", arr[i].start, arr[i].end);
}
//the interval is already sorted by ending time

vector<Interval> vect;
//traverse the graph from vertex 0
for(long long int i=0; i<n; i++){

  vect=insert(vect, arr[i], power, i);


}

for(long long int i=0; i<n; i++)
{

	printf("%lld\n", power[i]);

}



return 0;
}


