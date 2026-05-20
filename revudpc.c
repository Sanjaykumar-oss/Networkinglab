#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
    int sockfd;
    char str[1024];

    struct sockaddr_in server;
    socklen_t len = sizeof(server);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Enter a string: ");
    scanf("%s", str);

    sendto(sockfd, str, strlen(str)+1, 0,
           (struct sockaddr *)&server, len);

    recvfrom(sockfd, str, sizeof(str), 0, NULL, NULL);

    printf("Reversed string: %s\n", str);

    close(sockfd);

    return 0;
}