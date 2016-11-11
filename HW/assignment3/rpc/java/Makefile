CLASSPATH=./lib/commons-codec-1.3.jar:./lib/xmlrpc-2.0.1.jar:.

all: Server.class Client.class

server:
	@java -classpath $(CLASSPATH) Server

client:
	@java -classpath $(CLASSPATH) Client

Server.class: Server.java
	javac -classpath $(CLASSPATH) Server.java

Client.class: Client.java
	javac -classpath $(CLASSPATH) Client.java

clean:
	rm *.class
