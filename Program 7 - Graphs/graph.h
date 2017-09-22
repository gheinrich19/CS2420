#ifndef GRAPH_H
#define GRAPH_H

#include "edgeNode.h"
#include "queue.h"
#include <fstream>

class GraphNode{
public:
	int nodeID;       // ID of node; something that makes it easy to find the node in the array 
	string name;    //Node name 
	vector<EdgeNode> pred;  // predacency list (vector)
	vector<EdgeNode> succ;  // successor list (vector)
	bool visited;   // true if visited already 
	vector<int> path;               // recored path for shortest path
	GraphNode(int id = -1, string nameEle = " ") :
		nodeID(id), name(nameEle) {
		visited = false;
	}

	void bubbleSort(vector<EdgeNode>& vec, int n) {               //sort nodes in pred and succ lists
		bool swapped = true;
		int j = 0;
		EdgeNode tmp;
		while (swapped) {
			swapped = false;
			j++;
			for (int i = 0; i < n - j; i++) {
				if (vec[i].node > vec[i + 1].node) {
					tmp = vec[i];
					vec[i] = vec[i + 1];
					vec[i + 1] = tmp;
					swapped = true;
				}
			}
		}
	}

private:

}; // GraphNode


class Graph{
protected:
	GraphNode *G;  // Array of nodes of graph – will be given space once the size is known 
	int nodeCt;    // Size of G 
	void sort(){                       // sort the predecessors and succesors
		for (int i = 0; i < nodeCt; i++){
			G[i].bubbleSort(G[i].pred, G[i].pred.size());
			G[i].bubbleSort(G[i].succ, G[i].succ.size());
		}
	}
	void reset(){                             // reset graph after completed operation
		for (int i = 0; i < nodeCt; i++){
			G[i].visited = false;
			G[i].path.clear();
		}
	}

public:
	Graph(int size){
		G = new GraphNode[size];
		for (int i = 0; i < size; i++){
			G[i].nodeID = i;
		}
		nodeCt = size;
	};  // create node array 

	//string toString(string label, ostream & fout);

	void BuildGraph(ifstream& fin){         // build graph from given file
		EdgeNode node;
		int edges;
		EdgeNode s;
		fin >> edges;
		while (!fin.eof()){
			fin >> node.node >> s.node;
			G[node.node].pred.push_back(s);
			G[s.node].succ.push_back(node);
		}
		sort();                     // sort nodes
	}

	void findShortestPath(int Node1, int Node2){                     // shortest path
		Queue q;                                              // queue to store nodes yet to be visited
		G[Node1].visited = true;
		int prev = Node1;
		G[prev].path.push_back(Node1);                        // add first node to path

		for (unsigned int i = 0; i < G[Node1].pred.size(); i++){                  // add all preds and succs to queue
			int n = G[Node1].pred[i].node;
			G[n].path = G[prev].path;
			G[n].path.push_back(n);
			q.add(G[Node1].pred[i]);
			G[G[Node1].pred[i].node].visited = true;
		}
		for (unsigned int i = 0; i < G[Node1].succ.size(); i++){
			int n = G[Node1].succ[i].node;
			G[n].path = G[prev].path;
			G[n].path.push_back(n);
			q.add(G[Node1].succ[i]);
			G[G[Node1].succ[i].node].visited = true;
		}

		EdgeNode e = q.remove();                         // remove from queue and add to path
		while (e.node != Node2){                              // continue process until you get to end node
			prev = e.node;                                          // process described in readme.txt
			for (unsigned int i = 0; i < G[e.node].pred.size(); i++){
				int n = G[e.node].pred[i].node;
				if (G[n].visited == false){
					G[n].path = G[prev].path;
					G[n].path.push_back(n);
					q.add(G[e.node].pred[i]);
					G[n].visited = true;
				}
			}
			for (unsigned int i = 0; i < G[e.node].succ.size(); i++){
				int n = G[e.node].succ[i].node;
				if (G[n].visited == false){
					G[n].path = G[prev].path;
					G[n].path.push_back(n);
					q.add(G[e.node].succ[i]);
					G[n].visited = true;
				}
			}

			e = q.remove();
		}
		int x = G[e.node].path.size();
		cout << "Shortest Ancestral Path: " << G[e.node].path[0];                  // print solution
		for (int i = 1; i < x; i++){
			cout << "-" << G[e.node].path[i];
		}
		cout << endl;
		cout << "Associated Length: " << x - 1 << endl;
		findCommonAncestor(Node1, Node2);
		q.empty();
		reset();
	}

	void findCommonAncestor(int node1, int node2){                           // look at nodes in shortest path and try to find common ancestor
		for (unsigned int i = 0; i < G[node2].path.size(); i++){
			int ind = G[node2].path[i];
			if (G[ind].pred.size() == 0){                                          // if  there are no pred's automatic common ancestor
				cout << "Shortest Common Ancestor: " << ind << endl;
				return;
			}
			for (unsigned int j = 0; j < G[ind].pred.size(); j++){
				int n = G[node2].path[i + 1];
				if (G[ind].pred[j].node == node2){                             // if a pred is end node
					cout << "The Shortest Common Ancestor is (" << node2 << ") assuming a node is its own ancestor.\n";
					return;
				}
				else if (G[ind].pred[j].node == G[n].nodeID){                    // if a pred is next node in path break from nested loop
					break;
				}
				else if (j == G[ind].pred.size() - 1){                                 // if no pred's in path, current node is common ancestor
					cout << "Shortest Common Ancestor: " << ind << endl;
					return;
				}
			}
		}
	}

	string toString(){                         // print graph, with edges and nodes
		stringstream ss;
		for (int i = 0; i < nodeCt; i++){
			ss << i << ": ";
			for (unsigned int j = 0; j < G[i].pred.size(); j++){
				ss << G[i].pred[j].node << " ";
			}
			ss << endl;
		}
		ss << endl;
		for (int i = 0; i < nodeCt; i++){
			ss << i << ": ";
			for (unsigned int j = 0; j < G[i].succ.size(); j++){
				ss << G[i].succ[j].node << " ";
			}
			ss << endl;
		}
		return ss.str();
	}

	string toString(int num, int startNode){
		stringstream ss;

		return ss.str();
	}
}; // Graph

#endif