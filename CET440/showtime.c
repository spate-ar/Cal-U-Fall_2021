//Andrew Spate
//CET 440- Lab 2
#include <stdio.h>
#include <time.h>
#include <string.h>

/*       monthLookup
General:  Takes numerical version of month of year and prints corresponding string
Pre Conditions: must have int (1-12)
Post Conditions: none
*/
/*       dayLookup
General: Takes numerical version of day of week and prints corresponding string
Pre Conditions: must have int (0-6)
Post Conditions: none
*/
void monthLookup(int monthNUM);
void dayLookup(int dayOfWEEK);
int main()
{
	time_t rawtime;
	struct tm *info;
	int sec, monthNUM,dayOfWEEK;
	time(&rawtime);                                                             // pull raw time using the time.h library
	info=localtime(&rawtime);                                                   // convert raw time to local time
	fprintf(stderr,"Today is ");                                                // start printing the string
	dayOfWEEK= info->tm_wday;                                                   // access the number relative to what day of the week it is
	dayLookup(dayOfWEEK);                                                       // using the number provided, print the spelling based on what day of the week it is
	fprintf(stderr,"- ");                                                       // print a dash for the main string
	monthNUM=info->tm_mon+1;                                                    // determine the month number for switch case to print full spelled month
	monthLookup(monthNUM);                                                      // look up and print the corresponding month
	fprintf(stderr,"%d, %d.  Current time is:", info->tm_mday,info->tm_year+1900); // print the day of the month and the year, adding the 1900 since the year is how many years since 1900
	fprintf(stderr,"\n");                                                       // print a new 
	fprintf(stderr,"%d:%02d:%02d", info->tm_hour, info->tm_min, info->tm_sec);  // print the initial time with formatting for double digits
	while(1)
	{
	time(&rawtime);                                                             // reaccess raw time data
	info=localtime(&rawtime);                                                   // reconvert to local
	printf("\r%02d:%02d:%02d   ", info->tm_hour, info->tm_min, info->tm_sec);   // erase old line and reprint the time
	if ((info->tm_hour==0) && (info->tm_sec==0) && (info->tm_min==0))          // if midnight aka new day, re print whole statement
        {
             fprintf(stderr,"\r\r");                                                     // erase both lines for a reprint
             fprintf(stderr,"Today is ");                                                // start printing the string
	         dayOfWEEK= info->tm_wday;                                                   // access the number relative to what day of the week it is
	         dayLookup(dayOfWEEK);                                                       // using the number provided, print the spelling based on what day of the week it is
	         fprintf(stderr,"- ");                                                       // print a dash for the main string
	         monthNUM=info->tm_mon+1;                                                    // determine the month number for switch case to print full spelled month
	         monthLookup(monthNUM);                                                      // look up and print the corresponding month
	         fprintf(stderr,"%d, %d.  Current time is:", info->tm_mday,info->tm_year+1900); // print the day of the month and the year, adding the 1900 since the year is how many years since 1900
	         fprintf(stderr,"\n");                                                       // print a new 
	         fprintf(stderr,"%d:%02d:%02d", info->tm_hour, info->tm_min, info->tm_sec);  // print the initial time with formatting for double digits
          }
	}
	return 0;
}

void dayLookup(int dayOfWEEK)
{
	switch(dayOfWEEK)                                                           // takes number correlated with day of week and chooses option 
	{
		case(0):                                                                // if 0, prints sunday
		{
			fprintf(stderr,"Sunday ");
			break;
		}
		case(1):                                                                // if 1, prints monday
		{
			fprintf(stderr,"Monday ");
			break;
		}
		case(2):                                                                // if 2, prints tuesday
		{
			fprintf(stderr,"Tuesday ");
			break;
		}
		case(3):                                                                // if 3, prints Wednesday
		{
			fprintf(stderr,"Wednesday ");
			break;
		}
		case(4):                                                                // if 4, prints Thursday
		{
			fprintf(stderr,"Thursday ");
			break;
		}
		case(5):                                                                // if 5, prints Friday
		{
			fprintf(stderr,"Friday ");
			break;
		}
		case(6):                                                                // if 6, prints Saturday
		{
			fprintf(stderr,"Saturday ");
			break;
		}
	
	}
	return;
}


void monthLookup(int monthNUM)
{
	 switch(monthNUM)                                                           // takes month of the year and prints the month
	{
		case(1):                                                                // if 1, prints January
		{
			fprintf(stderr," January ");                                        
			break;
		}
		case(2):                                                                // if 2 prints february
		{
			fprintf(stderr," February ");
			break;
		}
		case(3):                                                                // if 3, prints March
		{
			fprintf(stderr," March ");
			break;
		}
		case(4):                                                                // if 4, prints April
		{
			fprintf(stderr," April ");
			break;
		}
		case(5):                                                                // if 5, prints May
		{
			fprintf(stderr," May ");
			break;
		}
		case(6):                                                                // if 6, prints June
		{
			fprintf(stderr," June ");
			break;
		}
		case(7):                                                                // if 7 prints july
		{
			fprintf(stderr," July ");
			break;
		}
		case(8):                                                                // if 8, prints August
		{
			fprintf(stderr," August ");
			break;
		}
		case(9):                                                                // if 9, Prints september
		{
			fprintf(stderr," September ");
			break;
		}
		case(10):                                                               // if 10, prints October
		{
			fprintf(stderr," October ");
			break;
		}
		case(11):                                                               // if 11, prints Novemeber
		{
			fprintf(stderr," November ");
			break;
		}
		case(12):                                                               // if 12, prints December
		{
			fprintf(stderr," December ");
			break;
		}
	}
	return;
	
}

