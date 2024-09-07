## File Transfer Using TCP

```
Basically, the server will do ls -a.

The output will be stored in a file. This file will be read using `fread` one chunk at a time and sent to the client.

The client will read this file sent and chooose which one they want the server to upload 

The server will read the response from the client and upload that particular file to the socket connection.

The client will then download that file.
```


This is the task we have to do.

APIs to Use

1. `connect`
2. `accept`
3. `recv`
4. `fread`
5. `fwrite`
6. `socket`
7. `system` for `ls -a`
8. `bind`
9. `listen`
10. `send`


