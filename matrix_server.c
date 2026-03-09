#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdlib.h>
int fact(int);
int main()
{
   int r1,c1,r2,c2,A[5][5]={0},B[5][5],C[5][5];
   int s=socket(AF_INET,SOCK_STREAM,0);
   int opt=1,num;
   char b[2048];
   struct sockaddr_in a={AF_INET,htons(8087),INADDR_ANY};
   setsockopt(s,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
   bind(s,(struct sockaddr*)&a,sizeof(a));
   listen(s,5);
   printf("server running\n\n");
   while(1)
   {
      int len=sizeof(a);
      int cli=accept(s,(struct sockaddr*)&a,&len);
      recv(cli,&r1,sizeof(r1),0);
      recv(cli,&c1,sizeof(c1),0);
      recv(cli,&r2,sizeof(r2),0);
      recv(cli,&c2,sizeof(c2),0);
      printf("Matrix 1:\n\n");
      for(int i=0;i<r1;i++)
      {
       for(int j=0;j<c1;j++)
       {
          recv(cli,&A[i][j],sizeof(A[i][j]),0);
          printf("%d\t",A[i][j]);
       }
        printf("\n");
      }
      printf("\nMatrix 2:\n\n");
      for(int i=0;i<r2;i++)
      {
       for(int j=0;j<c2;j++)
       {
          recv(cli,&B[i][j],sizeof(B[i][j]),0);
          printf("%d\t",B[i][j]);
       }
        printf("\n");
      }
      if(c1==r2)
      {
          for(int i=0;i<r1;i++)
          {
            for(int j=0;j<c2;j++)
            {
               C[i][j]=0;
               for(int k=0;k<c1;k++)
               {
                  C[i][j]+=A[i][k]*B[k][j];
               }
            }
          }
      }
      printf("\nThe resultant matrix\n");
      for(int i=0;i<r1;i++)
      {
        for(int j=0;j<c2;j++)
        {
          printf("%d\t",C[i][j]);
          send(cli,&C[i][j],sizeof(C[i][j]),0);
        }
        printf("\n");
      }

      printf("response send to client....\n");
   }
   return 0;
}
