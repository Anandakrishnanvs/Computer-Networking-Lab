#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
int main()
{
   char b[1024];
   int s=socket(AF_INET,SOCK_STREAM,0),n;
   struct sockaddr_in a={AF_INET,htons(8085),INADDR_ANY};
   int opt=0;
   setsockopt(s,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
   printf("server live.......");
   bind(s,(struct sockaddr *)&a,sizeof(a));
   listen(s,3);
   n=accept(s,0,0);
  
   while(1)
   {
      memset(b,0,1024);
      if(read(n,b,1024)<=0 || !strncmp(b,"exit",4))
         break;
      printf("client:%s\tserver:",b);
      fgets(b,1024,stdin);
      send(n,b,strlen(b),0);
      if(!strncmp(b,"exit",4))
         break;
   }
   
   
   close(n);
   close(s);
    return 0;
}