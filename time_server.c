#include "unp.h"
#include <time.h>

int main(int argc, char **argv)
{
    int sock_fd, client_fd;
    char buf[MAXLINE];
    time_t ticks;

    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(13);

    sock_fd = Socket(AF_INET, SOCK_STREAM, 0);
    Bind(sock_fd, (SA *) &address, sizeof(address));
    Listen(sock_fd, LISTENQ);

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    for (;;) {
        client_fd = Accept(sock_fd, (SA *) NULL, NULL);
        ticks = time(NULL);
        snprintf(buf, sizeof(buf), "%.24s\r\n", ctime(&ticks));
        Write(client_fd, buf, strlen(buf));
        Close(client_fd);
    }
#pragma clang diagnostic pop
}
