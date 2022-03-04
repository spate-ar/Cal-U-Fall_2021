/*
	Nicholas Spudich
	Andrew Spate
	Frank Bedekovich
	CET 440: Computer Networking
	Chen, W.
	10/21/2021
 */

#include <stdio.h>			// for standard system I/O stuff
#include <errno.h>			// for error handling on system calls
#include <sys/types.h>		// for system defined types
#include <sys/ipc.h>		// for IPC permission structure
#include <sys/shm.h>		// for shared memory facility defines
#include <time.h>			// for getting the time for various functions
#include <stdbool.h>		// for useing booleans in the program
#include <string.h>			// for useing strings in the program
#include "client.h"			// for holding the structure and function prototypes
#define SHMKEY 0x77000 + 01 // shared memory "key"

main()
{
    time_t rawtime;     // for storing rawtime
    struct tm *info;    		// for accessing time 
    time(&rawtime);     		// pull raw time using the time.h library
    info=localtime(&rawtime);  	// convert raw time to local time
    int shm_id,         		// stores the shared memory id
        sumAge = 0;     		// stores the sum of students ages
    bool flag= true;			// setting a boolean called flag to true
	struct sharedmem_struct *z; // z will point to shared memory array
    shm_id = shmget( SHMKEY, 0, 0 );
    if ( shm_id == -1 )			// check shmget() return value
    {
    	printf( "\nError: shmget() failed, errno = %i\n", errno );
    	perror( "shmget()" );
    	exit( -1 );
    }
    else
        printf( "\nshmget() successful, shm_id = %i\n", shm_id );
        //return shm_id;
    z = (struct sm_struct *) shmat( shm_id, 0, SHM_RDONLY );
    if ( (int) z == -1 )
    {
    	printf( "Error: shmat() failed, errno = %i\n", errno );
    	perror( "shmat()" );
    	exit( -1 );
    }
    dataSort(rawtime, z, info);
//  --------------------------------------------------------------------
//  done with shared memory, detach from it
//  --------------------------------------------------------------------
    shmdt( (void *) z );
    

    
    
    

      
    
    
    return( 0 );	// ending program
}



