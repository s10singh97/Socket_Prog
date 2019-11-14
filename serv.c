#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
#include<errno.h>
#include<stdio.h>
#include<netdb.h>
#include<sys/types.h>
#include <time.h>
#include <unistd.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    time_t clock;
    pid_t pid;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in ipofserver;
    memset(&ipofserver, '0', sizeof(ipofserver));
    ipofserver.sin_family = AF_INET;
    ipofserver.sin_addr.s_addr = htonl(INADDR_ANY);
    ipofserver.sin_port = htons(2016);
    bind(sock, (struct sockaddr*) (&ipofserver), sizeof(ipofserver));
    listen(sock, 20);
    char datasend[1025];
    memset(datasend, '0', sizeof(datasend));
    while(1)
    {
        printf("Running..\n");
        int conn = accept(sock, (struct sockaddr*)NULL, NULL);
        if((pid = fork()) == 0)
        {
            close(sock);
            clock = time(NULL);
            snprintf(datasend, sizeof(datasend), "%.24s\r\n", ctime(&clock));
            write(conn, datasend, strlen(datasend));
        }
        close(conn);
        sleep(1);
    }
    return 0;
}