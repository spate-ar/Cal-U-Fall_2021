#ifndef CLIENTP2
#define CLIENTP2

#include <stddef.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#include <time.h>

#define RCVBUFSIZE 1024   /* Size of receive buffer */
#define SNDBUFSIZE 1024   /* Size of receive buffer */

void WriteToFile(char quitstr[], char logstr[], FILE *fp);

#endif
