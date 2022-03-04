/*
    CET 440: Computer Networking - Client/Server Lab Part II
    Nicholas Spudich
    Andrew Spate
    Frank Bedekovich
    11/10/2021
    
*/

#include "Clientp2.h"

int main(int argc, char *argv[])
{
    int servSock = 0, n = 0;
    char recvBuff[RCVBUFSIZE];
    char sendBuff[SNDBUFSIZE];
    char command[20], username[8];
    struct sockaddr_in serv_addr; 
    int quit=0, mistake=0, bytesRcvd;
    char servIP[16];
    int port;
    FILE *fp;
    char quitstr[50];
    char *q = quitstr;
    size_t quitSize = 50;
    char string[20];
    char logstr[50];
    //char *line_buf=NULL;
    char *l = logstr;
    size_t logSize = 50;
    ssize_t q_line_size;
    ssize_t l_line_size;
    
    time_t rawtime;
	struct tm *info;
	time(&rawtime); // pull raw time using the time.h library
	info=localtime(&rawtime);
	
    fp=	fopen(".clientrecords.txt","r");
    
    if (fp == NULL)
    {
        printf("empty/nonexistant file, creating new\n");
    }
    else
    {
        q_line_size=getline(&q, &quitSize, fp);
        printf("%s",q);
        l_line_size=getline(&l, &logSize, fp);
        printf("%s",l);
    }
    if (fp!=NULL)
    {
        fclose(fp);
    }
    fp = fopen(".clientrecords.txt","w");
    
    /* Function to read data from file if available, save to local variables*/
    //The last time connected: Display from file
    //print last time of login: display from file
    printf("Please input the port to connect:");
    scanf("%d", &port);


    strcpy(servIP, "158.83.254.100");             /* First arg: DRACO1 IP address (dotted quad) */

    if((servSock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    } 

    memset(&serv_addr, '0', sizeof(serv_addr)); 
    serv_addr.sin_family      = AF_INET;             /* Internet address family */
    serv_addr.sin_addr.s_addr = inet_addr(servIP);   /* Server IP address */
    serv_addr.sin_port        = htons(port); /* Server port */


    if( connect(servSock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    } 

    if ((bytesRcvd = recv(servSock, recvBuff, RCVBUFSIZE + 1, 0)) <= 0)
        printf("Error: recv() failed or connection closed prematurely\n");      
        
    do
    {
        printf("Server_echo:%s \n",recvBuff);
        printf("Please type to send to server (type -1 to quit):");
        scanf("%s", sendBuff);
        if (strcmp(sendBuff,"-1")==0)
        {   
            time(&rawtime);                                                             // reaccess raw time data
	        info=localtime(&rawtime); 
            //update variable string for time
            quitstr[0]='\0';
            sprintf(quitstr, "The last time connected:\t%04d:%02d:%02d:%02d:%02d:%02d\n", info->tm_year+1900, info->tm_mon+1, info->tm_mday, info->tm_hour, info->tm_min, info->tm_sec);
        }
        /*if (strcmp(sendBuff,"Logout")==0)
        {
            time(&rawtime);                                                             // reaccess raw time data
            info=localtime(&rawtime); 
            //update variable string of time
            logstr[0]='\0';
            sprintf(logstr, "The last time Logged In:\t%04d:%02d:%02d:%02d:%02d:%02d\n",info->tm_year+1900, info->tm_mon+1, info->tm_mday, info->tm_hour, info->tm_min, info->tm_sec);
        }*/
        if (send(servSock, sendBuff, sizeof(sendBuff), 0) < 0)
	        printf("Error: send() failed\n");
         sleep(1);
        if (strcmp(sendBuff, "-1") == 0)
        {
            bytesRcvd = 0;
        }                 
	    else
        { 
            memset(&recvBuff, '0', sizeof(recvBuff)); 
           if ((bytesRcvd = recv(servSock, recvBuff, RCVBUFSIZE + 1, 0)) <= 0)
                  printf("Error: recv() failed or connection closed prematurely\n");
          // printf("%s\n",recvBuff);
          // printf("%d\n",strlen(recvBuff));
            if((strlen(recvBuff)!=19) && (strcmp(sendBuff,"Logout")==0)) 
            {
                 
                 time(&rawtime);                                                             // reaccess raw time data
                 info=localtime(&rawtime); 
                 //update variable string of time
                 logstr[0]='\0';
                 sprintf(logstr, "The last time Logged In:\t%04d:%02d:%02d:%02d:%02d:%02d\n",info->tm_year+1900, info->tm_mon+1, info->tm_mday, info->tm_hour, info->tm_min, info->tm_sec);                    
            }                           
         }
    } while (bytesRcvd>0);
    
    WriteToFile(quitstr, logstr, fp);
    
    close(servSock); //close the socket
    return 0;
}
