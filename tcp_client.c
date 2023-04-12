#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[] )
{
if (argc != 3){
    printf("Sai dinh dang so tham so \n");
    return 0;
}
int i;
int n=0;
char *temp = NULL;
temp = malloc(strlen(argv[1]) + 1); 
strcpy(temp, argv[1]);
char *p = strtok(temp,".");

if (p == NULL){
    return 0;
    } 
while (p!=NULL){
    i= atoi(p);
    if (isdigit(*p)==0) {
        printf("Sai dinh dang ip  \n");
        return 0;
    }
    if (i<0 || i>255){
        printf("Sai dinh dang ip \n");
        return 0;
    }
    p = strtok(NULL,".");
    n++;
}

if (n!=4) {
    printf("Sai dinh dang ip  \n");
    return 0;
}

if (!isdigit(*argv[2])){
    printf("Sai dinh dang port \n");
    return 0;
}
char *port = argv[2];
int client = socket(AF_INET, SOCK_STREAM,IPPROTO_TCP);

struct sockaddr_in addr;
addr.sin_family = AF_INET;
addr.sin_addr.s_addr = inet_addr(argv[1]);
addr.sin_port = htons(atoi(port));

int ret = connect(client, (struct sockaddr *)&addr, sizeof(addr));
if (ret == -1) {
    printf("connect failed \n");
    return 0;
}
printf("Connect success\n");

int rec;
char b[256];

    rec = recv(client, b, sizeof(b),0);
    printf("%d",rec);
    printf("%s\n",b);


char buf[256];

while (1)
{
    printf("Enter String: ");
    fgets(buf,sizeof(buf),stdin);
    send(client,buf,strlen(buf),0);
}
free(buf);
close(client);
}