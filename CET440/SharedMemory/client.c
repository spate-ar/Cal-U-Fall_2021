/*
    Nicholas Spudich
    Andrew Spate
    Frank Bedekovich
    CET 440: Computer Networking
    Chen, W.
    10/21/2021
 */
#include "client.h"			// for holding the structure and function prototypes
#include <errno.h>			// for error handling on system calls
#include <sys/shm.h>		// for shared memory facility defines
#include <time.h>			// for anything related to the current time

#define SHMKEY 0x77000 + 01 // shared memory "key"
#define STDAMNT 30          // indexed at 0, there's 30 users (29 students plus Dr. Chen)


   
basicLoops(struct time_t *rawtime, struct sharedmem_struct *z, struct tm *info)
{
    int i = 0, j = 0, k=0, l=0, n=0, m=0, y = 0;		//variables used for various purposes
    int sumAge=0;
    float sumGpa = 0,
          avgGpa = 0,
          avgAge = 0;
    int activeMem = 0,  	// stores the # of active members
        studNum[STDAMNT];
    for(i = 0; i < STDAMNT; i++)
    {
        // accumulate gpa and age
        sumGpa += z->students[i].gpa;		// gpa accumulator
        sumAge += z->students[i].age;		// age accumulator
        
        if(z->students[i].curactive == 1)		// test to see what users are active
        {
            //printf("%d  ",i);
            studNum[j] = i;			// saveing value to stdnum
            j++;
            activeMem++;
        }
    }
    
    // calculate average gpa and age for all students
    avgGpa = sumGpa/STDAMNT;		//calculating gpa
    avgAge = sumAge/STDAMNT;  		//calculating age
    printf("The average GPA is... %.2f \n", avgGpa);	// prints out the average gpa of the class
    printf("The average age is... %.2f \n", avgAge);	// prints out the average age of the class
    printf("There are %i active users, \n", activeMem);	
    printf("\t\tUSERS: \n");
    for(i = 0; i < j; i++)
    {
        printf("\t\t %s, %s \n", z->students[studNum[i]].lastname, z->students[studNum[i]].firstname);		// prints out all active users
    }
    return;           
                
}
recentActivity(struct time_t *rawtime, struct sharedmem_struct *z, struct tm *info)
{
     //determine activity in past 3days
    double today, 
           yesterday, 
           twodaysago, 
           threedaysago;
    int i = 0, j = 0, k=0, l=0, n=0, m=0, y = 0;		//variables used for various purposes
    double temptime=time(&rawtime);		// gets the current time
    char tt70[20];
    today= dateToSec(info->tm_year, info->tm_mon+1, info->tm_mday, 0, 0, 0);  //0 for hour, minute, second, looking for seconds of midnight to create day offset
    //printf("Today:  %f\n",today);
    yesterday= today- 86400;
    twodaysago= yesterday-86400;
    threedaysago= twodaysago-86400;
    //printf("Yest:   %f\n",yesterday);
    //printf("2days:  %f\n",twodaysago);
    for(i=0; i< STDAMNT; i++)
    {   strncpy(tt70,z->students[i].lastlogged,20);
        int year, month, day, hour, minute, second, temp;	// variables used for determining time
        temp=((int)(tt70[0]-48)*10);                		//2
        temp= (temp+((int)(tt70[1])-48))*10;             	//0
        temp= (temp+((int)(tt70[2])-48))*10;            	//2
        temp= (temp+((int)(tt70[3])-48));             	//1
        year=temp;  
        month=twoDigitParse(tt70[5],tt70[6]);
        day=twoDigitParse(tt70[8],tt70[9]);
        hour=twoDigitParse(tt70[11],tt70[12]);
        minute=twoDigitParse(tt70[14],tt70[15]);
        second=twoDigitParse(tt70[17],tt70[18]);
        double studenttime;
        //printf("%d %d,%d    %d: %d :%d\n",month, day, year, hour, minute, second);

        studenttime=dateToSec(year, month+1, day, hour, minute, second);		// calculateing the value of fun
        studenttime=studenttime+167415065;     //upate current time offset
        //printf("%f-%f\n",today,studenttime);
        if (studenttime>today)
        {    k++;
        }
        else if (studenttime>yesterday)
        {
             l++;
        }
        else if (studenttime>twodaysago)
        {    
             n++;
        }
        else if (studenttime>threedaysago)
        {
             m++;
        }
    }
    printf("%d users today\n", k+1); //k				// prints out the users online today
    printf("%d users yesterday\n", l+1); //l			// prints out the users online yesterday
    printf("%d users two days ago\n", j+1); // j		// prints out the users online two days ago
    printf("%d users three days ago\n", m+1); // m		// prints out the users online three days ago 
    return;    
              
}
usersByDate(struct time_t *rawtime, struct sharedmem_struct *z, struct tm *info)
{   
    char tt70[20]; 
    int logbydate[STDAMNT][2],
        tempar[STDAMNT][2];
    int i = 0, j = 0, k=0, l=0, n=0, m=0, y = 0;		//variables used for various purposes
    double temptime=time(&rawtime);		// gets the current time
    printf("Users by Activity (Currently active to oldest Log in):\n");
    for(i = 0; i < STDAMNT; i++)
    {
          logbydate[i][1]=i;
          strncpy(tt70,z->students[i].lastlogged,20);
          int year, month, day, hour, minute, second, temp;	// variables used for determining time
          temp=((int)(tt70[0]-48)*10);                		//2
          temp= (temp+((int)(tt70[1])-48))*10;             	//0
          temp= (temp+((int)(tt70[2])-48))*10;            	//2
          temp= (temp+((int)(tt70[3])-48));             	//1
          year=temp;
          
          month=twoDigitParse(tt70[5],tt70[6]);
          day=twoDigitParse(tt70[8],tt70[9]);
          hour=twoDigitParse(tt70[11],tt70[12]);
          minute=twoDigitParse(tt70[14],tt70[15]);
          second=twoDigitParse(tt70[17],tt70[18]);
          //printf("%d %d %d %d %d %d\n", year, month, day, hour, minute, second);
          if (year==0 && month==0 && day== 0)   // throw inactive users to end
          {
                      year=9999;				// values given to inactive users
                      month=99;
                      day=99;
                      hour=99;
          }
          double fun= dateToSec(year, month, day, hour, minute, second);		// calculateing the value of fun
          fun= temptime-fun;		// more calculating
          logbydate[i][2]= fun;		//setting logbydate to the value of fun
     }
    for(y=0;y<STDAMNT-1;y++)		// sorts the login dates
    {
       for(i=0; i<STDAMNT-y-1; i++)
       {
             if(logbydate[i][2]>logbydate[i+1][2])                           // 29 vs 30 if 29>30                             
             {
                 tempar[i][1]= logbydate[i][1];
                 tempar[i][2]= logbydate[i][2];
                 logbydate[i][1]=logbydate[i+1][1];
                 logbydate[i][2]=logbydate[i+1][2];
                 logbydate[i+1][1]=tempar[i][1];
                 logbydate[i+1][2]=tempar[i][2];
             }
         }
    }    

    for(i=0; i<STDAMNT; i++)
    {
        printf("\t\t%s, %s\n",z->students[logbydate[i][1]].lastname, z->students[logbydate[i][1]].firstname);		//prints out students activity by their last login date
    }
    return;         
}

double dateToSec (int year, int month, int day, int hour, int minute, int second)
{
       double fun=((year-1970)*31557600)+(month*2629800)+(day*86400)+(hour*3600)+(minute*60)+second;
       return fun;
}

int twoDigitParse(char temp1, char temp2)
{
    int temp;
    temp=((int)(temp1-48)*10);                  	
    temp= (temp+((int)(temp2)-48)); 
    return temp;
}

dataSort(struct time_t *rawtime, struct sharedmem_struct *z, struct tm *info)
{
    basicLoops(rawtime, z, info);
    recentActivity(rawtime, z, info);
    usersByDate(rawtime, z, info);
}

