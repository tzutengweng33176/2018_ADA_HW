#include<iostream>
#include<utility>
#include<vector>
#include<algorithm>
using namespace std;

// An interval has start time and end time 
struct Interval 
{ 
   long long int start, end; 
}; 

long long int power_of_interval(Interval i)
{
   return (i.end-i.start)*(i.end-i.start);
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
       // if (given.end < input[0].start)
       // {
       //     result.push_back(given);
       // }
        for (long long int i = 0; i < sz; i++)
        {
            result.push_back(input[i]);
        }
        if (given.start > input[sz - 1].end)
        {
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
            // check if given lies between input[i] and input[i+1]
       //     if (i < sz - 1 && given.start > input[i].end && given.end < input[i+1].start)
       //     {
       //         result.push_back(given);
			//					power[day]+=power_of_interval(given);
       //     }
						power[day]+=power_of_interval(input[i]);
            continue;
        }else{
        // Now we know the pair overlaps. Lets find out how many input overlap. 
        long long int st = i; 
     //   while (i < sz && intersect)
     //   {
     //       i++;
     //       if (i == sz) 
     //           intersect = false; 
     //       else
     //       {
     //           intersect = doesIntersect(input[i], given);
     //       }
     //   }
     //   i--;
        // Now all input from st to i overlap. 
        Interval toInsert{min(given.start, input[st].start), given.end};
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
// sort the intervals in increasing order of start time 
// if the vector is NOT empty
  if(!vect.empty()){ 
	sort(vect.begin(), vect.end(), compareInterval);
	}
  vect=insert(vect, arr[i], power, i);


}

for(long long int i=0; i<n; i++)
{

	printf("%lld\n", power[i]);

}



return 0;
}


