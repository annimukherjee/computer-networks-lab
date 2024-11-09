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

    printf("Socket created %d\n", ret);
    // ------------------------------------------------------------




    // server BIND -----------------------------------------------------------------------------

    struct sockaddr_in server_info;
    server_info.sin_family = AF_INET;
    server_info.sin_port = htons(5000);
    server_info.sin_addr.s_addr = INADDR_ANY;
    int ret1 = bind(ret, (const struct sockaddr*)&server_info, sizeof(server_info));
    


    if (ret1 == -1) {
        printf("Bind not successful\n");
        return 1;
    }
    printf("Bind successful %d\n", ret1);

    // -----------------------------------------------------------------------------------------


    // server LISTEN -----------------------------------------------------------------------------

    int lis = listen(ret, 5);
    if (lis == -1) {
        printf("Listen not successful\n");
        return 1;
    }
    printf("Listening...\n");
    // -----------------------------------------------------------------------------------------


    while (1) {

        // accept tcp ---------------------------------------------------------------------
        struct sockaddr_in client;
        socklen_t client_len = sizeof(client);
        int csock = accept(ret, (struct sockaddr*)&client, &client_len);
        if (csock == -1) {
            printf("Connection accept failed\n");
            continue;
        }

        printf("Client connected\n");
        // ---------------------------------------------------------------------------------


        // 
        system("ls > res.txt");


        // send file list to client begins ---------------------------------------
        FILE *fp = fopen("res.txt", "r");

        if (fp == NULL) {
            char error_msg[] = "Could not open files_in_dir.txt\n";
            send(csock, error_msg, sizeof(error_msg), 0);
            close(csock);
            continue;
        }


        char buffer[1000];
        int byter;
        while ((byter = fread(buffer, sizeof(char), sizeof(buffer), fp)) > 0) {
            send(csock, buffer, byter, 0);
        }
        fclose(fp);
        printf("File list sent to client\n");

        // ----- send file list to client ends --------------------------------
        

        // get the name of the the client wants to download -------------------------
        char reqfile[100];
        int r = recv(csock, reqfile, sizeof(reqfile), 0);

        if (r <= 0) {
            printf("Error receiving file request\n");
            close(csock);
            continue;
        }

        reqfile[r] = '\0';

        printf("Client requested file: %s\n", reqfile);

        // ------------- end --------------------------- -------------------------


        // open said file and send it ------------------------------------------------

        fp = fopen(reqfile, "r");

        if (fp == NULL) {
            char error_msg[] = "File not found\n";
            send(csock, error_msg, sizeof(error_msg), 0);
        } 
        else 
        {
            while ((byter = fread(buffer, sizeof(char), sizeof(buffer), fp)) > 0) {
                send(csock, buffer, byter, 0);
            }

            send(csock, "EOF", 3, 0); // Send EOF after the file content
            fclose(fp);

            printf("File sent successfully\n");
        }
        // -------- end -------------------------------------------------------------

    

        close(csock);

    }

    close(ret);

    return 0;

}