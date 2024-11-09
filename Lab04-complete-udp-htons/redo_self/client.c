#include<stdio.h>
#include<stdlib.h>

#include<netinet/ip.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<strings.h>


#include<sys/types.h>
#include<sys/socket.h>

int main()
{   

    int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

    if(sock_fd==-1)
    {
        printf("Socket creation failed\n");
        exit(1);
    }
    else
    {
        printf("Socket created successfully\n");
    }

    struct sockaddr_in client_struct;
    client_struct.sin_family = AF_INET;
    client_struct.sin_port=htons(6000);
    // client_struct.sin_addr.s_addr = INADDR_ANY;
    inet_aton("127.0.0.1", &client_struct.sin_addr);

    int bind_ret = bind(sock_fd, (const struct sockaddr*)(&client_struct), sizeof(client_struct));

    if(bind_ret==-1)
    {
        printf("Bind creation failed\n");
        exit(1);
    }
    else
    {
        printf("Bind successfully\n");
    }

    int flag = 1;

    while (flag)
    {
        
        // first send stuff

        char send_buff[100];
        printf("Send a message: ");
        fgets(send_buff, sizeof(send_buff), stdin);


        struct sockaddr_in client_server_struct;

        client_server_struct.sin_family = AF_INET;
        client_server_struct.sin_port=htons(5000);
        // client_server_struct.sin_addr.s_addr = INADDR_ANY
        inet_aton("127.0.0.1", &client_server_struct.sin_addr);

        int size =  sizeof(client_server_struct);

        int send_ret = sendto(sock_fd, send_buff, strlen(send_buff), 0, (const struct sockaddr *)(&client_server_struct), size);

        if(send_ret==-1)
        {
            printf("Sending failed\n");
            exit(1);
        }
        else
        {
            printf("Sent successfully");
        }

        // then receive stuff

         char recv_msg_buff[100];


        struct sockaddr_in server_recv_struct;
        int size_struct = sizeof(server_recv_struct);

        int receive_ret = recvfrom(sock_fd, recv_msg_buff, sizeof(recv_msg_buff), 0, (struct sockaddr *)(&server_recv_struct), (socklen_t *)&size_struct);


        if(receive_ret==-1)
        {
            printf("Recv failed\n");
            exit(1);
        }
        else
        {
            printf("Received successfully\n");
            printf("MESSAGE: %s", recv_msg_buff);
            printf("Port number of sender = %d\n", ntohs(server_recv_struct.sin_port));
			printf("IP Address of sender = %s\n", inet_ntoa(server_recv_struct.sin_addr));
        }




    }
    


    return 0;   
}