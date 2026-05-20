#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
    int sock = 0;
    struct sockaddr_in serv_addr;

    char str[1024];

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    printf("Enter a string: ");
    scanf("%s", str);

    send(sock, str, strlen(str)+1, 0);

    read(sock, str, sizeof(str));

    printf("Reversed string: %s\n", str);

    close(sock);

    return 0;
}