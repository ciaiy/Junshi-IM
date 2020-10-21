#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>

#define portnum 2333

int main()
{
    struct sockaddr_in server_addr;
    char buffer[128];

    //1.创建套接字
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        printf("create socket error!\n");
        exit(1);
    }

    //2.1设置要连接的服务器的地址
    bzero(&server_addr, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portnum);
    server_addr.sin_addr.s_addr = inet_addr("47.94.149.37");

    //2.连接服务器
    if (connect(sockfd, (struct sockaddr *)(&server_addr), sizeof(struct sockaddr)) == -1)
    {
        printf("connect error\n");
        exit(1);
    }
    while (1)
    {
        //3.发送数据到服务器
        printf("please input char:\n");
        fgets(buffer + 4, 124, stdin);
        *(int *)buffer = strlen(buffer + 4);
        printf("data : %s, len : %d\n", buffer + 4, *(int *)buffer);
        send(sockfd, buffer, 4 + strlen(buffer + 4), 0);
        char recvBuf[256];
        read(sockfd, recvBuf, 256);
        printf("recv : %d\n", *(int *)recvBuf);
    }
    //4.关闭连接
    close(sockfd);

    return 0;
}
