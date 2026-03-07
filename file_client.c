#include<stdio.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
void main()
{
    int s=socket(AF_INET,SOCK_STREAM,0);
    char fname[256],b[2048];
    struct sockaddr_in a={AF_INET,htons(8085)};
    inet_pton(AF_INET,"127.0.0.1",&a.sin_addr);
    if(connect(s,(struct sockaddr*)&a,sizeof(a))==0)
    {
       printf("enter the reuqested file:");
       scanf("%s",fname);
       send(s,fname,strlen(fname),0);
       int n=recv(s,b,sizeof(b),0);
       b[n]=0;
       printf("file content:%s",b);
    }
    else
    {
        printf("connection failed\n");
    }
    close(s);
}
 
