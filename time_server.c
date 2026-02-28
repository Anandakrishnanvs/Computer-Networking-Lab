#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>
#include<time.h>
#define max 10
int main()
{
    int sock=socket(AF_INET,SOCK_DGRAM,0);
    struct sockaddr_in srv={AF_INET,htons(8088),INADDR_ANY};
    bind(sock,(void *)&srv,sizeof(srv));
    char b[1024];
    while(1)
    {
       struct sockaddr_in cli;
       socklen_t l=sizeof(cli);
       int n=recvfrom(sock,b,1024,0,(void *)&cli,&l);
       if(n<=0) continue;
       b[n]=0;
       printf("Time request from %s:%d\n",inet_ntoa(cli.sin_addr),ntohs(cli.sin_port));
       time_t now=time(NULL);
       char *timestr=ctime(&now);
       sendto(sock,timestr,strlen(timestr),0,(void *)&cli,l);
       printf("sent:%s\n",timestr);
    }



   close(sock);






 return 0;
}
