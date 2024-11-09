#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>

#include <netinet/in.h>
#include <netinet/ip.h>

#include <string.h>
#include <arpa/inet.h>

#include <unistd.h>

 

int main() {

    // socket -----------------------------------------------------

    int ret = socket(AF_INET, SOCK_STREAM, 0);
    if (ret == -1) {
        printf("Socket not created\n");
        return 1;
    }
    printf("Socket created %d\nOK\n", ret);

    // ------------------------------------------------------------


    // connect to server -------------------------------------------------
    struct sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_port = htons(5000);
    server.sin_addr.s_addr = INADDR_ANY;

    
    int connection = connect(ret, (const struct sockaddr*)&server, sizeof(server));
    if (connection != 0) {
        printf("Connection unsuccessful\n");
        return -1;
    }

    printf("Connected to server\nOK\n");
    // ----------------------------------------------------------------------

    

    // receive the list of files from server ---------------------------------

    FILE *fp = fopen("list.txt", "w");
    if (!fp) {
        printf("Error opening list.txt for writing\n");
        close(ret);
        return -1;
    }

    char file_list[1000];
    int r = recv(ret, file_list, sizeof(file_list) - 1, 0);

    if (r > 0) {
        file_list[r] = '\0';
        printf("Files in server directory:\n=========\n%s\n===========\n", file_list);
        fwrite(file_list, sizeof(char), strlen(file_list), fp);
    } 
    else 
    {
        printf("Error receiving file list\n");
        close(ret);
        fclose(fp);
        return -1;

    }

    fclose(fp);
    // ------------------------------------------------------------------------

 


    char requested_file[100];
    printf("Enter the filename to request: ");
    scanf("%s", requested_file);

    send(ret, requested_file, strlen(requested_file), 0);


    FILE *fp2 = fopen("file1.txt", "w");
    if (!fp2) {
        printf("Error opening file.txt for writing\n");
        close(ret);
        return -1;
    }



    char file_content[1000];
    printf("\nContents of the file '%s':\n---------------------------------------------\n", requested_file);

    while ((r = recv(ret, file_content, sizeof(file_content) - 1, 0)) > 0) {
        file_content[r] = '\0';
        if (strstr(file_content, "EOF")) {
            break; 
        }
        printf("%s", file_content); 
        fwrite(file_content, sizeof(char), r, fp2);
    }

    fclose(fp2);
    printf("\n---------------------\n");
    printf("File transfer complete\n");


    close(ret);

    return 0;

}