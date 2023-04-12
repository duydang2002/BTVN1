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
    if (argc != 4) {
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
printf("Accepted socket %d from IP: %s:%d ",client,inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));


FILE *file = fopen(argv[2],"rb");

if (file == NULL) {
    perror("fopen failed 1");
    return 1;
}

char buf[256];
int rec;
while (!feof(file))
    {
        rec = fread(buf, 1, sizeof(buf), file);
        if (rec <= 0)
            break;
        printf("%s",buf);
        send(client, buf, rec, 0);
    }

// fclose(file);
char buf2[256];
int ret;

FILE *file2 = fopen(argv[3],"wb");
if (file2 == NULL) {
    perror("fopen failed 2");
    return 1;
}
while (1){
    ret = recv(client,buf2,sizeof(buf2),0);
    if (ret<=0){
        break;
    }
    printf("%s\n",buf2);
    fwrite(buf2,1,ret,file2);
}
fclose(file2);
// close(client);
close(listener);
}
