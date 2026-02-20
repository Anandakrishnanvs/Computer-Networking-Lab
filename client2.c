#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>
int main()
{

   int s=socket(AF_INET,SOCK_STREAM,0);
   struct sockaddr_in a={AF_INET,htons(8086)};
   inet_pton(AF_INET,"127.0.0.1",&a.sin_addr);
   char *m="Hello world 2";
   
   if(connect(s,(struct sockaddr *)&a,sizeof(a))==0)
  {
      send(s,m,13,0);
      printf("msg sent sucessfully\n");
   }
   
   close(s);
   
return 0;
}