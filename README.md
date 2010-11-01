
This is a shell wrapper for [ZeroMQ](http://zeromq.org). Currently it can talk 
with a zeromq server using only a REQ socket.

Building
=========

Just run `make`. You can customize include or library paths like so:

    make LIBRARY_PATH=$HOME/.local/lib INCLUDE_PATH=$HOME/.local/include

Installing
===========

just run `make install`

You can customize installation prefix like so:

    make install PREFIX=$HOME/.local

Using
======

Template:

    zmq <SOCKET_TYPE> <DESTINATION_URI> [messages ...]

Example:

    zmq REQ tcp://localhost:5556 hello

Sockets
-------

In REQ mode, zmq sends one message, recv's one message, then exits. The
messages can be multipart messages -- zmq sends each argument as a message part
and prints each part in an incoming message in a new line.

Just like other shell tools, this is mainly for exchanging text-only messages.
