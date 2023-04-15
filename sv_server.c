#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("Sai tham so \n");
    }
    if (!isdigit(*argv[1])){
    printf("Sai dinh dang port \n");
    return 0;
}

int listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
if (listener == -1) {
    perror("socket failed");
    return 1;
}
char *port = argv[1];

struct sockaddr_in addr;
addr.sin_family = AF_INET;
addr.sin_addr.s_addr = htonl(INADDR_ANY);
addr.sin_port = htons(atoi(port));

if (bind(listener,(struct sockaddr *)&addr,sizeof(addr))){
    perror("bind failed");
    return 1;
}

if (listen(listener,5)){
    perror("listen failed");
    return 1;
}
struct sockaddr_in client_addr;
int client_addr_len = sizeof(client_addr);

int client = accept(listener,(struct sockaddr *)&client_addr,&client_addr_len);

if (client == -1) {
    perror("accept failed");
    return 1;
}
printf("Accepted socket %d from IP: %s:%d \n ",client,inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
int ret;
char buf[50];
FILE* file = fopen(argv[2], "wb");
while (1)
{
    ret = recv(client, buf, sizeof(buf),0);
    if (ret <= 0) break;
    if (ret <sizeof(buf)) buf[ret] = '\0';
    printf("%d byte received %s\n",ret,buf);
    fwrite(buf,1,ret,file);
}

}