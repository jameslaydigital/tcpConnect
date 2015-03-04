#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>

void error(const char * msg) {
  perror(msg);
  exit(0);
}

int main(int argc, char *argv[]) {
    // if not enough args were supplied, give help msg
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }

    //int sockfd, portno, n;                                  //initialize...

    //struct sockaddr_in serv_addr;                           //netinet/in :: sockaddr_in -> struct with information about a net address.

    //char buffer[256];                                       //256 characters of buffer to send to host.

    //portno = atoi(argv[2]);                                 //convert input to port number.

    //sockfd = socket(AF_INET, SOCK_STREAM, 0);               //sys/socket :: socket(...) -> create new socket,
                                                            //then assign file descriptor (int) to sockfd.

    //if (sockfd < 0)                                         //socket() returns negative upon failure.
        //error("ERROR opening socket");

    //struct hostent *server;                                 //netdb.h :: hostent -> struct with information about a server.
                                                            //netdb.h :: gethostbyname(...) -> returns a (hostent) from the hostname.
    //server = gethostbyname(argv[1]);                        //DNS resolution. deprecated - Use getaddrinfo instead.
    //if (server == NULL) {
        //fprintf(stderr,"ERROR, no such host\n");
        //exit(1);
    //}

    struct addrinfo *server;
    getaddrinfo(node, service, NULL, &addrinfo_array ); 

    //bzero((char*)&serv_addr, sizeof(serv_addr));            //note : replace this with memset. 'bzero' is deprecated.
    //serv_addr.sin_family = AF_INET;
    //bcopy(                                                  //use memcpy. bcopy is deprecated.
            //(char*)server->h_addr,
            //(char*)&serv_addr.sin_addr.s_addr,
            //server->h_length
    //);
//
    //serv_addr.sin_port = htons(portno);                     //htons = convert byte-order from host order to network order.

                                                            //connect : initiate a connection on a socket. Returns negative integer
                                                            //upon failure.
    //if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        //error("ERROR connecting");

    //printf("Please enter the message: ");

    //bzero(buffer,256);                                      //bzero -> again, deprecated.  Use memset instead.

    //fgets(buffer,255,stdin);                                //get user input into buffer.

    //n = write(sockfd,buffer,strlen(buffer));                //write the buffer.
    //if (n < 0) 
         //error("ERROR writing to socket");

    //bzero(buffer,256);                                      //yet again, memset here...

    //n = read(sockfd,buffer,255);                            //read response from host.
    //if (n < 0) 
         //error("ERROR reading from socket");

    //printf("%s\n",buffer);                                  //print out response

    //close(sockfd);                                          //close connection

    return 0;
}
