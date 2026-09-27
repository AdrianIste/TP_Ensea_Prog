\# Linux Systems Programming in C



Two labs from a systems programming course at ENSEA, written in C for Linux.



\## TP1 – enseash, a mini shell



A simple command-line shell. It runs each command with its arguments in a

separate process, then shows in the prompt how the command ended and how long

it took. Type `exit` or press Ctrl+D to quit.



The folder contains one file per step of the lab. `Q6.c` is the final version.



```bash

gcc TP1/Q6.c -o enseash

./enseash

```



\## TP2 – TFTP client



A TFTP client (RFC 1350) that downloads and uploads files with a server over UDP.

Files are sent in blocks of up to 512 bytes, and each block is acknowledged.



\- `Q4.c` – download a file from the server (gettftp)

\- `Q5.c` – upload a file to the server (puttftp)



```bash

gcc TP2/Q4.c -o gettftp

gcc TP2/Q5.c -o puttftp

./gettftp <server> <file>

./puttftp <server> <file>

```



The client connects to the server on port 1069.

