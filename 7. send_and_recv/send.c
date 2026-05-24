/**
    THIS CHAPTER IS ALL ABOUT SEND AND RECV
    send() and recv() are for communicating over stream sockets or CONNECTED datagram sockets .
    For regular unconnected datagram sockets .. we need sendto() and recvfrom()

    * SYNTAX for send()
       int send(int socketfd, const void *msg, int len, int flags)

       socketfd - socket descriptor you want to send the data to ( does not matter socketfd is
       returned by what) msg - pointer to the data you want to send len - length of the data in
       bytes flags - set to 0 .. for more see the man page of send()

        *** - send() also returns number of bytes actually sent out -- this might be less than the
                    number you gave. it's upto you how you want to proceed with the rest of the data
                - if packet is arounf 1k it will probably manage to send the whole thing in one go.

        again it returns -1 in case of error and set errno



    * SYNTAX for recv()
       int recv(int socketfd, void *buf, int len, int flags)

       socketfd - socket descriptor to read from.
       buf - buffer to read the info into
       len - max length of the buffer
       flags - set to 0 again ( see man page for recv() )

       recv() returns the number of bytes read into the buffer or -1 on error ( with errno )
       == recv() can return 0 - means remote side closed the connection ***********


*/

#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

int main() {
    // follow through the chaptere 6 example and add the extra things
}

/**

   send() and recv() are BLOCKING CALLS
    - recv() will block until there is some data ready to receive
    - send() can also be blocking if the stuff that you are sending is all jammed up somehow .. very
   rare

*/

/**
    Unconnected Datagram Sockets

    ** SYNTAX for sendto()

    int sendto(int sockfd, const void *msg, int len, unsigned int flags, const struct sockaddr *to,
               socklen_t tolen)

    * to - pointer to struct sockaddr ( which will prolly be another sockaddr_in or sockaddr_storage
         that you can cast at the last minute) which contains destination ip+port .

    * tolen - an int .. can simply be set to sizeof *to or sizeof(struct sockaddr_storage)

    TO get destination address structure .. prolly get it from getaddrinfo() or from recvfrom()
    ..or fill it out by hand

    === sendto() returns the no of bytes actually sent ( might be less than number you specified)
        or -1 on error (errno)


    ** SYNTAX for recvfrom()

       int recvfrom(int socketfd, void *buf, int len, unsigned int flags, struct sockaddr *from
                    int *fromlen)

        * from - pointer to a local struct sockaddr_storage that will be filled with IP + PORT of
                 the originating machine **

        * fromlen is a pointer to a local int that should be initialized to sizeof *from or
          sizeof(struct sockaddr_storage) . When the function returns .. fromlen will contain
          the length of the address actually stored in "from"

        recvfrom() returns the number of bytes received, or -1 on error (with errno set
   accordingly).


*/

/**
    COPIED DIRECTLY FORM THE BOOK

    So, here’s a question: why do we use struct sockaddr_storage as the socket type? Why not
    struct sockaddr_in ?
    - Because, you see, we want to not tie ourselves down to IPv4 or IPv6. So we use
      the generic struct sockaddr_storage which we know will be big enough for either.

   (So… here’s another question: why isn’t struct sockaddr itself big enough for any address?
   We even cast the general-purpose struct sockaddr_storage to general-purpose struct sockaddr !
   Seems extraneous and redundant, huh?
   - The answer is, it just isn’t big enough, and I’d guess that changing it at this
      point would be Problematic. So they made a new one.)

   **************************
   Remember, if you connect() a datagram socket, you can then simply use send() and rec() for all
   your transactions. The socket itself is still a DATAGRAM SOCKET and the packets still use UDP,
   but the socket interface will automatically add the destination and source information for you.
   **************************



*/