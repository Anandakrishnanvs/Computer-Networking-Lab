#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>
int main()
{

   int s=socket(AF_INET,SOCK_STREAM,0),n;
   struct sockaddr_in a={AF_INET,htons(8086),INADDR_ANY};
   int opt=1;
   setsockopt(s,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
   bind(s,(struct sockaddr *)&a,sizeof(a));
   listen(s,1);
   char b[1024]={0};
   for(int i=0;i<2;i++)
   {
     n=accept(s,0,0);
     read(n,b,1024);
     printf("%s\n",b);
   }
   
   close(s);
   close(n);
return 0;
}