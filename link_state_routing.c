#include<stdio.h>
#include<stdlib.h>
#define INF 999
void dijkstra(int G[10][10],int n,int start)
{
    int cost[10],vist[10]={0},next[10],min,u;
    for(int i=0;i<n;i++)
    {
       cost[i]=INF;
       next[i]=-1;
    }
    cost[start]=0;
    for(int count=0;count<n-1;count++)
    {
        min=INF,u=-1;
        for(int i=0;i<n;i++)
        {
           if(!vist[i]&&cost[i]<=min)
           	min=cost[i];
		u=i; 
        }
        if(u==-1) break;
        vist[u]=1;
        for(int i=0;i<n;i++)
        {
            if(!vist[i]&&G[u][i]&&cost[u]!=INF&&cost[u]+G[u][i]<cost[i])
            {
                cost[i]=cost[u] + G[u][i];
                next[i]=(u==start)?i:next[u];
            }
        }
    }
    printf("\nRouter\nDestination\tcost\tnexthop\n");
    for(int i=0;i<n;i++)
    {   
         if(i!=start)
         	printf("%d\t%d\t%d\n",i,cost[i],(cost[i]>=INF)?-1:next[i]);
    }
}

void dijkstra(int G[10][10],int,int);
void main()
{
    int n,G[10][10];
    printf("Enter the number of routers:\n");
    scanf("%d",&n);
    printf("Enter the cost matrix:\n");
    for(int i=0;i<n;i++)
    {
       for(int j=0;j<n;j++)
       {
          scanf("%d",&G[i][j]);
          if(G[i][j]==999) G[i][j]=INF;
       }
    }
    printf("\n.........Routing table........\n");
    for(int i=0;i<n;i++)
    {
       dijkstra(G,n,i);
    }
}
