#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
    int sockfd;
    char buffer[1024];

    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    bind(sockfd, (struct sockaddr *)&server, sizeof(server));

    printf("Server waiting for data...\n");

    recvfrom(sockfd, buffer, sizeof(buffer), 0,
             (struct sockaddr *)&client, &len);

    int n = strlen(buffer);

    for(int i = 0; i < n/2; i++)
    {
        char temp = buffer[i];
        buffer[i] = buffer[n-i-1];
        buffer[n-i-1] = temp;
    }

    sendto(sockfd, buffer, strlen(buffer)+1, 0,
           (struct sockaddr *)&client, len);

    close(sockfd);

    return 0;
}