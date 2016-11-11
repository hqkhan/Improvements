#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <pthread.h>

using namespace std;

int main(void) {
     int sockfd, newsockfd, n, temp, remaining_length, portno = 8080;
     socklen_t clilen;
     char read_buffer[512];
     char write_buffer[512];
     char* temp_buffer;
     struct sockaddr_in serv_addr, cli_addr;
    
     // Create your TCP socket
     sockfd =  socket(AF_INET, SOCK_STREAM, 0);
     // The commented code below would create a UDP socket
     // sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)
     if (sockfd < 0) {
        cout << "Error: error creating socket for listening" << endl;
	exit(-1);
     }

     // Setup your server's socket address structure
     // Clear it out, and set its parameters
     bzero((char *) &serv_addr, sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;  // use IPv4
     serv_addr.sin_addr.s_addr = INADDR_ANY; // fill in server IP address
     serv_addr.sin_port = htons(portno); // convert port number to network byte order and set port

     // Bind socket to IP address and port on server
     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
       cout << "Error: error binding an IP address and port on the server to our socket" << endl;
       exit(-1);
     }

     // Listen on the socket for new connections to be made
     // 20 references the size of the queue of outstanding (non-accepted) requests we will store
     listen(sockfd,20);

     // The accept() call actually accepts an incoming connection
     clilen = sizeof(cli_addr);

     // accept a connection from a client, returns a new client socket for communication with client
     while (1) {
      newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
      if (newsockfd < 0) {
        cout << "Error: error creating new socket for communication with client" << endl;
        exit(-1);          
      }

      cout << "Server accepted connection from " << inet_ntoa(cli_addr.sin_addr) << " on port " << ntohs(cli_addr.sin_port) << endl;
      
      // send data to client using write
	bzero(write_buffer,512);
	strcat(write_buffer,"HTTP/1.0 200 OK\nServer: BaseHTTP/0.3 Python/2.7.6\nDate: Fri, 11 Nov 2016 18:35:37 GMT\nContent-type: text/xml\nContent-length: 247\n\n<?xml version='1.0'?>\n<methodResponse>\n<params>\n<param>\n<value><array><data>\n<value><int>7</int></value>\n<value><double>2.79</double></value>\n<value><string>hello_world</string></value>\n</data></array></value>\n</param>\n</params>\n</methodResponse>\n");

      remaining_length = strlen(write_buffer);
      temp_buffer = write_buffer;
      do {
        temp = send(newsockfd, temp_buffer, remaining_length, 0);
        if (temp < 0) {
          cout << "Error: error sending data to the client" << endl;
          exit(-1);          
        } 
        temp_buffer = temp_buffer + temp;
 	remaining_length -= temp;
      } while (remaining_length != 0);

 
      bzero(read_buffer,512);

      // receive data from client using read
      n = recv(newsockfd, read_buffer, 511, 0);
      if (n < 0) {
        cout << "Error: error receiving data from client" << endl;
        exit(-1);          
      }

      cout << "Client sent the following message: " << read_buffer << endl;
      close(newsockfd);
     }
     close(sockfd);
     return 0; 
}
