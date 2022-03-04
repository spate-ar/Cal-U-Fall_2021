#include "Clientp2.h"

void WriteToFile(char quitstr[], char logstr[], FILE *fp) //write quit/logout time to file
{
    fputs(logstr, fp);
    fputs(quitstr, fp);
}
