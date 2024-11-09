#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX_CLIENTS 5

int main()
{

    // Created a socket -------------------------------------------
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        printf("Socket not created\n");
        return 1;
    }
    printf("Socket created %d\n", server_socket);
    // ------------------------------------------------------------


    // binding server's socket -----------------------------------------------------------------------------
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5678);
    // server_addr.sin_addr.s_addr = INADDR_ANY;
    inet_aton("127.0.0.1", &server_addr.sin_addr);

    int bind_ret = bind(server_socket, (const struct sockaddr *)&server_addr, sizeof(server_addr));
    if (bind_ret == -1)
    {
        printf("Bind not successful\n");
        return 1;
    }
    printf("Bind successful %d\n", bind_ret);
    // -----------------------------------------------------------------------------------------------------


    // call listen ----------------------------------------------------------------------------------------

    int listen_ret = listen(server_socket, MAX_CLIENTS);
    if (listen_ret == -1)
    {
        printf("Listen not successful\n");
        return 1;
    }
    printf("Server listening on port 5678\n");
    // ------------------------------------------------------------------------------------------------------


    int client_sockets[MAX_CLIENTS];
    struct sockaddr_in client_addrs[MAX_CLIENTS];
    int client_count = 0;
    int pid = 1;

    while (pid)
    {
        if (client_count < MAX_CLIENTS)
        {
            socklen_t addr_len = sizeof(client_addrs[client_count]);
            client_sockets[client_count] = accept(server_socket, (struct sockaddr *)&client_addrs[client_count], &addr_len);
            if (client_sockets[client_count] == -1)
            {
                printf("Accept not successful\n");
                continue;
            }
            char *client_ip = inet_ntoa(client_addrs[client_count].sin_addr);
            int client_port = ntohs(client_addrs[client_count].sin_port);
            printf("Connection accepted from IP: %s, Port: %d\n", client_ip, client_port);

            int client_index = client_count;
            client_count++;
            char recv_buff[100];
            
            
            pid = fork();
            
           if (pid == 0)
            { // Child process
                close(server_socket); // Close listening socket in child process

                // Loop until "bye" message is received
                while (strcmp(recv_buff, "bye") != 0)
                {
                    int recv_ret = recv(client_sockets[client_index], recv_buff, sizeof(recv_buff) - 1, 0);
                    if (recv_ret == -1)
                    {
                        printf("Receive not successful\n");
                        break; // Break the loop on receive error
                    }
                    recv_buff[recv_ret] = '\0'; // Null-terminate the string
                    printf("Message from client %d: %s\n", client_index, recv_buff);

                    // Respond to the client
                    char send_buff[100];
                    snprintf(send_buff, sizeof(send_buff), "Hello from server to client %d", client_index);
                    int send_ret = send(client_sockets[client_index], send_buff, strlen(send_buff), 0);
                    if (send_ret == -1)
                    {
                        printf("Send not successful\n");
                        break; // Break the loop on send error
                    }
                    printf("Message sent to client %d\n", client_index);

                } 

                // Clean up and exit after finishing the conversation
                close(client_sockets[client_index]);
                return 0; // Exit child process
            }
            else if (pid > 0)
            {
                close(client_sockets[client_index]); // Parent closes the socket descriptor for this client
            }
            else
            {
                printf("Fork failed\n");
                return -1;
            }
        }
    }
    close(server_socket);
    return 0;
}