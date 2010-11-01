
/*
 * zmq - A ZeroMQ Shell Wrapper. Copyright (C) Burak Arslan
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
 */

#include <stdexcept>
#include <iostream>
using std::cout;
using std::endl;

#include <cstdlib>
#include <cstring>

#include <zmq.hpp>

void usage() {
    cout << "Usage: \n"
         << "    zmq <SOCKET_TYPE> <URI> <MSG>\n"
         << "\n";

    std::exit(0);
}

int get_socket_type(const char *str) {
    int retval = 0;

    if (! std::strcmp(str, "REQ")) {
        retval = ZMQ_REQ;
    }
    else {
        throw std::invalid_argument(
            "Invalid socket type. Only \"REQ\" is supported."
        );
    }

    return retval;
}

int main(int argc, char **argv) {
    if (argc < 3) {
        usage();
    }

    int socket_type = get_socket_type(argv[1]);

    zmq::context_t context(1);
    zmq::socket_t socket(context, socket_type);
    socket.connect(argv[2]);

    if (argc == 3) {
        zmq::message_t empty_message;
        socket.send(empty_message);

        socket.recv(&response);
    }
    else {
        for (int i=3; i<argc; ++i) {
            size_t arg_len= std::strlen(argv[i]);
            zmq::message_t message(arg_len);
            std::memcpy(message.data(), argv[i], arg_len);
            socket.send(message, ZMQ_SNDMORE && ( (i+1) < argc) );
        }

        int64_t more=-1;
        size_t more_size = sizeof (more);
        while(more) {
            zmq::message_t response;
            socket.recv(&response);

            std::string response_str((const char *)response.data(), response.size());
            cout << response_str << endl;

            socket.getsockopt(ZMQ_RCVMORE, &more, &more_size);
        }
    }

    return 0;
}
