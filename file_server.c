#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
void main()
{
    int s=socket(AF_INET,SOCK_STREAM,0);
    char fname[256],b[4096],c[2048];
    struct sockaddr_in a={AF_INET,htons(8085),INADDR_ANY};
    bind(s,(struct sockaddr *)&a,sizeof(a));
    listen(s,5);
    printf("server running...\n");
    int len=sizeof(a);
    int news=accept(s,(struct sockaddr *)&a,&len);
    int n=recv(news,fname,sizeof(fname),0);
    fname[n]=0;
    FILE *fp =fopen(fname,"r");
    if(fp)
    {
       n=fread(c,1,2047,fp);
       c[n]=0;
       fclose(fp);
       send(news,c,sizeof(c),0);
       printf("requested file is send to client\n");
    }
    else
    {
       perror("file reuested failed to send\n");
    }
   
   close(news);
   close(s);
}