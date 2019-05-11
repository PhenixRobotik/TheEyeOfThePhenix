#include "transmission.h"

transmitter::transmitter()
{
  if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
  memset(&servaddr, 0, sizeof(servaddr));

  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(PORT);
  servaddr.sin_addr.s_addr = inet_addr(ADDR);
}

void transmitter::transmit_position(const char *to_transmit)
{
    sendto(sockfd, to_transmit, strlen(to_transmit),0, (const struct sockaddr *) &servaddr,sizeof(servaddr));
}

void transmitter::end()
{
  close(sockfd);
}
