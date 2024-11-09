#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<strings.h>
#include<netinet/ip.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main()
{
    int flag =1;

    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    if(sock_fd == -1) {
		printf("Socket creation failed\n");
		exit(1);
	} else {
		printf("Socket created successfully\n");
	}




    struct sockaddr_in server_info;
    server_info.sin_family = AF_INET;
    server_info.sin_port = htons(5000);
    inet_aton("127.0.0.1", &server_info.sin_addr);

    int bind_fd = bind(sock_fd, (const struct sockaddr *)(&server_info), sizeof(server_info));

    if (bind_fd == -1)
	{
		printf("Bind creation failed\n");
		exit(1);
	}
	else
		printf("Bind created successfully\n");
	printf("\n");


    int listen_fd = listen(sock_fd, 5);

    struct sockaddr_in accept_conn1_struct;    // this will be populated by the OS!
	socklen_t sizee = sizeof(accept_conn1_struct);
	int accept1_fd = accept(sock_fd, (struct sockaddr *)&accept_conn1_struct, &sizee);

    

    

    while(flag)
    {

        char recv_buff[100];
        int receive_fd = recv(accept1_fd, recv_buff, sizeof(recv_buff), 0);

        if (receive_fd == -1)
		{
			printf("API recv failed\n");
			exit(1);
		}
		else if (receive_fd > 0)
		{
			printf("Received msg: %s\n", recv_buff);
			printf("Port number of sender = %d\n", ntohs(accept_conn1_struct.sin_port));
			printf("IP Address of sender = %s\n", inet_ntoa(accept_conn1_struct.sin_addr));

			if (strcasecmp(recv_buff, "bye") == 0)
				exit(1);
		}



        ////


		char send_buff[100];
		printf("\nEnter the msg to send : \n");
		fgets(send_buff, sizeof(send_buff), stdin);
		printf("\n");
          
		// send_buff[len-1] = '\0';






		int send_fd = send(accept1_fd, send_buff, strlen(send_buff), 0);

        if (send_fd == -1)
        {
            printf("Error\n");
            exit(1);
        }
        else
        {
            if (strcasecmp(send_buff, "bye") == 0)
            {
                exit(1);
            }
        }
    }

    return 0;

}