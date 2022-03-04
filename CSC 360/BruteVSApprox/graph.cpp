#include "graph.h"
#include <iostream>
#include <string>
#include <fstream>
#include <assert.h> 
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <ctime>


using namespace std;


/*==================
	Constructor
==================*/
Graph::Graph()
{
	edges = 0;		// initialize edges to 0
	vertices = 0;	// initialize vertices to 0
	temp = 0;		// for adding new nodes
	head = 0;

}

//Copy Constructor
Graph::Graph(const Graph& toDuplicate) {
	if (toDuplicate.vertices > 0) {
		Node* nodePtrNew;
		Node* nodePtrToDup;
		Node* tempPtr;

		//initialize values for Graph object
		edges = toDuplicate.edges;
		vertices = toDuplicate.vertices;

		nodePtrToDup = toDuplicate.head;  //sets start point

		nodePtrNew = new Node;  //initilization node for graph
		head = nodePtrNew;  //assigns the address of the first node to the head of the graph
		temp = head;  //sets temp to head of graph
		nodePtrNew->next = 0; //sets to null

		//iterate through nodes of graph while next node is not null
		while (nodePtrToDup) {
			nodePtrNew->edges = nodePtrToDup->edges; //copies edge number of node
			nodePtrNew->numEdges = nodePtrToDup->numEdges; //copies edge number of node
			nodePtrNew->size = nodePtrToDup->size; //copies size of node
			nodePtrNew->nodeNum = nodePtrToDup->nodeNum;  //copies nodeNum of node

			//copy the adjacency matrix
			for (int j = 0; j < nodePtrToDup->size; j++) {
				nodePtrNew->connections[j] = nodePtrToDup->connections[j];  //copies nodes connected to
			}

			//Sets next node in linked list
			//if another node in original, then create new node
			if (nodePtrToDup->next) {
				tempPtr = new Node;  //new node for graph
				nodePtrNew->next = tempPtr;  //links to next node
				nodePtrNew = tempPtr;  //jumps to next new node
			}
			else {
				nodePtrNew->next = 0;
			}
			nodePtrToDup = nodePtrToDup->next;  //move to next node in graph

		}
	}
	else {
		//empty graph, set values
		edges = 0;		// initialize edges to 0
		vertices = 0;	// initialize vertices to 0
		temp = 0;		// for adding new nodes
		head = 0;
	}
}

/*==================
	Destructor
==================*/
Graph::~Graph()
{
	temp = head;
	while (head != 0)
	{
		temp = head->next;
		delete(head);
		head = temp;
	}
}

/* STILL TROUBLESHOOTING THIS
 *
 * Having trouble checking the 'temp -> connections' with string 's'. It won't assign connections that should otherwise be assigned
 * because they are good values. The else statement is in place for testing purposes only and will be removed after the if statement is
 * corrected. The number of edges assigned is working correctly. String copying seems to be working as well, but it won't assign the next
 * connection and otherwise moves to the next node.
 * */
void Graph::SetEdges(int n)
{
	const int edgeMaxSize = n - 1;    // attached to all nodes
	const int edgeMinSize = 0;    // attached to no nodes
	int connNum = 0; // for assigning connections
	bool addIt = true;
	srand(time(NULL)); // initialize random seed using time

	temp = head;    // set temp to head

	for (int i = 0; i < n; i++)    // for loop to run through and set edge sizes and connections
	{
		long int random = (rand() % (edgeMaxSize - temp->size-2)); // randomize number of edges based off edge density
		temp->numEdges = random;    // set the num of edges for the node and store in var
		while (random != 0)    // add connections to that node until they are all assigned
		{
			connNum = rand() % n;    // assign randomly using the max size

			for (int k = 0; k < temp->size; k++)
			{
				if (connNum == temp->connections[k])
				{
					addIt = false;
				}
			}
			if (addIt)
			{
				if (connNum != temp->nodeNum)
				{
					temp->connections[temp->size] = connNum;    // add the connection number to the adjacency list
					temp->size += 1;    // +1 to connection size
					Node* curNode = temp;
					int nodeNum = temp->nodeNum;
					temp = head;
					for (int l = 0; l < n - connNum - 1; l++)
					{
						temp = temp->next;
					}
					temp->connections[temp->size] = nodeNum;;    // add the connection number to the adjacency list
					temp->size += 1;    // +1 to connection size
					temp = curNode;
					random--;
				}
			}
			addIt = true; // reset the flag
		}
		temp = temp->next;    // move to the next node
	}
	//sets the number of vertices for the graph
	vertices = n;
}

void Graph::CreateNode(int _nodeNum)
{
	temp = new Node;			// create a new node at temp
	temp->nodeNum = _nodeNum;	// set the node number
	temp->next = head;		// add node to head (i.e. 5-4-3-2-1-0)
	head = temp;
}

