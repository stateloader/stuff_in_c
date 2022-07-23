README

MODULES
        COMMAND
        CONNECT
        RECEIVE
        REQUEST

The protocol, throughout the comments referred to as 'PROTOCOL' consist of 3 bytes (and a NULL-terminator). This protocol
will be attached at the end of every package from both the server and the client during transmissions. For the moment it's
just possble to write/read regarding comments and the device. Much logic across the program is mostly in place for making
it easier to scale things up down the road.