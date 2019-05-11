#include "transmission.h"

transmitter::transmitter()
{
  if ( (robot_sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {//for sending positions to robot
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
  memset(&robot_addr, 0, sizeof(robot_addr));
  robot_addr.sin_family = AF_INET;
  robot_addr.sin_port = htons(ROBOT_PORT);
  robot_addr.sin_addr.s_addr = inet_addr(ADDR);

  if ( (listen_sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
  memset(&listen_addr, 0, sizeof(listen_addr));

  listen_addr.sin_family    = AF_INET; // IPv4
  listen_addr.sin_addr.s_addr = INADDR_ANY;
  listen_addr.sin_port = htons(LISTEN_PORT);

  struct timeval tv;
  tv.tv_sec = 0;
  tv.tv_usec = 1;
  setsockopt(listen_sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);

  if ( bind(listen_sockfd, (const struct sockaddr *)&listen_addr, sizeof(listen_addr)) < 0 )
  {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }
}

char transmitter::transmit_position(const char *to_transmit)
{
    int n;
    socklen_t len;
    char buffer[MAXLINE];
    sendto(robot_sockfd, to_transmit, strlen(to_transmit),0, (const struct sockaddr *) &robot_addr,sizeof(robot_addr));
    n = recv(listen_sockfd, (char *)buffer, MAXLINE,MSG_WAITALL);
    if(n>0)
    {
      return buffer[0];
    }
    return 'r';
}

void transmitter::end()
{
  close(robot_sockfd);
  close(listen_sockfd);
}
