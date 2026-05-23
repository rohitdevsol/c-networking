// JUST A REWRITE OF THE showip.c
// JUST FOR PRACTICE ..
// NOT SURE WHY FIRST IF CONIDTION THROWS ERROR
// of variable being undeclared

#include "arpa/inet.h"
#include "netdb.h"
#include "stdio.h"
#include "string.h"
#include <stdio.h>
#include <string.h>

int main(int agrc, char *argv[]) {

  // get the args from the command line
  //   if (argc != 2) {
  //     fprintf(stderr, "usage: showip hostname\n");
  //     return 1;
  //   }

  int status;
  char ipaddr[INET6_ADDRSTRLEN];
  // declare addrinfo
  struct addrinfo hints, *res, *p;
  // has all the field

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  if ((status = getaddrinfo(argv[1], NULL, &hints, &res)) != 0) {
    fprintf(stderr, "error getaddrinfo %s \n", gai_strerror(status));
  }

  printf("IP address for %s: \n", argv[1]);

  for (p = res; p != NULL; p = p->ai_next) {
    void *addr;
    char *ipver;
    struct sockaddr_in *ipv4;
    struct sockaddr_in6 *ipv6;

    if (p->ai_family == AF_INET) {
      // this is ipv4
      ipver = "IPv4";
      ipv4 = (struct sockaddr_in *)p->ai_addr;
      addr = &(ipv4->sin_addr);
    }

    else {
      // this is ipv6
      ipver = "IPv6";
      ipv6 = (struct sockaddr_in6 *)p->ai_addr;
      addr = &(ipv6->sin6_addr);
    }

    // print this
    inet_ntop(p->ai_family, addr, ipaddr, sizeof(ipaddr));
    printf(" %s: %s\n", ipver, ipaddr);
  }

  freeaddrinfo(res);

  return 0;
}