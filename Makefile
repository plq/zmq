
LIBRARY_PATH=/usr/lib
INCLUDE_PATH=/usr/include
PREFIX=/usr/local

zmq: zmq.cpp
	g++ -O3 zmq.cpp -lzmq -o zmq -L$(LIBRARY_PATH) -I$(INCLUDE_PATH)

clean:
	-rm zmq

install: zmq
	cp zmq $(PREFIX)/bin
