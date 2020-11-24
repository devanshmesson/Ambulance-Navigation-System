#include<stdio.h>
#include<time.h>

#ifndef ONLINE_JUDGE
#define freopen freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
#else
#define freopen //comment
#endif

#define int long long int
int mat[60][60];
int TSP_DP(int bitmask,int prevnode,int check,int nodes,int cost,int finalcost) //generating 2^n subsets
{
  if(bitmask==check){return mat[prevnode][0];}
  for(int i=0;i<nodes;i++)
  {
    if((bitmask&(1<<i))==0) //if (i+1)th vertex is procressed for this particular path or not
    {
      cost=mat[prevnode][i] + TSP_DP((bitmask |(1<<i)),i,check,nodes,cost,finalcost);//Recursion
      if(finalcost>cost )finalcost=cost; //taking minimum of all costs
    }
  }
  return finalcost;
}
int main()
{
  //freopen
  int nodes,edges,bitmask=1,prevnode=0,check,cost,finalcost=1e18,distance,a,b;
  scanf("%lld%lld",&nodes,&edges);
  check=(1<<nodes)-1;

  for(int i=0;i<=59;i++)for(int j=0;j<=59;j++)mat[i][j]=0;


  for(int i=0;i<edges;i++)
  {
      scanf("%lld%lld%lld",&a,&b,&distance);
      a--;b--;
      if(mat[a][b]>distance) //For Multiple edges
      {
        mat[a][b]=distance;
        mat[b][a]=distance;
      }
      else
      {
       mat[a][b]=distance;
       mat[b][a]=distance;
      }
  }
  time_t start,end;
  start=clock();
  int answer=TSP_DP(bitmask,prevnode,check,nodes,cost,finalcost);
  printf("Answer=%lld\n",answer);
  end=clock();

  double num=end-start;
  double den=CLOCKS_PER_SEC;
  double time=num/den;
  printf("\nTime=%f",time);
}
