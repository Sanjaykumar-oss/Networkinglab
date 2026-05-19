#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

int isPrime(int n)
{
    int i;
    if(n <= 1)
        return 0;

    for(i = 2; i <= n/2; i++)
    {
        if(n % i == 0)
            return 0;
    }
    return 1;
}

int main()
{
    int sockfd, num;
    char buffer[1024];
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr*)&server, sizeof(server));

    printf("Server waiting for data...\n");

    recvfrom(sockfd, &num, sizeof(num), 0, (struct sockaddr*)&client, &len);

    if(isPrime(num))
        sprintf(buffer, "Prime number. Factors: 1 and %d", num);
    else
        sprintf(buffer, "Composite number");

    sendto(sockfd, buffer, strlen(buffer)+1, 0, (struct sockaddr*)&client, len);

    close(sockfd);
    return 0;
}