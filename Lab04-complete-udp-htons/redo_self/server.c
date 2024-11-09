#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netinet/ip.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>

#include<string.h>
#include<strings.h>

int main()
{

    int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sock_fd==-1)
    {
        printf("Socket creation failed\n");
        exit(1);
    }
    else
    {
        printf("Socket creation successful\n");
    }


    // ---------------------------------------



    printf("Starting to bind\n");

    
    struct sockaddr_in serv_details;
    serv_details.sin_family = AF_INET;
    serv_details.sin_port = htons(5000);
    // serv_details.sin_addr.s_addr = INADDR_ANY;
    // send.sin_addr.s_addr = inet_addr("10.2.248.220");
    
    inet_aton("127.0.0.1", &serv_details.sin_addr);

    int bind_ret = bind(sock_fd, (const struct sockaddr *)&serv_details, sizeof(serv_details));

    if(bind_ret==-1)
    {
        printf("Bind creation failed\n");
        exit(1);
    }
    else
    {
        printf("Bind successfully\n");
    }

    printf("in front of while loop\n");

    int flag =1;
    while (flag)
    {
        // recv first

        char receive_msg_buffer[100];
        struct sockaddr_in receive_struct;
        int size_struct = sizeof(receive_struct);

        int recv_ret = recvfrom(sock_fd, receive_msg_buffer, sizeof(receive_msg_buffer), 0, (struct sockaddr *)(&receive_struct), (socklen_t *)(&size_struct));

        if(recv_ret==-1)
        {
            printf("Received failed");
            exit(1);
        }
        else
        {
            printf("Received successfully\n");
            printf("Message received: %s\n", receive_msg_buffer);
            printf("Port number of sender = %d\n", ntohs(receive_struct.sin_port));
			printf("IP Address of sender = %s\n", inet_ntoa(receive_struct.sin_addr));
        }
    


        // then send response

        char send_msg_buffer[100];
        printf("Enter your message:");
        fgets(send_msg_buffer, sizeof(send_msg_buffer), stdin);

        struct sockaddr_in send_client;
        send_client.sin_family=AF_INET;

        send_client.sin_port = receive_struct.sin_port;

        printf("receive_struct.sin_port: %d\n", htons(receive_struct.sin_port));
        send_client.sin_addr.s_addr = INADDR_ANY; 

        int send_ret = sendto(sock_fd, send_msg_buffer, sizeof(send_msg_buffer), 0, (const struct sockaddr *)(&send_client), sizeof(send_client));


        if(send_ret==-1)
        {
            printf("SENDING failed");
            exit(1);
        }
        else
        {
            printf("SENT successfully");
        }
        


    }
    

    



    return 0;
}