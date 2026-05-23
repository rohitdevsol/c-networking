// THIS FILE WILL CONTAIN (SOME) CODE FROM THE SOCKET_CONNECT FOLDER
// -- WRITTEN BY HAND AGAIN FOR THE PRACTICE

/*
 * WHAT IS BIND() - WHAT PORT I AM ON ??
 * ONCE YOU HAVE A SOCKET .. you might need to associate that socket with some
   port on your LOCAL MACHINE (commonly done if we are going to listen on some
 port for incoming connections)
 *  And when someone needs to connect with us they would do a connect() syscall
 */

// Syntax for the bind()
// int bind (int socketfd, struct sockaddr *my_addr, int addrlen)

// sockaddr has info about your port and ip address
// addrlen is the length in bytes of that address

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

  // prefill some data into the hints
  hints.ai_family = AF_UNSPEC;
  hints.ai_flags = AI_PASSIVE; // means - bind my own ip address .. you can ofc
                               // bind another local ip address(but then pass it
                               // to getaddrinfo after dropping this line)
  hints.ai_socktype = SOCK_STREAM;

  int status;

  if ((status = getaddrinfo(NULL, "3490", &hints, &res)) != 0) {
    fprintf(stderr, "failed to process getaddrinfo: %s\n",
            gai_strerror(status));
    return 1;
  }

  int socketfd;

  if ((socketfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) ==
      -1) {
    fprintf(stderr, "failed to process socket() method: %s\n", strerror(errno));
    return 2;
  }

  // bind it to the port we passed in to the getaddrinfo
  int bindstatus;

  if ((bindstatus = bind(socketfd, res->ai_addr, res->ai_addrlen)) == -1) {
    fprintf(stderr, "failed to process bind() method: %s\n", strerror(errno));
    return 3;
  }

  return 0;
}

// OLD Codes generally have hardcoded sockaddr_in structs
// the below code is directly taken from the book
/* !!! THIS IS THE OLD WAY !!!

 int sockfd;
 struct sockaddr_in my_addr;

 sockfd = socket(PF_INET, SOCK_STREAM, 0);

 my_addr.sin_family= AF_INET;
 my_addr.sin_port= htons(MYPORT); // short, network byte order
 my_addr.sin_addr.s_addr= inet_addr("10.12.110.57");
 memset(my_addr.sin_zero,'\0', sizeof my_addr.sin_zero);

 bind(sockfd, (struct sockaddr *)&my_addr, sizeof my_addr);

 */

// ==========================================================================

// AGAIN this part if from the book
/***

One small extra final note about bind(): there are times when you won’t
absolutely have to call it. If you are connect() ing to a remote machine
and you don’t care what your local port is (as is the case with telnet where you
only care about the remote port), you can simply connect() , it’ll check to see
if the socket is unbound and will bind() to an unused local port if necessary

*/