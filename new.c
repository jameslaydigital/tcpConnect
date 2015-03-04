#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define BUF_SIZE 500

struct addrinfo * resolveHost(char*, char*);
int createTCPSocket();
void bindSocket(int, struct addrinfo*);
int tcpConnect(char*, char*);

/*  PROCESS:
 *
 *    1. Resolve dns of requested host.
 *    2. Create a tcp stream socket.
 *    3. Connect the socket to the resolved host.
 *
 * */

int main(int argc, char *argv[]) {

  // PREPARATION
  if (argc < 3) {
     fprintf(stderr, "Usage: %s host port\n", argv[0]);
     exit(EXIT_FAILURE);
  }
  char * host = argv[1];
  char * port = argv[2];


  //========== EXAMPLE USAGE ========
  int sockfd = tcpConnect(host, port);
  //=================================

  //TODO - do something with the connection.


  //close the connection.
  close(sockfd);
  return 0;
}

//  // 4. SEND AND RECEIVE MESSAGES.
//  char * response = (char*)malloc(sizeof(char)*BUF_SIZE);
//  char * msg = (char*)malloc(sizeof(char)*BUF_SIZE);
//  int connected = 1;
//  while ( connected == 1 ) {
//    memset(msg, 0, BUF_SIZE);
//    fgets(msg, BUF_SIZE, stdin); 
//    write(sockfd, msg, strlen(msg));
//    memset(response, 0, BUF_SIZE);
//    read(sockfd, response, BUF_SIZE);
//    printf("response: %s\n", response);
//    if ( strlen(response) < 2 ) {
//      printf("\nSession disconnected.\n");
//      connected = 0;
//    }
//  }
//  free(msg);
//  free(response);
//  close(sockfd);
//  return 0;
//}

int tcpConnect(char * host, char * port) {
  struct addrinfo *firstDNSRslt = resolveHost(host, port);
  int sockfd = createTCPSocket();
  bindSocket(sockfd, firstDNSRslt);
  return sockfd;
}

void bindSocket(int sockfd, struct addrinfo * firstDNSRslt) {
  // 3. TRY TO CONNECT YOUR SOCKET TO THE ADDRESSES RETURNED FROM DNS
  //      -> Loop through DNS results until you can connect a socket with one of them.
  if ( firstDNSRslt == NULL ) {
    fprintf(stderr, "Cannot connect to NULL DNS.\n");
    exit(EXIT_FAILURE);
  }
  struct addrinfo *currDNSRslt; //linked list
  struct sockaddr *addr;
  socklen_t addrlen;
  int connectSuccess;
  currDNSRslt = firstDNSRslt;
  while( currDNSRslt != NULL ) {
    addr = currDNSRslt->ai_addr;
    addrlen = currDNSRslt->ai_addrlen;
    connectSuccess = connect(sockfd, addr, addrlen);
    if ( connectSuccess == 0 )
      break; //success!

    currDNSRslt = currDNSRslt->ai_next;
  }
  if ( currDNSRslt == NULL ) {
    fprintf(stderr, "not resolve domain for specified host.\n");
    exit(EXIT_FAILURE);
  }
  freeaddrinfo(firstDNSRslt);
  return;
}



int createTCPSocket() {
  int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if ( sockfd == -1 ) {
    fprintf(stderr, "Socket failed.\n");
    exit(EXIT_FAILURE);
  }
  printf("Socket success!\n");
  return sockfd;
}



struct addrinfo * resolveHost(char * host, char * port) {
  struct addrinfo *firstDNSRslt;
  struct addrinfo hostParams;
  int dnsSuccess;

  //is it necessary to zero out this memblock?
  memset(&hostParams, 0, sizeof(struct addrinfo));
  hostParams.ai_family = AF_INET;       //Internet Protocol Version 4
  hostParams.ai_socktype = SOCK_STREAM; //Socket Stream
  hostParams.ai_protocol = IPPROTO_TCP; //Transmission Control Protocol
  hostParams.ai_flags = 0;              //No Flags
  // 1. TRY TO RESOLVE DNS
  dnsSuccess = getaddrinfo(host, port, &hostParams, &firstDNSRslt);
  if ( dnsSuccess != 0 ) {
    fprintf(stderr, "Could not resolve domain name for specified host.\n");
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(dnsSuccess));
    exit(EXIT_FAILURE);
  }
  return firstDNSRslt;
}
