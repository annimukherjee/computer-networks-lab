#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include <unistd.h>

int main()
{
    int sockfd=socket(AF_INET,SOCK_STREAM ,0);
    char send_buffer[100];
    char recv_buffer[100];
    if(sockfd==-1)
    {
        printf("Socket not created ! \n");
        exit(1);
    }
    else
        printf("Socket Created successfully\n");
    struct sockaddr_in server_addr;
    int c_size=sizeof(server_addr);
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(5000);
    server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    int c=connect(sockfd, (const struct sockaddr *)&server_addr,sizeof(server_addr));   
    if(c==-1)
    {
        printf("Connection unsuccessful\n");
        close(sockfd);
        exit(1);
    }
    else
    {
        printf("Connection successful\n");
    }

    
while(1){
int b=recv(sockfd,recv_buffer,sizeof(recv_buffer)-1,0);
recv_buffer[b]='\0';
if(b==-1)
{
printf("The connection is closed by the server !");
break;
}
printf("Received message : %s \n",recv_buffer);
if(strcmp(recv_buffer,"bye")==0)
{
printf("Sent bye closing the server\n");
break;
}
printf("Enter message : ");
scanf("%s",send_buffer);
send(sockfd, send_buffer,strlen(send_buffer), 0);
if(strcmp(send_buffer,"bye")==0)
{
printf("Sent , bye closing connection\n");
break;
}
}
close(sockfd);
return 0;
}