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

    
    // --------------  create socket for client  ----------------------------
	int sock_fd = socket(AF_INET, 
								SOCK_STREAM, 
								0);
								
	if (sock_fd == -1)
	{
		printf("Socket creation failed\n");
		exit(1);
	}
	else
		printf("Socket created successfully\n");

    
    struct sockaddr_in client_details_struct;
	client_details_struct.sin_family = AF_INET;
	client_details_struct.sin_port = htons(5000);
	
	inet_aton("127.0.0.1", &client_details_struct.sin_addr);

	// ---------------------------------------------------------

	int connect_fd = connect(sock_fd, 
							(const struct sockaddr *)&client_details_struct,
                   			sizeof(client_details_struct));

    




    while(flag)
    {
        // sending

		char send_buff[100];
        printf("\nEnter the msg to send : \n");
		fgets(send_buff, sizeof(send_buff), stdin);
		printf("\n");

        int send_fd = send(sock_fd, send_buff, strlen(send_buff), 0);

        if (send_fd == -1)
        {
            printf("Error\n");
			exit(1);
        }
        else
        {
            if (strcasecmp(send_buff, "bye") == 0)
				exit(1);

        }



        // receiving

        char recv_buff[100];

        int receive_fd = recv(sock_fd, 
											recv_buff, 
											sizeof(recv_buff), 
											0);
        
        if (receive_fd == -1)
		{
			printf("recv failed\n");
			exit(1);
		}
		else if (receive_fd > 0)
		{

			printf("Received msg: %s\n", recv_buff);
			

			if (strcasecmp(recv_buff, "bye") == 0)
				exit(1);
		}


    }

    return 0;

}