#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char* argv[]){

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

int num=0,m=5;
struct sinhvien {
    char MSSV [10] ;
    char hoten[32] ;
    char ngaySinh[12];
    char diemTrungBinh[6];
};
struct sinhvien sv;
char* mssvLabel= "Ma So Sinh Vien:";
char* hoTenLabel= "Ho ten Sinh Vien:";
char* ngaySinhLabel="Ngay sinh:";
char* diemTbLabel = "Diem Tb:";
char * xuongDong = "";
// sv = malloc(sizeof(struct sinhvien)*m);
while (1)
{

   printf("Nhap vao MSSV: \n");
   fgets(sv.MSSV,sizeof(sv.MSSV),stdin);
   send(client,mssvLabel,strlen(mssvLabel),0);
   send(client,sv.MSSV,strlen(sv.MSSV),0);

   printf("Nhap vao hoten: \n");
   fgets(sv.hoten,sizeof(sv.hoten),stdin);
   send(client,hoTenLabel,strlen(hoTenLabel),0);
   send(client,sv.hoten,strlen(sv.hoten),0);

   printf("Nhap vao ngay sinh: \n");
   fgets(sv.ngaySinh,sizeof(sv.ngaySinh),stdin);
   send(client,ngaySinhLabel,strlen(ngaySinhLabel),0);
   send(client,sv.ngaySinh,strlen(sv.ngaySinh),0);

   printf("Nhap vao diem trung binh: \n");
   fgets(sv.diemTrungBinh,sizeof(sv.diemTrungBinh),stdin);
   send(client,diemTbLabel,strlen(diemTbLabel),0);
   send(client,sv.diemTrungBinh,strlen(sv.diemTrungBinh),0);
}


}