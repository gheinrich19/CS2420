#ifndef NODE_H
#define NODE_H

#include "Board.h"

class Node{
public:
	Node(Board b, Node* n=NULL){
		data = b;
		next = n;
	}

	Node* next;
	Board data;
};

#endif
