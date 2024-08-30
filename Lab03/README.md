# normal UDP communication




## receiver.c


First import the necessay header files:
```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
```



Then we have to create the socket. This can be acheived with the code snippet below.
The socket function can be found on Linux man pages by typing `man socket`.


```c
int main()
{


    int flag = 1;
    int ret = socket(AF_INET, SOCK_DGRAM, 0);
    if (ret == -1)
    {
        printf("Socket creation failed");
        exit(1);
    }
    else
    {
        printf("Socket creation successfully\n");
    }
}

```


After we create the socket, we have to do a "binding" step.
This step assigns a "name" to the socket if you will.

We have to populate the `struct sockaddr_in` structure / data-type.
Details about the `struct sockaddr_in` struct can be found in `man 7 ip`.


In the code below, `ret` is the socket file descriptor.

Apologies for the poor variable naming convention.

```c

int main() 
{
    struct sockaddr_in sent;
    sent.sin_family = AF_INET;
    sent.sin_port = 5500;
    sent.sin_addr.s_addr = INADDR_ANY;


    int ret1 = bind(ret, 
                    (const struct sockaddr *)&sent, 
                    sizeof(sent));

    if (ret1 == -1)
    {
        printf("Bind failed");
    }
    else
    {
        printf("Bind successfully\n");
    }
}

```

Now here begins our infinite while loop through which communication happens between the sender and the receiver.


As we are in `receiver.c` (this can also be thought of as the `server` so `server.c` woudl have been an appropiate name as well.)

We define another `struct sockaddr_in` instance as `recv`. Note that we do not need to manually fill the members of this instance as this is done automatically by the OS.

The `recvfrom` API does the heavylifting of actually receiving the message.




Then the `send_message` part of the loop begins. Here, the `server` is sending a message back to the `client` to enable two way communication.


We have to define "where" the message has to go, which is why we populate another instance of the `sockaddr_in` structure.


And then, we use the `sendto` API to do the actual sending of the message.




```c
int main()
{
    
    while (flag)
    {


        // recieve message
        char recv_buff[100];
        struct sockaddr_in recv;
        int size = sizeof(recv);

        int res = recvfrom(ret, 
                            recv_buff, 
                            sizeof(recv_buff), 
                            0, 
                            (struct sockaddr *)(&recv),
                            (socklen_t *)(&size));

                            
        if (res == -1)
        {
            printf("Recieved failed");
        }
        else
        {
            if (recv_buff[0] == 'e' && recv_buff[1] == 'x' && recv_buff[2] == 'i' && recv_buff[3] == 't')
            {
                exit(0);
            }
            printf("%s\n", recv_buff);
        }


        // ---------------------------------------



        // send message
        char send_buff[100];
        printf("Please enter the message to send:");
        scanf("%[^\n]%*c", send_buff);
        
        struct sockaddr_in send;
        send.sin_family = AF_INET;
        send.sin_port = recv.sin_port;
        send.sin_addr.s_addr = INADDR_ANY;
        int size2 = sizeof(send);

        int res2 = sendto(ret, 
                        send_buff, 
                        strlen(send_buff), 
                        0, 
                        (const struct sockaddr *)(&send), 
                        size);

        if (res2 == -1)
        {
            printf("Send failed");
        }
        else
        {
            printf("Successful\n");
            if (send_buff[0] == 'e' && send_buff[1] == 'x' && send_buff[2] == 'i' && send_buff[3] == 't')
            {
                exit(0);
            }
        }
        
    }
}
```





> And that's a wrap. That's more or less how the above programme works. Will update this README with an explanation of the `sender.c` code as well as and when I get time!

Thank you.

