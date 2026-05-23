/* IN THIS CHAPTER WE WILL CONNECT WITH SOME REMOTE IP + PORT
  USING SOME PROTOCOL LET'S SAY TELNET

    BASICALLY connect() LETS YOU CONNECT TO A REMOTE HOST
 -- SYNTAX
 int connect (int socketfd, struct sockaddr *serv_addr, int addrlen)

 1. sockaddr struct - contain destination port and IP address.
 ( we saw the same struct in bind )
  .. here it is for SERVER_ADDRESS (remote one)

 // This proves that structs are not entirely method dependent - my theory only
 .. may change later

 2. addrlen - length in bytes of the server address structure



 connect() returns -1 on error and set the variable errno
 */

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

int main() {

  struct addrinfo hints, *res;

  memset(&hints, 0, sizeof hints);

  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  int status;

  if ((status = getaddrinfo("www.example.com", "3490", &hints, &res)) != 0) {
    fprintf(stderr, "unable to process with getaddrinfo() : %s \n",
            gai_strerror(status));
    return 1;
  }

  // ofc again I am mentioning here that we should traverse the linked list
  // pointed by the res for the better results
  // here I am assuming that the first node has the correct data .. for more
  // info see the first folder in this repo

  //  now we need to get a socket fd
  int socketfd;

  if ((socketfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) ==
      -1) {
    // kuch to hil gya
    fprintf(stderr, "unable to get the socket fd using socket() : %s \n",
            strerror(errno));
    return 2;
  }

  // FINALLY the charm of the connect()

  int connect_status;
  if ((connect_status = connect(socketfd, res->ai_addr, res->ai_addrlen)) ==
      -1) {
    // kuch to fas gya
    fprintf(stderr, "unable to connnect(): %s\n", strerror(errno));
    return 3;
  }

  return 0;
}

/*
    Here we are not using bind .. because we do not care about the local port
   number.. we only care where we are going ( the remote port )

   The Chad , The man , the myth .. KERNEL will choose a local port for us and
   the site we connect to will automatically get this info from us ...
    craezy craezy
*/
