#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdlib.h>
int fact(int);
int main()
{
   int s=socket(AF_INET,SOCK_STREAM,0);
   int opt=1,num;
   char b[2048];
   struct sockaddr_in a={AF_INET,htons(8087),INADDR_ANY};
   setsockopt(s,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
   bind(s,(struct sockaddr*)&a,sizeof(a));
   listen(s,5);
   printf("server running\n");
   while(1)
   {
      int len=sizeof(a);
      int cli=accept(s,(struct sockaddr*)&a,&len);
      recv(cli,&num,sizeof(num),0);
      int n=fact(num);
      snprintf(b,sizeof(b),"factorial of %d : %d\n",num,n);
      send(cli,b,sizeof(b),0);
      printf("response send to client....\n");
   }
   return 0;
}
int fact(int num)
{
    int n=1;
    for(int i=1;i<=num;i++)
    {
       n=n*i;
    }
    return n; 
}