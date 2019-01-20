#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>

typedef long long ll;

using namespace std;
#define N 10
#define mod  1000000007

int dp[N][N][N][N][100][100]; //
int bit[N];
int arr[2]={1,-1};
void change(char *a)  //处理对于字符串减一操作
{
    int i,j;
    int len=strlen(a);
    len--;
    while(len>=0)
    {
        a[len]--;
        if(a[len]>='0') break;
        a[len]='9';
        len--;
    }
    len=strlen(a);
    for(i=0;i<len-1;i++) if(a[i]>='1') break;
    int k=0;
    for(i;i<len;i++)
        a[k++]=a[i];
    a[k]='\0';
}

ll dfs(int pos,int le,int mid,int ri,int sum,int sum2,bool bound)
{
    if(pos==0) return (le%3==0)&&(mid%3==0)&&(ri%3==0)&&(sum%3==0)&&((100-sum2)%11==0) ? 1:0;
    if(!bound&&dp[pos][le][mid][ri][sum][sum2]>=0) return dp[pos][le][mid][ri][sum][sum2];
    int up=bound ? bit[pos]:9;
    ll ans=0;
    for(int i=0;i<=up;i++)
    {
        if(i==3)
          ans=(ans+dfs(pos-1,le+1,mid,ri,sum+3,sum2+3*arr[pos%2],bound&&i==up))%mod;
        else
          if(i==6)
           ans=(ans+dfs(pos-1,le,mid+1,ri,sum+6,sum2+6*arr[pos%2],bound&&i==up))%mod;
        else
            if(i==9)
             ans=(ans+dfs(pos-1,le,mid,ri+1,sum+9,sum2+9*arr[pos%2], bound&&i==up))%mod;
        else
             ans=(ans+dfs(pos-1,le,mid,ri,sum+i,sum2+i*arr[pos%2],bound&&i==up))%mod;
    }
    if(!bound) dp[pos][le][mid][ri][sum][sum2]=ans;
    return ans;
}


ll solve(char *c)
{
   int i,j;
   int len=strlen(c);
   for(i=1;i<=len;i++)
    bit[i]=c[len-i]-'0';

   return dfs(len,0,0,0,0,100,true)%mod;
}

int main()
{
    int i,j,t;
    char a[N],b[N];
    memset(dp,-1,sizeof(dp));
    scanf("%d",&t);
    while(t--)
    {
        scanf("%s%s",a,b);
        change(a);
        printf("%lld\n",(solve(b)-solve(a)+mod+mod)%mod);//必须+mod % mod 因为可能是负数
    }
    return 0;
}
