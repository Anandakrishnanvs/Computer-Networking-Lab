#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#define max 10
int main()
{
    int sock=socket(AF_INET,SOCK_DGRAM,0);
    struct sockaddr_in srv={AF_INET,htons(8088),INADDR_ANY};
    bind(sock,(void *)&srv,sizeof(srv));
    struct sockaddr_in clients[max];
    int client_count=0;
    char b[1024];
    fd_set fds;
    while(1)
    {

      FD_ZERO(&fds);
      FD_SET(0,&fds);
      FD_SET(sock,&fds);
      select(sock+1,&fds,0,0,0);
      if(FD_ISSET(sock,&fds))
      {
          struct sockaddr_in cli;
          socklen_t l=sizeof(cli);
          int n=recvfrom(sock,b,sizeof(b),0,(void *)&cli,&l);
          if(n<=0) continue;
          b[n]=0;
          printf("From %s:%d :%s\n",inet_ntoa(cli.sin_addr),ntohs(cli.sin_port),b);
          
          int found=0;
          for(int i=0;i<client_count;i++)
          {
             if(clients[i].sin_port==cli.sin_port&&clients[i].sin_addr.s_addr==cli.sin_addr.s_addr)
             {
                 found=1;
                 break;
             }
          }
          if(!found && client_count<max)
          {
             clients[client_count++]=cli;
             printf("New client joined %s : %d\n",inet_ntoa(cli.sin_addr),ntohs(cli.sin_port));
          }
 
          char echo[1024];
          int len=snprintf(echo,sizeof(echo),"[echo]%s",b);
          sendto(sock,echo,len,0,(void *)&cli,l);
       }
       if(FD_ISSET(0,&fds)&&fgets(b,1024,stdin))
       {
           for(int i=0;i<client_count;i++)
           {
               sendto(sock,b,sizeof(b),0,(void *)&clients[i],sizeof(clients[i]));
           }
       }
    }
   close(sock);
   return 0;
}
