#include "unp.h"

int main(int argc, char *argv[])
{
    int sockfd, n;
    char buf[MAXLINE + 1];
    struct sockaddr_in servaddr;

    if (argc != 2) {
        err_quit("usage: gettimeclient <IPAddress>");
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        err_sys("socket error");

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(13);

    printf("%s\n", argv[1]);
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
        err_quit("inet_pton error for %s", argv[1]);

    if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
        err_sys("connect error");

    while ((n = (int) read(sockfd, buf, MAXLINE)) > 0) {
        buf[n] = '\0';
        if (fputs(buf, stdout) == EOF)
            err_sys("fputs error");
    }

    if (n < 0)
        err_sys("read error");

    return 0;
}
