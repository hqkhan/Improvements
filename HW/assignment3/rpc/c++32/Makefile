CC=g++
DEBUG=-g
CFLAGS=$(DEBUG) -c
SERVER_SOURCE=server.cpp
SERVER_INCLUDE=-I. -I./include -I./include
SERVER_LIB=./lib/libxmlrpc_server_abyss++.a ./lib/libxmlrpc_server++.a ./lib/libxmlrpc_server_abyss.a ./lib/libxmlrpc_server.a ./lib/libxmlrpc_abyss.a -lpthread ./lib/libxmlrpc++.a ./lib/libxmlrpc.a ./lib/libxmlrpc_util.a ./lib/libxmlrpc_xmlparse.a ./lib/libxmlrpc_xmltok.a

CLIENT_SOURCE=client.cpp
CLIENT_INCLUDE=-I. -I./include -I./include 
CLIENT_LIB=./lib/libxmlrpc_client++.a ./lib/libxmlrpc_client.a ./lib/libxmlrpc++.a ./lib/libxmlrpc.a ./lib/libxmlrpc_util.a ./lib/libxmlrpc_xmlparse.a ./lib/libxmlrpc_xmltok.a  -L/usr/lib/i386-linux-gnu -lcurl ./lib/libxmlrpc_packetsocket.a

all:
	$(CC) $(CFLAGS) $(SERVER_INCLUDE) server.cpp -o server.o
	$(CC) -o xmlrpc-server server.o $(SERVER_LIB)
	$(CC) $(CFLAGS) $(CLIENT_INCLUDE) client.cpp -o client.o
	$(CC) client.o $(CLIENT_LIB) -o xmlrpc-client

server:
	./xmlrpc-server

client:
	./xmlrpc-client
	
clean:
	rm -rf *.o xmlrpc-server xmlrpc-client

