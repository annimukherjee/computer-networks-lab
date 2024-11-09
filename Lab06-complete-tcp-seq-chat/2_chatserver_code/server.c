#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX_CLIENTS 4

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    char send_buffer[100];
    char recv_buffer[100];

    if (sockfd == -1)
    {
        printf("Socket not created ! \n");
        exit(1);
    }
    else
    {
        printf("Socket Created successfully\n");
    }

    struct sockaddr_in server_addr;
    

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int b = bind(sockfd, (const struct sockaddr *)(&server_addr), sizeof(server_addr));
    
    if (b == -1)
    {
        printf("Bind Unsuccessful\n");
        exit(1);
    }
    else
    {
        printf("Bind Successful!\n");
    }

    int l = listen(sockfd, 4); // 4 backlog buffer
    if (l == -1)
    {
        printf("Listen unsuccessful !\n");
        exit(1);
    }
    else
    {
        printf("Listen Successful ! \n");
    }

    int client_fds[MAX_CLIENTS];
    int client_count = 0;
    int client_no;

    struct sockaddr_in client_addr;
    int c_size = sizeof(client_addr);

    while (client_count < MAX_CLIENTS)
    {
        int new_client_fd = accept(sockfd, (struct sockaddr *)(&client_addr), (socklen_t *)(&c_size));
        if (new_client_fd == -1)
        {
            printf("Error accepting new connection!\n");
            continue;
        }

        client_fds[client_count] = new_client_fd;
        client_count++;
        printf("Connection established with client %d!\n", client_count);
    }

    while (1)
    {
        int should_run;
        printf("Should the server continue? (0 or 1): ");
        scanf("%d", &should_run);

        if (should_run == 0)
        {
            printf("Closing the server!\n");
            break;
        }

        printf("Enter the client number to send message to (1 to %d): ", client_count);
        scanf("%d", &client_no);
        getchar();

        if (client_no <= 0 || client_no > client_count || client_fds[client_no - 1] == -1)
        {
            printf("Invalid or closed client number!\n");
            continue;
        }

        while (1)
        {

            printf("Enter the message to send: ");
            scanf("%s", send_buffer);
            send(client_fds[client_no - 1], send_buffer, strlen(send_buffer), 0);

            if (strcmp(send_buffer, "bye") == 0)
            {
                printf("Sent 'bye', closing connection with client %d\n", client_no);
                close(client_fds[client_no - 1]);
                client_fds[client_no - 1] = -1;
                break;
            }

            int r = recv(client_fds[client_no - 1], recv_buffer, sizeof(recv_buffer) - 1, 0);
            if (r <= 0)
            {
                printf("Connection closed by the client!\n");
                close(client_fds[client_no - 1]);
                client_fds[client_no - 1] = -1;
                break;
            }
            recv_buffer[r] = '\0';
            printf("Received message from client %d: %s\n", client_no, recv_buffer);

            if (strcmp(recv_buffer, "bye") == 0)
            {
                printf("Client : %d sent 'bye', closing connection!", client_no);
                close(client_fds[client_no - 1]);
                client_fds[client_no - 1] = -1;
                break;
            }
        }
    }

    for (int i = 0; i < client_count; i++)
    {
        if (client_fds[i] != -1)
        {
            send(client_fds[i], "bye", strlen("bye"), 0);
            close(client_fds[i]);
        }
    }

    close(sockfd);
    return 0;
}