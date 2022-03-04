/*
 Project Partners:
 - Nicholas Spudich
 - Andrew Spate
 - Daniel Nash
 10/28/2021
 */

 /*	Troubleshooting Notes:
  * 	Nicholas Spudich		Date of Changes		10/31/2021
  * 	-------------------------------------------------------------
  * 	- Line 46 node.cpp : SetEdges Function (Read Notes above it)
  * 	- Line 45 main.cpp : Just a thought on array of nodes, not necessarily necessary
  * 	- Files need changed from node.cpp/node.h to graph.h/graph.c
  *
  * 	Changes:
  * 	- Changed the node class name to 'Graph' and struct to 'Node'.
  * 	- Added a few functions : in main.cpp : CreateGraph()
  * 							: in node.cpp : CreateNode()
  * 										  : Display()
  * 	- Fixed the destructor to match the linked list.
  * 	----------------------------------------------------------------
  *
  */

#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>
#include <stdlib.h>
#include <ctime>
#include <iomanip>
#include <cmath>  							//include math lib

#include "graph.h"

using namespace std;

/*==================
 Function Prototypes
 ==================*/

/*BruteForce
General: Derives the minimum dominating set of the current graph, and writes data to file/screen
Preconditions: must have a graph of nodes, needs the number of nodes in the graph, and needs the output file for writing
PostCondtions: will write to file and screen after complete, may take a while
*/
void BruteForce(struct Node* n, Graph g, int size, ofstream& o);


int main()
{
	int size = 9;							// size of current graph, we changed this value when adjusting how many nodes per run
	int numNodes = size;
	bool sizeFlag = true;					// main loop flag
	struct Node n;							// define graph struct

	Graph g;								// access Node class functions
	ofstream o; 							// output file handle
	time_t t1;


	o.open("output.txt", ofstream::app);

	
	//while (sizeFlag)						// initial idea was to run consecutively in a loop, however this never worked, we did iterations with different sizes
	//{
	o << "ITERATION " << size << endl;
	srand(time(NULL));						// initialize random seed
	for (int i = 0; i < numNodes; i++)
	{
		g.CreateNode(i);					// create the nodes for the graph
	}
	g.SetEdges(numNodes);					// set the edges for the nodes using the number of nodes
	g.Display(o);							// display the current graph in the output text file

	BruteForce(&n, g, size, o);				// call function that determines brute force method of deriving an answer
	ApproximateDom(g, o);					// call function that determines aproximate method for minimum dominating set


	//size = size + 1;						// as previously mentioned, we wanted to do a loop, however it never worked correctly
	//}
	o.close();
	system("pause");
	return 0;
}


void BruteForce(struct Node* n, Graph g, int size, ofstream& o)
{
	int minSETOLD = size;					//creates a minimum dominating set of all the nodes, initializes with assumption of disjointed graph
	int minSET;								
	int minROW;								// keeps track of nodes in the iteration that consist of dominating set
	int i;
	time_t t2, t3;							// initializes time variables

	time(&t2);								// gets initial time for start of iteration
	long rows = 0.0;						// initializes a variable for the for loop that drives the iteration
	int domFLAG;							// used as boolean for determining if current iteration is a dominating set
	rows = (long)(pow(2, size));			// determines number of loops to run based on all combinations
	int BestBF[50];							// keeps the current best case senario for dominating set
	
	//MAIN LOOP
	for (i = 0; i <= rows - 1; i++)
	{
		int BF[50] = { 0 };					// initialize the current iteration to all 0's
		int j = size - 1;					// accounts for size in main starts at 1 index, this sets array column to 0 index
		int num = i;						// moves the current loop count into a variable for binary conversion
		while (num > 0)						// converts number to binary, and sets as the intial values in the array
		{
			BF[j] = num % 2;
			num = num / 2;
			j--;
		}
		for (j = 0; j < size; j++)									// getting adjacencies for given point
		{
			if (BF[j] == 1)											// if the current array slot is a member of the dominating set
			{
				int curEDGE = g.GetSize(size - (j + 1));			// gets the number of connections the node contains
				for (int m = 0; m < curEDGE; m++)					// cycles through the nodes based on how many connections it has
				{
					if (BF[g.GetEdges(size - (j + 1), m)] != 1)		// if an adjacent node is not a 1, it makes it a 2 as it is dominated
					{
						BF[g.GetEdges(size - (j + 1), m)] = 2;
						
					}
				}
			}
		}
		domFLAG = 1;												// asssumes iteration is a dominating set..
		for (j = 0; j < size; j++)									// loops through current iteration to check if it is a dominating set
		{	
			if (BF[j] == 0)											// if array contains a 0, it is not a dominating set, flips flag
			{
				domFLAG = 0;
			}
		}
		if (domFLAG == 1)											// if it is a dominating set
		{
			minSET = 0;
			for (int j = 0; j <= size; j++)							// loops through array to 
			{
				if (BF[j] == 1)										// if the node is in the dominating set, increment the node count for the line
				{
					minSET++;
				}
			}
			if (minSETOLD > minSET)									// if new dominating set is less nodes than previous version, replace old version
			{
				minSETOLD = minSET;
				minROW = i;
				for (int j = 0; j < size; j++)
				{
					BestBF[j] = BF[j];
				}
			}
		}	
	}
	o << "Minimum Dominating Set using Brute Force: { ";			// writing results to file
	for (int j = 0; j < size; j++)
	{
		if (BestBF[j] == 1)
		{
			o << j << ", ";
		}
	}
	o << "}"<<endl;
	time(&t3);									// getting end time
	double t = difftime(t3, t2);				//gets current time and gets difference from first time to now
	o << "It took " << setprecision(5) << t << " seconds for that iteration" << endl;	

	cout << "It took " << std::setprecision(10) << t << " seconds for that iteration" << endl;	//cout to let user know completed test on console
}
