#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>
void main()
{
   int list[10];
   int opt=1;
   int s=socket(AF_INET,SOCK_DGRAM,0);
   struct sockaddr_in a={AF_INET,htons(8088),INADDR_ANY};
   setsockopt(s,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
   struct sockaddr_in cli;
   bind(s,(struct sockaddr*)&a,sizeof(a));
  
    int len=sizeof(cli);
    int n;
    recvfrom(s,&n,sizeof(n),0,(struct sockaddr*)&cli,&len);

      for(int i=0;i<n;i++)
      {
         int num;
         recvfrom(s,&list[i],sizeof(list[i]),0,(struct sockaddr*)&cli,&len);
      }
 
    int max=-1; 
    for(int i=0;i<5;i++)
    {
       if(list[i]>max)
       {
         max=list[i];
       }
    } 
  
    sendto(s,&max,sizeof(max),0,(struct sockaddr*)&cli,len);

   
}