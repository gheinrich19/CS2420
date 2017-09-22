#ifndef NODE_H
#define NODE_H

class Node{
public:
	Node(){
		parent = 0;
		size = 0;
		lowRow = 1000;
		highRow = -1;
	}

	int parent = 0;
	int size = 0;
	int lowRow = 1000;               // for percolation
	int highRow = -1;                // for percolation
	bool status = false;             // for percolation

private:
};

#endif