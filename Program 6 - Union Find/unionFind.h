#ifndef UNIONFIND_H
#define UNIONFIND_H

#include <iostream>
#include <vector>
#include <iomanip>
#include "node.h"

using namespace std;

class UnionFind
{
	public:
		vector<Node*> s;
		UnionFind(){}   //default constructor
		UnionFind(int numElements)        //constructor with initial number of elements
		{
			for (int i = 0; i < numElements; i++){
				n = new Node();
				n->parent = i;
				n->size = 1;
				s.push_back(n);
			}
		}

		int find(int x){              // find (path compression)
			if (x >= s.size() || x < 0)       // check element is valid
				return -1;
			if (s[x]->parent == x)
				return x;
			else
				return s[x]->parent = find(s[x]->parent);
		}

		void unionSet(int root1, int root2){                      // union by size
			if (root1 >= s.size() || root2 >= s.size() || root1 < 0 || root2 < 0)              // check element is valid
				return;
			root1 = find(root1);
			root2 = find(root2);
			if (s[root2]->size >= s[root1]->size) {                       // root2 is deeper
				s[root1]->parent = root2;                             // Make root2 new root
				s[root2]->size += s[root1]->size;
				if (s[root1]->lowRow < s[root2]->lowRow){
					s[root2]->lowRow = s[root1]->lowRow;
				}
				if (s[root1]->highRow > s[root2]->highRow){
					s[root2]->highRow = s[root1]->highRow;
				}
			}
			else{
				s[root2]->parent = root1;                             // Make root1 new root
				s[root1]->size += s[root2]->size;
				if (s[root2]->lowRow < s[root1]->lowRow){
					s[root1]->lowRow = s[root2]->lowRow;
				}
				if (s[root2]->highRow > s[root1]->highRow){
					s[root1]->highRow = s[root2]->highRow;
				}
			}
		}

		void print(){                           // print elements, with parents size of parents
			for (unsigned int i = 0; i < s.size(); i++){
				cout << right << setw(2) << i << "| " << s[i]->parent << "		";
				if (s[i]->parent != i)
					cout << " " << endl;
				else
					cout << s[i]->size << endl;
			}
		}
		
	private:
		Node* n;
};

#endif