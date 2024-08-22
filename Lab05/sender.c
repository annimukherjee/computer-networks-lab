#include<stdio.h>
#include<stdlib.h>


#include<netinet/in.h>
#include<netinet/ip.h> 


#include<string.h>
#include<strings.h>

#include<arpa/inet.h>

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>


int main() {

	// --------------  create socket for client  ----------------------------
	int client_sock_fd = socket(AF_INET, 
								SOCK_STREAM, 
								0);
	if(client_sock_fd == -1) {
		printf("Socket creation failed\n");
		exit(1);
	} else {
		printf("Socket created successfully\n");
	}

	// ---------------------------------------------------------
	

	// --------------  LET OS DO THE BIND AUTOMATICALLY  ----------------------------

	// struct sockaddr_in send_struc;
	// send_struc.sin_family = AF_INET;
	// send_struc.sin_port = htons(5100);
	// //send.sin_addr.s_addr = inet_addr("10.2.248.220");
	// inet_aton("127.0.0.1", &send_struc.sin_addr);
	// int ret2 = bind(client_sock_fd, (const struct sockaddr *)&send_struc, sizeof(send_struc));
	// if(ret2 == -1) {
	// 	printf("Bind creation failed\n");
	// 	exit(1);
	// } else {
	// 	printf("Bind created successfully\n");

	// }

	struct sockaddr_in send_struct;
	send_struct.sin_family = AF_INET;
	send_struct.sin_port = htons(7000);
	
	inet_aton("127.0.0.1", &send_struct.sin_addr);

	// ---------------------------------------------------------

	int connect_fd = connect(client_sock_fd, 
							(const struct sockaddr *)&send_struct,
                   			sizeof(send_struct));



	// while(1) {
		
	//sending
	char send_buff[100];

	printf("\nEnter the msg to send : \n");
	fgets(send_buff, sizeof(send_buff), stdin);
	printf("\n");
	size_t len = strlen(send_buff);
	send_buff[len-1] = '\0';
	
	
	// struct sockaddr_in se;
	// se.sin_family = AF_INET;
	// se.sin_port = htons(5000);
	// inet_aton("127.0.0.1", &se.sin_addr);

	ssize_t NumberOfBytesSend = send(client_sock_fd, 
									send_buff, 
									strlen(send_buff), 
									0);

								//  (const struct sockaddr *)&se, 
								// sizeof(se)


	if(NumberOfBytesSend == -1) {
		printf("Error\n");
		exit(1);
	} else {
		if(strcasecmp(send_buff, "bye") == 0) {
			exit(1);
		}
	}
		// //receiving
		// char recv_buff[100];
		// struct sockaddr_in recv;
		// socklen_t size = sizeof(recv);
		// int NumberOfBytesReceived = recvfrom(ret1, recv_buff, sizeof(recv_buff), 0, (struct sockaddr *)(&recv), (&size));
		// if(NumberOfBytesReceived == -1) {
		// 	printf("API recvfrom failed\n");
		// 	exit(1);
		// } else if(NumberOfBytesReceived > 0){
		// 	recv_buff[NumberOfBytesReceived] = '\0';
		// 	printf("Received msg : %s\n", recv_buff);
		// 	printf("Port number of sender = %d\n", ntohs(recv.sin_port));
		// 	printf("IP Address of sender = %s\n", inet_ntoa(recv.sin_addr));
		// 	if(strcasecmp(recv_buff, "bye") == 0) {
		// 		exit(1);
		// 	}
		// }
	// }
}
