#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
int main()
{
   char b[1024];
   int s=socket(AF_INET,SOCK_STREAM,0),n;
   struct sockaddr_in a={AF_INET,htons(8085)};
   inet_pton(AF_INET,"127.0.0.1",&a.sin_addr);
   
   if(connect(s,(struct sockaddr *)&a,sizeof(a))<0)
        return 1;
   while(1)
   {
      printf("client:");
      fgets(b,1024,stdin);
      send(s,b,strlen(b),0);
      
       if(!strncmp(b,"exit",4))
         break;
  
       memset(b,0,1024);
        if(read(s,b,1024)<=0 || !strncmp(b,"exit",4))
         break;
      printf("server:%s",b);
   }
  
   close(s);
    return 0;
}