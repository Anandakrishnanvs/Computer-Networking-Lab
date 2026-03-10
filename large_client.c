#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>
void main()
{
   int list[10];
   int n;
   int s=socket(AF_INET,SOCK_DGRAM,0);
   struct sockaddr_in a={AF_INET,htons(8088)};
   inet_pton(AF_INET,"127.0.0.1",&a.sin_addr);
   if(connect(s,(struct sockaddr*)&a,sizeof(a))==0)
   {
      printf("enter the number of numbers in the list:");
      scanf("%d",&n);
      sendto(s,&n,sizeof(n),0,(struct sockaddr*)&a,sizeof(a));
      printf("Enter the list of numbers:");
      for(int i=0;i<n;i++)
      {
         scanf("%d",&list[i]);
         sendto(s,&list[i],sizeof(&list[i]),0,(struct sockaddr*)&a,sizeof(a));
      }
      

      int len=sizeof(a);
      int larger;
      recvfrom(s,&larger,sizeof(larger),0,(struct sockaddr*)&a,&len);
      printf("%d is larger\n",larger);
   }
   else
   {
      printf("connection failed\n");
   }
}