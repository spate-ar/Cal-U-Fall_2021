#include "Clientp3.h"

/*
General: Creates a array that will be the key for encrypting and decrypting
Preconditions: correct file opened for reading
Post Conditions: file passed back to main
*/
void CreateKey(FILE * fp, int * p)
{
    int i = 0;
    
    for(i = 0; i < SSIZE; i++)
	{
    	fscanf(fp, "%d", &p[i]); // read from the FILE
	}  
}
/*
General: Encrypts a message for sending to server
Preconditions: must have a message and a key
Postconditions: will return a string to be sent
*/

void encrypt(char * ptext, char * ctext, int * keytext, int flag)
{
	int i, length;
	length = strlen(ptext);
	
	for (i=0; i<length; i++)
	{
		ctext[i]=keytext[ptext[i]-ASCIIS]+ASCIIS;  //The first keyboard printable character have an ASCII code 32, defined as ASCIIS char * keytext
	}
}

/*
General: Decrypts a message from the server
Preconditions: Will recieve an encrypted string from server and a key
Postconditions:  Will return the decyphered message to print
*/

void decrypt(char * input, char * output, int * keytext)
{
    int i, length;
    length = strlen(input);
    //printf("%d\n", length);
    for (i=0; i < length; i++)
    {
        //printf("Attempt %d\n",i);
        // search in key for the present value
        int found = 0;
        int j=0;
        //printf("input: %d \n", input[i]);
        //printf("loop %i", i);
        if(input[i] == 0x0A)
            printf("\n");
            //output[i] = 0x0A;
            
        else
        {
        while (found == 0)
        {
            //printf("Keytext: %i \n", keytext[j]);
            
            if (keytext[j] + ASCIIS == input[i])
            {
                output[i]=(j + ASCIIS);
                found = 1;
                printf("%c", output[i]);
            }
            else
            {
                j++;
            }
        
        }
        }
        //ctext[i]=key[ptext[i]-ASCIIS]+ASCIIS;  //The first keyboard printable character have an ASCII code 32, defined as ASCIIS.
    }
}
