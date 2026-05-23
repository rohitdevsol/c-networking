/****
    IN HERE I AM JUST GETTING THE SOCKET FD .. BIND PART WILL BE IN BIND FOLDER
    - SOCKET FUNCTION SIMPLY RETURNS A -- SOCKET_DESCRIPTOR --
    - SOCKETFD ALONE IS NO  GOOD -- NEED SOME MORE SYSTEM CALLS


*/

// SYNTAX FOR THE SOCKET
//.           IP_TYPE      STREAM TYPE    ai_protocol(TCP or UDP)
// int socket(int domain,  int type,      int protocol)

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
int main() {

  int status;
  struct addrinfo hint, *res;

  memset(&hint, 0, sizeof hint); // set to 0 initially

  hint.ai_family = AF_UNSPEC;
  hint.ai_socktype = SOCK_STREAM;

  // you can also pass port instead of the protocol
  if ((status = getaddrinfo("www.example.com", "http", &hint, &res)) != 0) {
    // now this status should be 0
    fprintf(stderr, "unable to process getaddrinfo: %s\n",
            gai_strerror(status));
    return 1;
  }

  // assuming that the first node the res points to has the data that we need

  // now hint has all the data filled .. and res has a pointer to the linked
  // list of type hint(each node)
  // Now it begs the question that what should we do

  int socketfd;

  // the protocol can be 0 too ( auto detect gets activated -  tcp or udp)
  if ((socketfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) ==
      -1) {
    fprintf(stderr, "unable to get socket fd: %s\n", strerror(errno));
    return 2;
  }

  printf("Socket fd value is : %d\n", socketfd);
  // this socket fd is with us right now

  return 0;
}