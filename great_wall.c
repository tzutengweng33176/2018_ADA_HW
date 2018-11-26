#include<iostream>
#include<utility>
#include<vector>
#include<algorithm>
using namespace std;

// An interval has start time and end time 
struct Interval 
{ 
    int start, end; 
}; 

int power_of_interval(Interval i)
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
vector<Interval> insert(vector<Interval> &input, Interval given, int power[], int day)
{
    int sz = input.size();
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
    if (given.start > input[sz - 1].end || given.end < input[0].start)
    {
        if (given.end < input[0].start)
        {
            result.push_back(given);
        }
        for (int i = 0; i < sz; i++)
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

    for (int i = 0; i < sz; i++)
    {
        bool intersect = doesIntersect(input[i], given);
        if (!intersect)  // if NOT overlap
        {
            result.push_back(input[i]);
            // check if given lies between input[i] and input[i+1]
            if (i < sz - 1 && given.start > input[i].end && given.end < input[i+1].start)
            {
                result.push_back(given);
								power[day]+=power_of_interval(given);
            }
						power[day]+=power_of_interval(input[i]);
            continue;
        }
        // Now we know the pair overlaps. Lets find out how many input overlap. 
        int st = i; 
        while (i < sz && intersect)
        {
            i++;
            if (i == sz) 
                intersect = false; 
            else
            {
                intersect = doesIntersect(input[i], given);
            }
        }
        i--;
        // Now all input from st to i overlap. 
        Interval toInsert{min(given.start, input[st].start), max(given.end, input[i].end)};
        result.push_back(toInsert);
				power[day]+=power_of_interval(toInsert);
    }
    return result;
}


int main() {
int n;//number of vertices

scanf("%d", &n); //input n
int x[n], y[n];  //declare two arrays storing l and r
int power[n]; //store the power of each day

for(int i=0; i<n; i++){
  scanf("%d %d",&x[i], &y[i] ); //input a coordinate x, y

}
Interval arr[n]; //an array of Interval, from day 1 to day n

for(int i=0; i<n; i++){
 arr[i]={x[i], y[i]}; 
 power[i]=0;
// printf("%d %d\n", arr[i].start, arr[i].end);
}


vector<Interval> vect;
//traverse the graph from vertex 0
for(int i=0; i<n; i++){
// sort the intervals in increasing order of start time 
// if the vector is NOT empty
  if(!vect.empty()){ 
	sort(vect.begin(), vect.end(), compareInterval);
	}
  vect=insert(vect, arr[i], power, i);


}

for(int i=0; i<n; i++)
{

	printf("%d\n", power[i]);

}



return 0;
}

