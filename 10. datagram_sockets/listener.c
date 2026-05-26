/**
Listener just sits on a machine waiting for an incoming packet on some port
talker sends a packet to that port, on the specified machine, that contains
whatever the user enters on the command line

Let's use the IPv6 specifically

    getaddrinfo
    loop - socket and bind
    recvfrom.          theiraddr comes with this
    close(socketfd)
*/

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MYPORT "4950"
#define MAX_BUF_LEN 100

void *get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        // sinaddr from sockaddr_in
        return &((struct sockaddr_in *)sa)->sin_addr;
    }

    return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

int main() {
    int socketfd;

    struct addrinfo hints, *servinfo, *p;
    int rv;
    int numbytes;

    struct sockaddr_storage their_addr;
    char buf[MAX_BUF_LEN];

    socklen_t addr_len;
    char s[INET6_ADDRSTRLEN];

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET6;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;  // use my IP

    if ((rv = getaddrinfo(NULL, MYPORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo error %s:\n", gai_strerror(rv));
        return 1;
    }

    for (p = servinfo; p != NULL; p = p->ai_next) {
        // try to get the socketfd
        if ((socketfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            perror("listener: socket");
            continue;  // check for the next node
        }

        if (bind(socketfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(socketfd);
            perror("listener:bind");
            continue;
        }
        break;
    }

    if (p == NULL) {
        fprintf(stderr, "listener: failed to connect \n");
        return 2;
    }

    freeaddrinfo(servinfo);
    printf("listener: waiting to recvfrom...\n");
    addr_len = sizeof their_addr;
    if ((numbytes = recvfrom(socketfd, buf, MAX_BUF_LEN - 1, 0, (struct sockaddr *)&their_addr,
                             &addr_len)) == -1) {
        perror("recvfrom");
        exit(1);
    }

    printf(
        "listener: got packet from %s\n",
        inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof s));
    printf("listener: packet is %d bytes long\n", numbytes);
    buf[numbytes] = '\0';
    printf("listener: packet contains \"%s\"\n", buf);

    close(socketfd);

    return 0;
}