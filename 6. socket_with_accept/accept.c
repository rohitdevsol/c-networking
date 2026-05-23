// THIS CHAPTER IS ALL ABOUT accept() - Thankyou for calling this port
// returns -1 and sets errno if error occurs
/**
    Someone will try to connect() to our server on a port where we are listen() ing
    Their connection will be queued up waiting to be accept() ed.

    WHEN we call accept() .. we tell it to get a pending connection.
    -- IT WILL return a new SOCKET FD for this new connection

    // THE ORIGINAL socketfd is still listening for more new connections and the
    new SOCKET FD  is finally ready to send() and recv().

    // SYNTAX for accept

    int accept( int socketfd, struct sockaddr *addr, socklen_t *addrlen)

    1. socketfd - listen() ing socket descriptor.
    2. struct sockaddr *addr - pointer to a local struct SOCKADDR_STORAGE.

    SOCKADDR_STORAGE - this is where the info about the incoming connections will go ..
    ( with this we can determine which host is calling from which port )

    // ===== IMPORTANT ====
    3. addrlen is the local integer that should be set to size of (struct sockaddr_storage ) BEFORE
       ITS ADDRESS IS PASSED TO accept()

       accept() will not put more than that many bytes into addr (struct sockaddr_storage ) . If it
   pits fewer in, it will change the value of addrlen to reflect that

*/

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#define PORT "3000"
#define BACKLOG 10

// int accept( int socketfd, struct sockaddr *addr, socklen_t *addrlen)
int main() {
    struct sockaddr_storage their_addr;
    socklen_t addr_size;

    struct addrinfo hints, *res;
    int socketfd, newfd;

    memset(&hints, 0, sizeof hints);

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    // bind my own ip using AI PASSIVE
    hints.ai_flags = AI_PASSIVE;

    // now to use any port pass that to the getaddrinfo
    int status;

    if ((status = getaddrinfo(NULL, PORT, &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo failed: %s \n", gai_strerror(status));
        return 1;
    }

    if ((socketfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1) {
        // means error aagya
        fprintf(stderr, "socket() failed : %s\n", strerror(errno));
        return 2;
    }

    // int bind (int socketfd, struct sockaddr *my_addr, int addrlen)
    int bindstatus;
    if ((bindstatus = bind(socketfd, res->ai_addr, res->ai_addrlen)) == -1) {
        // bind nhi ho paya
        fprintf(stderr, "bind() failed: %s\n", strerror(errno));
        return 3;
    }

    // NOW FINALLY listen()

    listen(socketfd, BACKLOG);

    // NOW COMES THE accept()

    addr_size = sizeof their_addr;  // size of struct sockaddr_storage

    newfd = accept(socketfd, (struct sockaddr *)&their_addr, &addr_size);

    // ready to communicate on socket descriptor new_fd
    // we will use new-fd for all send() and recv() calls.
    return 0;
}

/***

NOTE - If you're only getting one single connection ever .. you can close() the listening socketfd
in order to prevent more incoming connections on the same port
( ONLY IF WE WANT )

*/