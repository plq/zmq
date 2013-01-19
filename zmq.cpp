
/*
 * zmq - A ZeroMQ Shell Wrapper. Copyright (C) Arskom Ltd.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the names of Arskom Ltd. or the ZeroMQ project, nor the
 *       names of its employees or contributors may be used to endorse or
 *       promote products derived from this software without specific prior
 *       written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */


#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <cstring>

#include <zmq.hpp>

using std::cout;
using std::endl;


void usage() {
    cout << "Usage: \n"
         << "    zmq <SOCKET_TYPE> <URI> <MSG>\n"
         << "\n";

    std::exit(1);
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


void recv_multipart(zmq::socket_t &socket) {
    int64_t more=-1;
    size_t more_size = sizeof (more);
    while(more) {
        zmq::message_t response;
        socket.recv(&response);

        std::string response_str((const char *)response.data(),
                                                             response.size());
        cout << response_str << endl;

        socket.getsockopt(ZMQ_RCVMORE, &more, &more_size);
    }
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

        recv_multipart(socket);
    }
    else {
        for (int i=3; i<argc; ++i) {
            size_t arg_len= std::strlen(argv[i]);
            zmq::message_t message(arg_len);
            std::memcpy(message.data(), argv[i], arg_len);
            socket.send(message, ZMQ_SNDMORE && ( (i+1) < argc) );
        }

        recv_multipart(socket);
    }

    return 0;
}
