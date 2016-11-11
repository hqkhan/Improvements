Place in this directory a Makefile that builds your server, and your server.cpp code.

We should be able to run your server by typing $./server after compiling by typing "make".  




This assignment is designed to provide experience with both sockets and RPCs.  The goal is to write a server using sockets that imitates or "spoofs" an RPC server executing a particular function.  That is, your socket-based server should return exactly the same output to the RPC client, as a real RPC server would return.  For the assignment, you will use the same code as in the socket and RPC example.  Your goal is to write a new socket-based server that gives the same results as the RPC server returns to the RPC client in the RPC example code.

Download assignment3.tar.gz

To complete the assignment, you need to learn what data XML-RPC actually transmits between client and server, and between server and client.  To do this, first write a socket-based server that accepts connections on the same port as one of the XML-RPC clients (hint: they all do the same thing, so any one will work), and simply prints to standard out whatever the XML-RPC client sends to the server.  You can modify the server.cpp example code in the socket directory. This shows you the format of a client XML-RPC message. 

Next, write a socket-based client that opens a connection to a real XML-RPC server (hint: you need to run one of the real XML-RPC servers in the example) and sends exactly the message that you just printed out to real server.  To do this, simply hardcode the message as a string in the client, and transmit it to the server.  You might use the strcpy() and strcat() functions here to copy a string to a buffer, and concatenate a new string to the end of an existing string. After sending the message, the client should receive a message from the server---you should print the message it receives to standard out. This is the information you need to write your socket-based "spoof" server.  Next, alter you socket-based server from above to send back this message back to the XML-RPC client after receiving the initial message.   Just as before, simply hardcode the message that the client expects as a string inside your server. 

To grade your assignment, we will start your socket-based spoof

Your socket-based "spoof" server

Note that you may use any machine for development, but you will be graded on the VirtualBox Ubuntu VM (or Codenvy), so make sure your solutions work correctly on that VM (or Codenvy).  You should name your solution assignment3-solutions.tar.gz. The submitted tar.gz file should look exactly like the file you downloaded, except it has your server.cpp in the top-level directory along with a Makefile that builds it by typing "make". We will grade your submissions on the VirtualBox Ubuntu VM.  To grade the assignment, we will type "make" to build your client and server, and we will then run "./server" to run your server.  Your server should be configured to listen on port 8080.  We will then run one of the XML-RPC clients on port 8000 and see if it prints the following text to standard out (which is the output of the XML-RPC client examples).

The first array value is 7 the second array value is 2.79 and the third array value is hello_world

You should upload your assignment3-solutions.tar.gz to Moodle by Thursday, November 10th at 11:59pm. 
