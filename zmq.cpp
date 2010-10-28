
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

#include <cstdlib>

#include <iostream>
using std::cout;
using std::endl;

#include <zmq.hpp>

void usage() {
    cout << "Usage: \n"
         << "    zmq <SOCKET_TYPE> <URI> <MSG>\n"
         << "\n";

    std::exit(0);
}

int main(int argc, char **argv) {
    if (argc != 3) {
        usage();
    }

    return 0;
}
