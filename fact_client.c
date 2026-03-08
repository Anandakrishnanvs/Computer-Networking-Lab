#include<stdio.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
void main()
{
    int s=socket(AF_INET,SOCK_STREAM,0);
    char b[2048];
    int num;
    struct sockaddr_in a={AF_INET,htons(8087)};
    inet_pton(AF_INET,"127.0.0.1",&a.sin_addr);
    if(connect(s,(struct sockaddr*)&a,sizeof(a))==0)
    {
       printf("enter the number:");
       scanf("%d",&num);
       send(s,&num,sizeof(num),0);
       int n=recv(s,b,sizeof(b),0);
       b[n]=0;
       printf("%s",b);
    }
    else
    {
        printf("connection failed\n");
    }
    close(s);
}
 
