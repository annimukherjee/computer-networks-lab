#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> 
#include <string.h>
#include <unistd.h>




int main(){

int ret=socket(AF_INET,SOCK_STREAM,0);

if(ret==-1){
  printf("Not created\n");
  return 1;
  
}
else{
  printf("Socket created %d\n",ret);
 }
 
 
  struct sockaddr_in sent;
 sent.sin_family=AF_INET;
 sent.sin_port=htons(5000);
 sent.sin_addr.s_addr=INADDR_ANY;
 
 int ret1=bind(ret,(const struct sockaddr*)&sent,sizeof(sent));
 
 if(ret1==-1){
     printf("Bind not successful");
     return 1;
   }
   
   else{
     printf("Bind successful %d\n",ret1);
   }
   
   int lis=listen(ret, 5);
   
   if(lis==-1){
   printf("Listen not successful");
   return 1;}
   
   struct sockaddr abc;
    socklen_t a=sizeof(abc);
   
   
   
   int clientSOCK=accept(ret, &abc,
              &a);
              
              
              
              
                char recv_buff[100];
              
              
               ssize_t r= recv(clientSOCK, recv_buff, sizeof(recv_buff),
                        0);
                        
                       if(r==-1){
                        printf("Not successful\n");
                        return -1;
                       }
                       
                       printf("Message recieved is %s\n",recv_buff);

              
              
              
              
              
              
              
              
              
              
              
              
              
             char send_buff[100];
   printf("\nEnter your message\n");
   scanf("%s",send_buff);
                ssize_t  s= send(clientSOCK, send_buff, strlen(send_buff), 0);
                if(s==-1){
                  printf("Sent not successful\n");
                  return 0;
                }
                
                printf("Number of bytes sent succesfully\n");

              
              
              
              
              
              
 
 return 1;               
}