#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>
int main()
{

   int s=socket(AF_INET,SOCK_STREAM,0);
   struct sockaddr_in a={AF_INET,htons(8087)};
   inet_pton(AF_INET,"127.0.0.1",&a.sin_addr);   
   if(connect(s,(struct sockaddr *)&a,sizeof(a))==0)
  {
      printf("connected sucessfully\n");
   }
   fd_set f;
   char b[1024];
   int n;
   while(1)
   {
      FD_ZERO(&f);FD_SET(0,&f);FD_SET(s,&f);
      select(s+1,&f,0,0,0);
      
      if(FD_ISSET(s,&f)&&(n=recv(s,b,1023,0))>0)
      {
         b[n]=0;fputs(b,stdout);
      }
      else if(FD_ISSET(s,&f)) break;
      if(FD_ISSET(0,&f)&&fgets(b,1024,stdin))
         send(s,b,strlen(b),0);
   }
   close(s);
   
return 0;
}