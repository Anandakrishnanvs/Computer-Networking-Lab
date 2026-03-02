#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>


int main()
{
   int sock = socket(AF_INET,SOCK_DGRAM,0);
   int expectedframe=1;
   struct sockaddr_in srv={AF_INET,htons(8089),INADDR_ANY};
   struct sockaddr_in cli;
   int buffer[100]={0};
   int frame;
   bind(sock,(void *)&srv,sizeof(srv));
   printf("Reciever running..............\n");
   while(1)
   {
       int recv_frame;
       int len=sizeof(cli);
       recvfrom(sock,&recv_frame,sizeof(recv_frame),0,(void *)&cli,&len);
       if(recv_frame==expectedframe)
       {
           printf("frame %d recieved  acknowledgment sent for %d\n ",recv_frame,recv_frame);
           sendto(sock,&expectedframe,sizeof(recv_frame),0,(void *)&cli,sizeof(cli));
           expectedframe++;
           
           while(buffer[expectedframe]==1)
           {
              printf("frame %d recieved  acknowledgment sent for %d \n",recv_frame,recv_frame);
              sendto(sock,&recv_frame,sizeof(recv_frame),0,(void *)&cli,sizeof(cli));
              expectedframe++;
           }

       } 
       else if(recv_frame>expectedframe)
       {  
          printf("recieved frame %d  expected frame %d\n",recv_frame,expectedframe);
          int NAK=-expectedframe;
          printf("Sending NAK for %d\n",expectedframe);
          sendto(sock,&NAK,sizeof(NAK),0,(void *)&cli,sizeof(cli));
           
          if(recv_frame<100)
          {
             buffer[recv_frame]=1;
          }

       }
   }
   close(sock);
  return 0;
}