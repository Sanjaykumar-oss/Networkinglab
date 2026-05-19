#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

long factorial(int n)
{
    long fact = 1;
    int i;
    for(i = 1; i <= n; i++)
        fact = fact * i;
    return fact;
}

int main()
{
    int server_fd, new_socket, num;
    long result;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    listen(server_fd, 3);
    printf("Server waiting for connection...\n");

    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

    read(new_socket, &num, sizeof(num));

    result = factorial(num);

    send(new_socket, &result, sizeof(result), 0);

    printf("Factorial sent to client\n");

    close(new_socket);
    close(server_fd);

    return 0;
}