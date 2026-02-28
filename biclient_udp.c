#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#define max 10
int main()
{
    int sock=socket(AF_INET,SOCK_DGRAM,0);
    struct sockaddr_in srv={AF_INET,htons(8088)};
    inet_pton(AF_INET,"127.0.0.1",&srv.sin_addr);
    char b[1024];
    fd_set fds;
    while(1)
    {
        FD_ZERO(&fds);
        FD_SET(0,&fds);
        FD_SET(sock,&fds);
        select(sock+1,&fds,0,0,0);
        if(FD_ISSET(0,&fds)&&fgets(b,1024,stdin))
        {
           sendto(sock,b,1024,0,(void *)&srv,sizeof(srv));
        }
        if(FD_ISSET(sock,&fds))
        {
           struct sockaddr_in from;
           socklen_t l=sizeof(from);
           int n=recvfrom(sock,b,1023,0,(void *)&from,&l);
           if(n<=0)continue;
           b[n]=0;
           printf("From %s:%d:%s",inet_ntoa(from.sin_addr),ntohs(from.sin_port),b);
        }
     }
     close(sock);
    return 0;

}