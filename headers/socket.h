#pragma once

struct sockaddr_un {
    uint16_t sun_family;
    char sun_path[108];
};

struct sockaddr_in {
    uint16_t sin_family;
    uint16_t sin_port;
    uint32_t sin_addr;
    unsigned char sin_zero[8];
};

struct sockaddr_in6 {
    uint16_t sin6_family;
    uint16_t sin6_port;
    uint32_t sin6_flowinfo;
    unsigned char sin6_addr[16];
    uint32_t sin6_scope_id;
};

typedef struct {
    int 	fd;
    char 	*ip;
    int 	port;
} sock_t;
