#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>

using namespace std;

int main(void) {
    int sockfd, n, temp, remaining_length, port = 8080;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char write_buffer[256];
    char* temp_buffer;
    char read_buffer[256];

    // Create a TCP socket for the client
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // The commented code below would create a UDP socket
    // sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)
    if (sockfd < 0) {
        cout << "Error: could not create socket for connecting to server" << endl;
	exit(-1);
    }

    server = gethostbyname("127.0.0.1");
    if (server == NULL) {
        cout << "Error: error getting hostname of server" << endl;
        exit(-1);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(port);

    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        cout << "Error: could not connect to server's socket" << endl;
        exit(-1);
    }

    strncpy(write_buffer, "Hello, I am the client!\n", 26);
    remaining_length = strlen(write_buffer);
    temp_buffer = write_buffer;
    do {
      n = send(sockfd, temp_buffer, remaining_length, 0);
      if (n < 0) {
        cout << "Error: error writing to socket; socket may be broken" << endl;
        exit(-1);
      }
      temp_buffer = temp_buffer + n;
      remaining_length -= n;
    } while (remaining_length != 0);

    bzero(read_buffer,256);
    n = recv(sockfd, read_buffer, 255, 0);
    if (n < 0) {
      cout << "Error: error reading from socket; socket may be broken" << endl;
      exit(-1);
    }

    cout << "Client received the following message: " << read_buffer << endl;
    close(sockfd);
    return 0;
}
