/*
    Nicholas Spudich
    Andrew Spate
    Frank Bedekovich
    CET 440: Computer Networking
    Chen, W.
    10/21/2021
 */
#ifndef CLIENT
#define CLIENT
#include <stddef.h>	
#define STDAMNT 30          //indexed at 0, there's 30 users (29 students plus Dr. Chen)
//define student structure
typedef struct
{
    char id[20];        	// handles student id
    char firstname[30]; 	// handles student firstname
    char lastname[30];  	// handles student age 
    int age;				// handles student ages
    double gpa;         	// handles student gpa 
    int curactive;      	// determines if a stude30nt is active or not
    char lastlogged[20];	// handles the date of the last known logged date
    char tottime[15];   	
} stud;

struct sharedmem_struct{
    stud students[STDAMNT]; // define array of student to cycle through
};


// Function Prototypes
void dataSort(struct time_t *rawtime, struct sharedmem_struct *z, struct tm *info);
double dateToSec (int year, int month, int day, int hour, int minute, int second);
int twoDigitParse (char temp1, char temp2);
void usersByDate(struct time_t *rawtime, struct sharedmem_struct *z, struct tm *info);
void recentActivity(struct time_t *rawtime, struct sharedmem_struct *z, struct tm *info);
void basicLoops(struct time_t *rawtime, struct sharedmem_struct *z, struct tm *info);

#endif
