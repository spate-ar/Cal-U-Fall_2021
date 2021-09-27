#include "synciph.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
// FUNCTIONS

// Input: starting ASCII value, Return: character array with +95 from the original ASCII value.
void createPChars(char* pChars)
{
    char charNum[3] = " ";
    int i;
    // 32-126 (starting - ending)
    for(i = 0; i < 95; i++)
    {
        pChars[i] = charNum[0];
        charNum[0]++;
    }   
}

void printPChars(char* pChars)
{ //sizeof(pChars)/sizeof(pChars[0])
	int j;
    printf("\t\t\t\tThe Cipher Key \n");
    for(j = 0; j < 95; j++)
    {
        printf("%c = %c\t", j+32, pChars[j]);
        if(0 == (j+1)%10 && j != 0)
        {
            printf("\n");
        }
    }
}

// Input: character array, Return: cipher character array
// takes in a chracter array and assigns a 1 to 1 value for each array slot.
void createCipher(char* pChars, char* cipher)
{
    char temp[5];
    
    // lowerbound of the ASCII printable characters
    int lowerBound = 32;
    // upperbound of the ASCII printable characters
    int upperBound = 126;
    // random number to be stored
    int num = 0;
    int j = 0;
    int fFlag = 0;
    int i;

    // test the value to see if it is unique
    // outer loop to fill the list
    for(i = 0; i < (upperBound - lowerBound + 1); i++)
    {
        
        do
        {   
            // generate a value using the upper/lowerbound
            num = (rand() % (upperBound - lowerBound + 1)) + lowerBound;
                
            // convert the number to string format to test
            sprintf(temp, "%d", num);
            
            if(temp[0] == cipher[j])
            {
                fFlag = 1;
            }
            
        } while(j < i);    
        
        if(fFlag == 0)
        {
            cipher[j] = temp[0];
        }
        
        // reset the flag
        fFlag = 0;
    }
}

void shuffle(char* pChars, size_t n)
{
    if(n > 1)
    {
        size_t i;
        for(i = 0; i < n - 1; i++)
        {
            size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
            int t = pChars[j];
            pChars[j] = pChars[i];
            pChars[i] = t;
        }
    }
}
