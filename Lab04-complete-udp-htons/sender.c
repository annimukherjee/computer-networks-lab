#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h> 
#include<string.h>
#include<strings.h>
#include<arpa/inet.h>

int main() {

	int ret1 = socket(AF_INET, SOCK_DGRAM, 0);
	if(ret1 == -1) {
		printf("Socket creation failed\n");
		exit(1);
	} else {
		printf("Socket created successfully\n");
	}
	


	struct sockaddr_in send;
	send.sin_family = AF_INET;
	send.sin_port = htons(5100);
	//send.sin_addr.s_addr = inet_addr("10.2.248.220");
	inet_aton("127.0.0.1", &send.sin_addr);
	int ret2 = bind(ret1, (const struct sockaddr *)&send, sizeof(send));
	if(ret2 == -1) {
		printf("Bind creation failed\n");
		exit(1);
	} else {
		printf("Bind created successfully\n");

	}
	
	while(1) {
		//sending
		char send_buff[100];
		printf("\nEnter the msg to send : \n");
		fgets(send_buff, sizeof(send_buff), stdin);
		printf("\n");
		size_t len = strlen(send_buff);
        send_buff[len-1] = '\0';


		struct sockaddr_in se;
		se.sin_family = AF_INET;
		se.sin_port = htons(5000);
		inet_aton("127.0.0.1", &se.sin_addr);

		int NumberOfBytesSend = sendto(ret1, send_buff, strlen(send_buff), 0, (const struct sockaddr *)&se, sizeof(se));
		
		if(NumberOfBytesSend == -1) {
			printf("Error\n");
			exit(1);
		} else {
			if(strcasecmp(send_buff, "bye") == 0) {
				exit(1);
			}
		}




		//receiving
		char recv_buff[100];
		struct sockaddr_in recv;
		socklen_t size = sizeof(recv);

		int NumberOfBytesReceived = recvfrom(ret1, recv_buff, sizeof(recv_buff), 0, (struct sockaddr *)(&recv), (&size));
		
		if(NumberOfBytesReceived == -1) {
			printf("API recvfrom failed\n");
			exit(1);
		} 
		else if(NumberOfBytesReceived > 0){
			recv_buff[NumberOfBytesReceived] = '\0';
			printf("Received msg : %s\n", recv_buff);
			printf("Port number of sender = %d\n", ntohs(recv.sin_port));
			printf("IP Address of sender = %s\n", inet_ntoa(recv.sin_addr));
			if(strcasecmp(recv_buff, "bye") == 0) {
				exit(1);
			}
		}
	}
}
