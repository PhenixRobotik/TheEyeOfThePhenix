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
#define PORT     1717 //1.7V for history
#define MAXLINE 1024


class transmitter
{
  private:
    int sockfd;
    struct sockaddr_in servaddr;

  public:
    transmitter();
    void transmit_position(const char *to_transmit);
    void end();
};
