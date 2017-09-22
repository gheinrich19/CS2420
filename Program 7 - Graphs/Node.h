#ifndef NODE_H
#define NODE_H

#include "graph.h"

class Node{
public:
	Node(EdgeNode g, Node* n = NULL){
		data = g;
		next = n;
	}

	Node* next;
	EdgeNode data;
};

#endif