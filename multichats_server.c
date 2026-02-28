#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
int main()
{

   int lsn=socket(AF_INET,SOCK_STREAM,0);
   struct sockaddr_in addr={AF_INET,htons(8085),INADDR_ANY};
   int opt=1,fdmax=lsn;
   char b[1024],out[1024];
   setsockopt(lsn,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
   struct sockaddr_in cli[FD_SETSIZE];
   bind(lsn,(void*)&addr,sizeof(addr));
   listen(lsn,5);
   printf("server started.....\n");
   fd_set master,fds;
   FD_ZERO(&master);
   FD_SET(lsn,&master);
   while(1)
   {
        fds=master;
        select(fdmax+1,&fds,0,0,0);
        for(int i=0;i<=fdmax;i++)
        {
            if(!FD_ISSET(i,&fds)) continue;
            if(i==lsn)
            {
                socklen_t l=sizeof(addr);
                int fd=accept(i,(void*)&addr,&l);
                if(fd>fdmax) fdmax=fd;
                FD_SET(fd,&master);
                cli[fd]=addr;
                printf("client connected %s: %d",inet_ntoa(addr.sin_addr),ntohs(addr.sin_port));
                int len=snprintf(out,sizeof(out),"Client %s : %d joined ",inet_ntoa(addr.sin_addr),ntohs(addr.sin_port));
                for(int j=0;j<=fdmax;j++)
                {
                    if(FD_ISSET(j,&master)&&j!=lsn)
                         send(j,out,len,0);
                } 
            }
            else
            {
                 int n=recv(i,b,1023,0);
                 if(n<=0)
                 {
                      printf("client disconnected %s: %d",inet_ntoa(addr.sin_addr),ntohs(addr.sin_port));
                      close(i);
                      FD_CLR(i,&master);
                      continue;
                 }
                b[n]=0;
                printf("message from %s : %d : %s",inet_ntoa(addr.sin_addr),ntohs(addr.sin_port),b);
                int len=snprintf(out,sizeof(out),"Client %s : %d joined ",inet_ntoa(addr.sin_addr),ntohs(addr.sin_port));
                for(int j=0;j<=fdmax;j++)
                {
                    if(FD_ISSET(j,&master)&&j!=lsn&&j!=i)
                         send(j,out,len,0);
                } 

            }
        }
        
       





   }
  return 0;
}