#include<stdio.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
void main()
{
    int r1,r2,c1,c2,A[5][5],B[5][5],C[5][5];
    int s=socket(AF_INET,SOCK_STREAM,0);
    char b[2048];
    int num;
    struct sockaddr_in a={AF_INET,htons(8087)};
    inet_pton(AF_INET,"127.0.0.1",&a.sin_addr);
    int len=sizeof(a);
    connect(s,(struct sockaddr*)&a,len);
    printf("enter the rows of matrix 1:");
    scanf("%d",&r1);
    send(s,&r1,sizeof(r1),0);
    printf("enter the rows of matrix 1:");
    scanf("%d",&c1);
    send(s,&c1,sizeof(c1),0);
    printf("enter the rows of matrix 2:");
    scanf("%d",&r2);
    send(s,&r2,sizeof(r2),0);
    printf("enter the rows of matrix 2:");
    scanf("%d",&c2);
    send(s,&c2,sizeof(c2),0);
    printf("\nenter the first matrix:\n");
    for(int i=0;i<r1;i++)
    {
       for(int j=0;j<c1;j++)
       {
          scanf("%d",&A[i][j]);
          send(s,&A[i][j],sizeof(A[i][j]),0);
       }
    }
    printf("\nenter the second matrix:\n");
    for(int i=0;i<r2;i++)
    {
       for(int j=0;j<c2;j++)
       {
          scanf("%d",&B[i][j]);
          send(s,&B[i][j],sizeof(B[i][j]),0);
       }
    }
    printf("\nThe resultant matrix:\n\n");
    for(int i=0;i<r1;i++)
    {
        for(int j=0;j<c2;j++)
        {
          recv(s,&C[i][j],sizeof(C[i][j]),0);
          printf("%d\t",C[i][j]);
        }
        printf("\n");
      }

    close(s);
}