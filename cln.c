#include<arpa/inet.h>
#include<netdb.h>
#include<errno.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    int n = 0;
    struct sockaddr_in ipofserver;
    memset(&ipofserver, '0', sizeof(ipofserver));
    ipofserver.sin_family = AF_INET;
    ipofserver.sin_addr.s_addr = inet_addr("127.0.0.1");
    ipofserver.sin_port = htons(2016);

    if(connect(sock, (struct sockaddr *)&ipofserver, sizeof(ipofserver))<0)
    {
        printf("Connection failed due to port and ip problems\n");
        return 1;
    }
    char datarec [1024];
    memset(datarec, '0', sizeof(datarec));
    while((n = read(sock, datarec, sizeof(datarec)-1)) > 0)
    {
        datarec[n] = 0;
        if(fputs(datarec, stdout) == EOF)
            printf("Standard Output Error\n");
        printf("\n");
    }
    return 0;
}