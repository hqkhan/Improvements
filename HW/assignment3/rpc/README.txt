Examples of XML-RPC clients and servers for many different languages.
Each example is driven out of a Makefile.

To run the server type:

make server

To run the client, open another window and run:

make client

The c++32 and java examples require compiling first, by running:

make all

All clients and servers across all languages are compatible.
That is run can a client from one language and have it make requests
to a server in another language.

The only caveat is the PHP server, which will only execute files that end in *.php.
To use clients in other languages with the PHP server, you must change the URL in 
the client code from "http://localhost:8080/RPC2" to be "http://localhost:8080/server.php"
