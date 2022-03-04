#ifndef CLIENTP3
#define CLIENTP3

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
#include <stdbool.h>

#define RCVBUFSIZE 1024   /* Size of receive buffer */
#define SNDBUFSIZE 1024   /* Size of receive buffer */
#define CSIZE 95
#define ASCIIS 32
#define SSIZE 1024
#define PSIZE 24


void encryption(char * ptext, char * ctext, int * keytext, int flag);
void decryption(char * input, char * output, int * keytext);
void CreateKey(FILE * fp, int * p);

#endif
