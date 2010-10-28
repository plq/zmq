
This is a shell wrapper for (ZeroMQ)[http://zeromq.org]. Currently it can only 
send to a REQ socket.

Building
--------

Just run make. You can customize include or library paths like so:

    make LIBRARY_PATH=$USER/.local/lib INCLUDE_PATH=$USER/.local/include

Usage
-----

Template:

    zmq `<SOCKET_TYPE>` `<DESTINATION_URI>` `[messages ...]`

Example:

    zmq REQ tcp://localhost:5556 hello

You will see the contents of the first return message, and the program will
exit.

