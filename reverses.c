#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    char buffer[1024];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    listen(server_fd, 3);

    printf("Server waiting for connection...\n");

    new_socket = accept(server_fd,
                        (struct sockaddr *)&address,
                        (socklen_t*)&addrlen);

    read(new_socket, buffer, sizeof(buffer));

    int len = strlen(buffer);

    for(int i = 0; i < len/2; i++)
    {
        char temp = buffer[i];
        buffer[i] = buffer[len-i-1];
        buffer[len-i-1] = temp;
    }

    send(new_socket, buffer, strlen(buffer)+1, 0);

    close(new_socket);
    close(server_fd);

    return 0;
}