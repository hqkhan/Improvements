CC=g++
DEBUG=
LDFLAGS=-lpthread -std=c++0x
SOURCES=server.cpp
EXECUTABLES=$(SOURCES:.cpp=)

SERVER_SOURCE=server.cpp

all: clean $(SOURCES) $(EXECUTABLES)

debug: DEBUG+=-g
debug: clean $(SOURCES) $(EXECUTABLES)

$(EXECUTABLES): 
	$(CC) $(DEBUG) $@.cpp -o $@ $(LDFLAGS)

map_example:
	$(CC) $(DEBUG) $@.cpp -o $@ $(LDFLAGS)

clean:
	rm -f $(EXECUTABLES) map_example
