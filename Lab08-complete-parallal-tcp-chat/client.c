#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <arpa/inet.h>

int main()
{
    int ret = socket(AF_INET, SOCK_STREAM, 0);
    if (ret == -1)
    {
        printf("Socket not created\n");
        return 1;
    }
    printf("Socket created %d\n", ret);

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(5678);
    server.sin_addr.s_addr = INADDR_ANY;

    int connection = connect(ret, (const struct sockaddr *)&server, sizeof(server));
    if (connection != 0)
    {
        printf("Connection unsuccessful\n");
        return -1;
    }
    printf("Connected to server\n");

    struct sockaddr_in l_addr;
    socklen_t addr_len = sizeof(l_addr);
    getsockname(ret, (struct sockaddr *)&l_addr, &addr_len);

    char *server_ip = inet_ntoa(l_addr.sin_addr);
    int server_port = ntohs(l_addr.sin_port);
    printf("Connected from IP: %s, Port: %d\n", server_ip, server_port);
    while (1)
    {
        /////////////
        char send_buff[100];
        printf("Enter your message: ");
        scanf("%s", send_buff);

        int s = send(ret, send_buff, strlen(send_buff), 0);
        if (s == -1)
        {
            printf("Send not successful\n");
            return -1;
        }
        char recv_buff[100];
        int r = recv(ret, recv_buff, sizeof(recv_buff) - 1, 0);
        if (r == -1)
        {
            printf("Receive not successful\n");
            return -1;
        }
        recv_buff[r] = '\0';
        printf("Message from server: %s\n", recv_buff);
    }

    // close(ret);
    return 0;
}