#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <assert.h>
#include <stdlib.h>
#include <ctime>

#define MAX_VERTICES 35 


struct Node
{
	long int numEdges;
	int edges;
	const static size_t SIZE = 35;
	int connections[SIZE] = { 0 };
	int size = 0;
	int nodeNum;
	struct Node* next;
};

class Graph
{
public:
	Graph();
	Graph(const Graph& toDuplicate);
	~Graph();
	void SetEdges(int n);	// randomize the node edge, 35%
	int GetEdges(int nodenum, int edgenum);
	int GetSize(int dest);
	void CreateNode(int nodeNum);
	void Display(std::ofstream& o);
	void setFileName(std::string fn);
	friend void ApproximateDom(const Graph& originalGraph, std::ofstream& o);
	void GenerateStatic();


private:
	int edges;
	int vertices;
	std::string filename;
	Node* temp;
	Node* head;
};

#endif /* GRAPH_H_ */


