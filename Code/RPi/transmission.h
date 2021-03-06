#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define ADDR "127.0.0.1"
#define ROBOT_PORT 1717 //1.7V for history
#define LISTEN_PORT 1718
#define MAXLINE 1024


class transmitter
{
  private:
    int robot_sockfd;
    struct sockaddr_in robot_addr;
    int listen_sockfd;
    struct sockaddr_in listen_addr;

  public:
    transmitter();
    char transmit_position(const char *to_transmit);
    void end();
};
