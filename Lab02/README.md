## Socket proramming

This is the code that does socket programming in C.

Important commands 

`man 7 ip`  --> defines `struct sockaddr_in` and `struct in_addr`. `struct in_addr` is a part of `struct sockaddr_in`

`man socket` --> creates  an endpoint for communication

`man bind` --> When a socket is created with socket(2), it exists in a name space (address family) but has no address assigned to it. `bind()`  assigns  the address  specified  by  addr  to the socket referred to by the file descriptor sockfd.