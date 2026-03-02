#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>


int main()
{
   int sock = socket(AF_INET,SOCK_DGRAM,0);
   int totalframes,windowsize;
   struct sockaddr_in srv={AF_INET,htons(8089),INADDR_ANY};
   struct sockaddr_in cli;
   int buffer[100]={0};
   struct timeval tv={2,0};
   setsockopt(sock,SOL_SOCKET,SO_RCVTIMEO,(void *)&tv,sizeof(tv));
   printf("enter the number of frames:");
   scanf("%d",&totalframes);
   printf("enter the size of window:");
   scanf("%d",&windowsize);
   int base=1;
   int acked[100]={0};
   while(base<=totalframes)
   {
       for(int i=0;i<windowsize&&(base+i)<=totalframes;i++)
       {
          int frame=(base+i);
          sendto(sock,&frame,sizeof(frame),0,(void *)&srv,sizeof(srv));
          printf("frame %d sent\n",frame);
          sleep(1);
       }
       int response=(base+windowsize<=totalframes)?windowsize:(totalframes-base+1);
       for(int i=0;i<response;i++)
       {
          int len=sizeof(srv);
          int ack;
          int n= recvfrom(sock,&ack,sizeof(ack),0,(void *)&srv,&len);
          if(n<0) 
          {
             printf("ACK not recieved for %d  resending.......\n",base);
             sendto(sock,&base,sizeof(base),0,(void *)&srv,len);
             recvfrom(sock,&ack,sizeof(ack),0,(void *)&srv,&len);
             if(ack>0)
             {
                printf("ACK recieved %d\n",ack);
                acked[ack]=1;
                if(ack==base) base++;

             } 
          }
          else
          {
              if(ack>0)
              {
                printf("ACK recieved %d\n",ack);
                acked[ack]=1;
                while(acked[base]&&base<=totalframes)  base++;
               }
               else
               {
                    printf("ACK not recieved for %d  resending.......\n",base);
                    int NAK=abs(ack);
                    sendto(sock,&NAK,sizeof(NAK),0,(void *)&srv,len);
               }
           }
       }
     if(base>totalframes)break;
   }
 close(sock);
 return 0;
}