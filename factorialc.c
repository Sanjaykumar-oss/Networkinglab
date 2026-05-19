#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main()
{
    int sock = 0, num;
    long result;
    struct sockaddr_in serv_addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    printf("Enter a number: ");
    scanf("%d", &num);

    send(sock, &num, sizeof(num), 0);

    read(sock, &result, sizeof(result));

    printf("Factorial received from server: %ld\n", result);

    close(sock);

    return 0;
}