void Graph::Display(std::ofstream& o)	// for testing purposes : prints the node number and the number of edges, whos edge they are connected to.
{
	o << "     Node #\t#size\t\tAdj. List" << endl;
	o << "---------------------------------------------" << endl;
	temp = head;
	while (temp != 0)
	{
		o << "     Node[" << temp->nodeNum << "]\t  " << temp->size << "\t\t";
		for (int l = 0; l < temp->size; l++)
		{
			o << temp->connections[l];
			if (l != temp->size - 1)
				o << "-";
		}
		o << endl;
		temp = temp->next;
	}
	o << endl;
}


int Graph::GetEdges(int nodenum, int edgenum)
{
	temp = head;
	for (int i = 0; i < nodenum; i++)
	{
		if (temp->next != NULL)
		{
			temp = temp->next;
		}
	}
	int retedge = temp->connections[edgenum];
	return retedge;
}

int Graph::GetSize(int dest)
{
	temp = head;											// sets temp to head, to move through the graph
	for (int i = 0; i < dest; i++)							// loops through nodes to desired node
	{
		if (temp->next != NULL)
		{
			temp = temp->next;
		}
	}
	int tempa;
	tempa = temp->size;										// pulls the size (Number of connections) from the node
	return tempa;											// retuns number of connections			
}

void Graph::setFileName(string fn)
{
	filename = fn;
}

void Graph::GenerateStatic()									// generates static graph, used for working on approximation prior to successful random graph
{
	//generate a static graph-- TESTING

	//creates seven nodes for the graph
	for (int i = 8; i >= 0; i--) {
		CreateNode(i);
		//cout << "i:"<< i << endl;
	}

	//manually specify connections for static graph
	//Node* tempPtr;

	//Node 0
	temp = head;
	temp->numEdges = 1;
	temp->size = 1;
	temp->connections[0] = 2;

	//Node 1
	temp = temp->next;
	temp->numEdges = 1;
	temp->size = 1;
	temp->connections[0] = 2;

	//Node 2
	temp = temp->next;
	temp->numEdges = 3;
	temp->size = 3;
	temp->connections[0] = 0;
	temp->connections[1] = 1;
	temp->connections[2] = 3;

	//Node 3
	temp = temp->next;
	temp->numEdges = 4;
	temp->size = 4;
	temp->connections[0] = 2;
	temp->connections[1] = 4;
	temp->connections[2] = 5;
	temp->connections[3] = 8;

	//Node 4
	temp = temp->next;
	temp->numEdges = 2;
	temp->size = 2;
	temp->connections[0] = 3;
	temp->connections[1] = 8;

	//Node 5
	temp = temp->next;
	temp->numEdges = 2;
	temp->size = 2;
	temp->connections[0] = 3;
	temp->connections[1] = 7;

	//Node 6
	temp = temp->next;
	temp->numEdges = 1;
	temp->size = 1;
	temp->connections[0] = 7;

	//Node 7
	temp = temp->next;
	temp->numEdges = 2;
	temp->size = 2;
	temp->connections[0] = 5;
	temp->connections[1] = 6;

	//Node 8
	temp = temp->next;
	temp->numEdges = 2;
	temp->size = 2;
	temp->connections[0] = 3;
	temp->connections[1] = 4;

	vertices = 9;
	edges = 9;

}

