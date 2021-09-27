/******************************************************************************
Group Names:	Nicholas Spudich
			    Andrew Spate
			    Kelli Huff

Professor:		Dr. Chen, W.
Class:			CET 440: Computer Networking
Assignment:		Lab Assignment 3
Date:			9/16/2021

References:
	Shuffle Function: 
		https://stackoverflow.com/questions/6127503/shuffle-array-in-c
	
*******************************************************************************/
#include <stdio.h>      // printf, scanf, etc.
#include <string.h>     // string operations
#include <stdlib.h>     // srand, rand
#include <time.h>       // time (srand)
#include "synciph.h"	// header file created


// MAIN
int main()
{
	srand(time(0));
	
    // for storing the user inputted message
    char msg[120];
    
    // randomly transformed cipher pulled from inputted printable characters.
    
	char cipher[96];
    char pChars[96];
    
    int temp, k;
    int length=0;
    
    // prompt for user input, Store: msg
    printf("Please enter a string!\n");
    gets(msg);
    
    // create the printable characters list 32-126 ASCII
    createPChars(pChars);
    
    shuffle(pChars, 96);
    
     // determine length of msg entered
    while(msg[length]!='\0')
    {
        length++;
    }
    
    // print the ciphered message
    for (k=0; k< length; k++)
    {
        temp= msg[k]-32;
        printf("%c", pChars[temp]);
    }
    printf("\n");
    //system("pause");
    
    // test function for printing
    printPChars(pChars);
    
    
    
    return 0;
}


