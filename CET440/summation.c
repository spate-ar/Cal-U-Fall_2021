/*
 *  sumation.c - CET 440 LAB 1
 *  Andrew Spate
 *  9/2/2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
recursive function
General: Perfom Summation of a number as defined in the Lab
Pre Conditions: Must have a positive integer
Post Conditions: Will return an integer
*/
int recursive(int number, int i, int sum);

int main()
{
  int i=0, u, len=0,sum=0, number=0, flag=0;                                    // integers that will be used, many are set to 0 for initial processing
  char input[u];                                                                // character array for user input
  //prompt user for input
  printf( "Sumation Calculator\n" );
  printf( "Enter positive whole number: \n" );
  //input validation loop
  while(number==0)
  {
              flag=0;
              scanf( "%s", &input );                                            // scan for input as a string
              len=strlen(input)-1;                                              // find length of string entered
              for (int u=0; len>=0;len--)                                       // run through the characters in the array
              {
                  if (input[len]=='.')                                          // test if the given character is a . for a decimal number
                  {
                     printf("Enter an integer without a decimal \n");           // reprompt user if bad data
                     flag=1;                                                    // set flag for retriggering loop
                     break;                                                     // break out of loop with flag set to recieve new data
                  }
                  if(input[len]=='-')                                           // test if given character is a - for a negative number
                  {
                     printf("Enter a positive integer\n");                      // repromt user based on inputted answer
                     flag=1;                                                    // set flag for retriggering loop
                     break;                                                     // break out of loop with flag set to recieve new data
                  }
                  if(!(input[len]=='0'||input[len]=='1'||input[len]=='2'||input[len]=='3'||input[len]=='4'||input[len]=='5'||input[len]=='6'||input[len]=='7'||input[len]=='8'||input[len]=='9'))  // test if the character is numeric.  I know there must be a more efficient way, but I didn't find it                         // test if the character is a number as well as positive
                  {
                       printf("Enter a number\n");                              // reprompt user if bad data
                       flag=1;                                                  // set flag for retriggering loop
                       break;                                                   // break out of loop with flag set to recieve new data
                  }
              } 
              //convert string into integer if no flags thrown
              if (flag==1)
              {
                 len=0;                                                         // reset the values associated with the loop
                 number=0;
              }
              else
              {
                  number=atoi(input);                                           // convert the now tested string into an integer for summation
              }
  }
  sum=recursive(number, i, sum);                                                // with good data, perform the function
  printf( "The sumation of %i is %ld.\n", number, sum);                         // print results
  system("PAUSE");                                                              // pause program to be able to read results
  return 0;
}

int recursive(int number,int i, int sum)
{
    if(i<=number)                                                               // if the loop counter is less than the inputted number
    {
                  sum=sum+i;                                                    // add sum to the sum
                  i++;                                                          // increment the loop counter
                  sum=recursive(number, i, sum);                                // call the function again
    }
    else
    {
        return sum;
    }
}