//Description: Takes in a graph, copies that graph, then uses a greedy approach to approximate the minimum dominating set
//Parameters: Graph to work with 
//Returns:
void ApproximateDom(const Graph& originalGraph, std::ofstream& o) {
	Graph g(originalGraph);  //copies the passed graph
	int numElements = 0;
	int mostEdges = 0;  //holds most edges
	int largestNodeNum = -1;  //holds most edges
	int tempVertices = 0; //temp hold so not changing graph values
	int rowValues[MAX_VERTICES] = { 0 };  //Creates a static array of size MAX_VERTICES to hold row info for each cycle
	int dominatingSet[MAX_VERTICES] = { 0 };  //Will hold the final dominating set
	int trueSize = g.vertices;  //will track number of vertices (AKA columns in the array being used)
	int rowCount = 0;
	int edgelessNodes = 0;
	time_t t2, t3;
	time(&t2); //gets time prior to starting

	//correction for numEdges property 
	g.temp = g.head;
	while (g.temp) {
		g.temp->numEdges = g.temp->size;
		g.temp = g.temp->next;
	}

	//Place x for all nodes that have 0 edges
	//find largest # of edges for node
	//label "1" as current node, 2's for adj nodes, 0 for non-adj nodes
	//Remove "1" node from adj list of "2's", update edge count
	//Add "1" to dominating set, set edges of "1" to 0
	//Check w/in the "2's" if they are adjacent to any other 2's. Remove the corresponding adjacent "2s" from the adjacency lists of those adjancet nodes appropriately, update edge count
	//whenever there is a node that reaches 0 edges, we subtract one vertice from the graph

	//remove any nodes that are disjointed
	g.temp = g.head;
	while (g.temp) {
		if (g.temp->numEdges == 0) {
			dominatingSet[g.temp->nodeNum] = 1;
		}
		g.temp = g.temp->next;  //move to next node
	}

	while (g.vertices > 0) {
		//resets values for new cycle
		mostEdges = 0;
		largestNodeNum = -1;
		tempVertices = 0;
		g.temp = g.head;

		//find node with most edges, if not found mostEdges will remain at 0 (DONE)
		while (g.temp) {
			if (mostEdges < g.temp->numEdges) {
				mostEdges = g.temp->numEdges;  //updates mostEdges to current Max
				largestNodeNum = g.temp->nodeNum;  //updates node that contains the most edges
			}
			g.temp = g.temp->next;  //move to next node
		}
		g.temp = g.head;  //reset temp to start 
		//at least one node left--> MAY not need this check
		if (largestNodeNum != -1) {
			rowValues[largestNodeNum] = 1;  //assign primary node for this cycle
			//find adjacent nodes
			while (g.temp) {

				//update edges and adjacency list for the primary node
				if (g.temp->nodeNum == largestNodeNum) {
					dominatingSet[g.temp->nodeNum] = 1;  //marks node in dominating set
					g.temp->numEdges = 0;  //prevents from being reselected

					for (int i = 0; i < g.temp->size; i++) {
						g.temp->connections[i] = -1;  //replaces all edges with -1 to prevent future use
					}
				}
				//iterate through adjacency list for a given node
				for (int i = 0; i < g.temp->size; i++) {
					//is current node connected to the primary node ("1")
					if (g.temp->connections[i] == largestNodeNum) {
						rowValues[g.temp->nodeNum] = 2; //assigns "2" to adjacent node
						g.temp->connections[i] = -1;  //indicates edge has been used already
						g.temp->numEdges--;  //update edge count
					}

				}
				g.temp = g.temp->next;  //move to next node
			}
			//Removes the edges from nodes that are adjacent to the primary node ("1") and to each other ("2")
			//Iterate through the rowArray to check for 2's
			for (int nodeIdOuter = 0; nodeIdOuter < trueSize; nodeIdOuter++) {
				g.temp = g.head; //reset temp to head for each iteration
				//if rowValue is adjacent, 
				if (rowValues[nodeIdOuter] == 2) {
					//iterate through the nodes for the node that was marked as a '2'
					while (g.temp) {
						//find node that corresponds to the current '2'
						if (g.temp->nodeNum == nodeIdOuter) {
							//iterate through the adjacency list of the current node marked as '2'
							for (int adjIndex = 0; adjIndex < g.temp->size; adjIndex++) {
								for (int nodeIdInner = 0; nodeIdInner < trueSize; nodeIdInner++) {
									//if rowValue is marked as a '2' and contained within adjancency list of current node, then remove
									if (rowValues[nodeIdInner] == 2 && g.temp->connections[adjIndex] == nodeIdInner) {
										g.temp->connections[adjIndex] = -1; //rmv node from adjacency list of current node
										g.temp->numEdges--; //since removing node from list, subtract one edge
									}
								}
							}
						}

						g.temp = g.temp->next;  //move to next node
					}
				}
			}
			rowCount++;
			//Shows nodes that were completed this round
			while (g.temp) {
				if (g.temp->numEdges <= 0) {
					rowValues[g.temp->nodeNum] = -1;

				}
				g.temp = g.temp->next;
			} 
			//clear the nodes to 0 that were not used
			for (int i = 0; i < MAX_VERTICES; i++) {
				if (rowValues[i] != -1) {
					rowValues[i] = 0;
				}
			}

		}
		//count how many nodes have zero edges left to check
		g.temp = g.head;
		while (g.temp) {
			if (g.temp->numEdges <= 0) {
				tempVertices++;  //increment for a blank vertice
			}
			g.temp = g.temp->next;
		}
		//if all nodes have no edges left to check, end loop
		if (tempVertices == g.vertices) {
			g.vertices = 0;  //all vertices edges have been exhausted, end loop
		}

	}
	//Print dominating 
	//gets number of elements that are in the set to print correctly
	for (int i = 0; i < trueSize; i++) {
		if (dominatingSet[i] == 1) {
			numElements++;
		}
	}

	o << "\nMinimum Dominating Set Using Greedy Approximation:{";
	for (int i = 0; i < trueSize; i++) {
		if (dominatingSet[i] == 1) {
			if (numElements == 1) {
				//print for last element in set
				o << i << "}\n";
			}
			else {
				//print for non-last elements
				o << i << ",";
				numElements--;
			}
		}
	}

	time_t t = difftime(time(&t3), t2);				//gets current time and gets difference from first time to now
	o << "totalTime: " << t << "\n\n\n\n";
	//print the dominating set

}



/*
 *
 * 			cout << "Node Number: " << temp -> nodeNum << endl;
			cout << "# of Connections: " << random << endl;
 * 			cout << "Connection Number: " << connNum << "   ";
				cout << "Size of: " << sizeof(temp -> connections) << " ";
				cout << "adjList: " << temp -> connections[k] << " \n";
 *
 */

