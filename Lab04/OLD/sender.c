#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <arpa/inet.h>

int main()
{
    int flag = 1;
    int ret = socket(AF_INET, SOCK_DGRAM, 0);
    
    if (ret == -1)
    {
        printf("Socket creation failed");
        exit(1);
    }
    else
    {
        printf("Socket creation successfully\n");
    }

    struct sockaddr_in sent;
    sent.sin_family = AF_INET;

    sent.sin_port = htons(6000);
    sent.sin_addr.s_addr = inet_addr("127.0.0.1");

    int ret1 = bind(ret, (const struct sockaddr *)&sent, sizeof(sent));
    
    if (ret1 == -1)
    {
        printf("Bind failed");
    }
    else
    {
        printf("Bind successfully\n");
    }


    while (flag)
    {
        // send message
        char send_buff[100];
        printf("Please enter the message to send:");
        scanf("%[^\n]%*c", send_buff);
        struct sockaddr_in send;
        send.sin_family = AF_INET;

        send.sin_port = htons(5500);
        send.sin_addr.s_addr =  inet_addr("127.0.0.1");

        int size = sizeof(send);
        int res = sendto(ret, send_buff, strlen(send_buff), 0, (const struct sockaddr *)(&send), size);
        if (res == -1)
            printf("Send failed");
        
        else
        {
            printf("Successful\n");
            if (send_buff[0] == 'e' && send_buff[1] == 'x' && send_buff[2] == 'i' && send_buff[3] == 't')
                exit(0);
        }

        // recieve message
        char recv_buff[100];
        struct sockaddr_in recv;
        int size2 = sizeof(recv);


        // recvfrom(file_descriptor, buffer, length_buffer, flag, stucture, )
        int res2 = recvfrom(ret, recv_buff, sizeof(recv_buff), 0, (struct sockaddr *)(&recv), (socklen_t *)(&size2));
        if (res2 == -1)
        {
            printf("Recieved failed");
        }
        else
        {
            if (recv_buff[0] == 'e' && recv_buff[1] == 'x' && recv_buff[2] == 'i' && recv_buff[3] == 't')
            {
                exit(0);
            }
            printf("\n%s\n", recv_buff);
            printf("%d\n", ntohs(recv.sin_port));
            printf("%s\n", inet_ntoa(recv.sin_addr));

        }
    }
}
