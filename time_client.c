#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>
int main()
{
    int sock=socket(AF_INET,SOCK_DGRAM,0);
    struct sockaddr_in srv={AF_INET,htons(8088)};
    inet_pton(AF_INET,"127.0.0.1",&srv.sin_addr);
    char b[1024];
    char *req="Time";
    sendto(sock,req,strlen(req),0,(void *)&srv,sizeof(srv));
    printf("TIme request sent...\n");
    struct sockaddr_in from;
    socklen_t l=sizeof(from);
    int n=recvfrom(sock,b,1023,0,(void *)&from,&l);
    b[n]=0;
    printf("server time:%s\n",b);
   

close(sock);

 return 0;
}
