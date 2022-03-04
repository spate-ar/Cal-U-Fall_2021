/*
    CET 440: Computer Networking - Client/Server Lab Part III
    Nicholas Spudich
    Andrew Spate
    Frank Bedekovich
    12/2/2021
    
*/

#include "Clientp3.h"

int main(int argc, char *argv[])
{
    int servSock = 0, n = 0;
    char recvBuff[RCVBUFSIZE];
    char sendBuff[SNDBUFSIZE];
    char derecvBuff[RCVBUFSIZE];
    char desendBuff[SNDBUFSIZE];
    char command[20], username[8];
    struct sockaddr_in serv_addr; 
    int quit=0, mistake=0, bytesRcvd;
    char servIP[16];
    int port;
    FILE *fp;
    int i = 0;
    char quitstr[50];
    char *q = quitstr;
    size_t quitSize = 50;
    char string[20];
    char logstr[50];
    char *l = logstr;
    size_t logSize = 50;
    ssize_t q_line_size;
    ssize_t l_line_size;
    time_t rawtime;
	struct tm *info;
	time(&rawtime); // pull raw time using the time.h library
	info=localtime(&rawtime);
	char ptext[SSIZE]="";
	char ctext[SSIZE]="";
	int keytext[SSIZE] = {0};
	int *p = keytext;
	//password checking
	bool flag = false;  // main loop flag
	char pWord[PSIZE] = ""; // PSIZE = 24, for storing the password
	bool upperCase = false;
	bool lowerCase = false;
	bool specialCase = false;
	bool number = false;
	int passwordSize = 0;
	int pNum = 0; // for checking the cases
	
	fp = fopen("key.txt", "r");
	CreateKey(fp, p);
	fclose(fp);
	printf("Please input the port to connect:");
    scanf("%d", &port);     // not encrypted
	
    strcpy(servIP, "158.83.254.100"); /* First arg: DRACO1 IP address (dotted quad) */

    if((servSock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    }
    memset(&serv_addr, '0', sizeof(serv_addr)); 
    serv_addr.sin_family      = AF_INET;            /* Internet address family */
    serv_addr.sin_addr.s_addr = inet_addr(servIP);  /* Server IP address */
    serv_addr.sin_port        = htons(port);        /* Server port */

    if( connect(servSock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    } 
    if ((bytesRcvd = recv(servSock, recvBuff, RCVBUFSIZE + 1, 0)) <= 0)
        printf("Error: recv() failed or connection closed prematurely\n");      
    do
    {
        printf("\n\nServer_echo: "); 
        decrypt(recvBuff, derecvBuff, keytext);
        printf("Please type to send to server (type -1 to quit):");        
        if (strcmp(derecvBuff, "Please enter a password")!=0)
        {
                               strcpy(desendBuff,sendBuff);
                               scanf("%s", sendBuff); //decrypted
                               strcpy(desendBuff,sendBuff);
         }
        else
        {
             printf("Password must be over 8 character and use 3/4 of Uppercase Letter, Lowercase letter, Special Caracter, number\n");
             while(flag == false)    // while the password is no good
             {
                        scanf("%s", pWord);
                        passwordSize = strlen(pWord);
        
                        if(passwordSize >= 8)   // check to see if the password is at least 8 characters long
                        {
                        printf("GOOD JOB! Your password is long enough. ");
                        for(i = 0; i < passwordSize; i++)
                        {
                              if(pWord[i] >= 32 && pWord[i] <= 47 || pWord[i] >= 58 && pWord[i] <= 64 || pWord[i] >= 91 && pWord[i] <= 96 || pWord[i] >= 123 && pWord[i] <= 126) // check for special characters
                              {
                                          specialCase = true; // set specialCase to true
                              }
                              if(pWord[i] >= 48 && pWord[i] <= 57)   // check for a number
                              {
                                          number = true;   // set number to true
                              }
                              if(pWord[i] >= 65 && pWord[i] <= 90)   // check for a uppercase letter
                              {
                                          upperCase = true;   // set upperCase to true
                              }
                              if(pWord[i] >= 97 && pWord[i] <= 122)   // check for a lowercase letter
                              {
                                          lowerCase = true;   // set lowerCase to true
                              }
                         }
            // increment flag number if the criteria is met
                         if(specialCase)
                         {
                                        pNum++;
                         }
                         if(number)
                         {
                                        pNum++;
                         }
                         if(upperCase)
                         {
                                        pNum++;
                         }
                         if(lowerCase)
                         {
                                        pNum++;
                         }
                         if(pNum >= 3)
                         {
                                        flag = true; // cancel main loop : password meets the correct criteria
                                        printf("Congratulations! Your password meets the necessary requirements!\n");
                                        strcpy(desendBuff,sendBuff);
                                        //scanf("%s", sendBuff); //decrypted
                                        strcpy(desendBuff,pWord);
                         }
                         else
                         {
                // Reset the flag number and the flags
                                         pNum = 0;
                                         lowerCase = false;
                                         upperCase = false;
                                         specialCase = false;
                                         number = false;
                          }
                }
                else
                {
                    printf("Your password is not long enough! \nPlease enter in at least 8 alphanumeric & special characters!\n");
                    memset(pWord, 0, PSIZE); // clear password
                }
            }                                       
        }
        encrypt(desendBuff, sendBuff, keytext, 1);
        if (send(servSock, sendBuff, sizeof(sendBuff), 0) < 0)
	        printf("Error: send() failed\n");
         sleep(1);
        if ((strcmp(desendBuff, "-1") == 0) || (strcmp(desendBuff, "Quit") == 0))
        {
            bytesRcvd = 0;
        }                 
	    else
        { 
            memset(&recvBuff, '0', sizeof(recvBuff));
           if ((bytesRcvd = recv(servSock, recvBuff, RCVBUFSIZE + 1, 0)) <= 0)
                  printf("Error: recv() failed or connection closed prematurely\n");
        }
    } while (bytesRcvd>0);
    close(servSock); //close the socket
    return 0;
}
