#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
int is_prime(int num);
void main()
{
    int opt=1,num,isprime;
    char b[2048];
    int s=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in a={AF_INET,htons(8083),INADDR_ANY};
    setsockopt(s,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
    bind(s,(struct sockaddr*)&a,sizeof(a));
    listen(s,5);
    while(1)
    {
       int len=sizeof(a);
       int cli=accept(s,(struct sockaddr*)&a,&len);
       recv(cli,&num,sizeof(num),0);
       isprime=is_prime(num);
       if(isprime)
       {
          snprintf(b,sizeof(b),"%d is prime\n",num);
       }
       else
       {
          snprintf(b,sizeof(b),"%d is not prime\n",num);
       }
       send(cli,b,sizeof(b),0);

      close(cli);
    }
   close(s);
}
int is_prime(int num)
{
   int flag=1;
   if(num<=1)
   {
      flag=0;
   }
   else
   {
       for(int i=2;i<=num/2;i++)
       {
           if(num%i==0)
           {
              flag=0;
           }
       }
   }
  return flag;
   
}