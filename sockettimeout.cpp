// https://www.freebsd.org/cgi/man.cgi?query=setsockopt&sektion=2
#include <sys/types.h>
#include <sys/socket.h>
     
struct timeval timeout;      
timeout.tv_sec = 10;
timeout.tv_usec = 0;

// socket
sd = socket(PF_INET, SOCK_STREAM, 0);

// timeout
if (setsockopt (sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,sizeof(timeout)) < 0)
    error("setsockopt failed\n");

if (setsockopt (sockfd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout,sizeof(timeout)) < 0)
    error("setsockopt failed\n");
