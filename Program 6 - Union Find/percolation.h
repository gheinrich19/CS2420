#ifndef PERCOLATION_H
#define PERCOLATION_H
#include "unionFind.h"

const int N = 20;

class Percolation{
public:
	Percolation(){
		u = new UnionFind(N*N);                      //make Union Find with N*N elements
	}

	void percolate(){
		int count = 0;
		while (true){
			i = random();                                  // give random site to open
			while (u->s[i]->status == true){                    // make sure given site is not already opened
				i = random();
			}
			u->s[i]->status = true;                           // open given site
			++count;
			int left, right, up, down;
			int x = i / N;
			int y = i%N;
			//cout << count << " x = " << x << " y = " << y << endl;
			if (x > 0 && x < N - 1 && y > 0 && y < N - 1){                         // union newly opened site and its open neighbors
				left = i - 1;
				right = i + 1;
				up = i - N;
				down = i + N;
				if (u->s[left]->status == true){
					u->unionSet(i, left);
					setRows(i);
				}
				if (u->s[right]->status == true){
					u->unionSet(i, right);
					setRows(i);
				}
				if (u->s[up]->status == true){
					u->unionSet(i, up);
					setRows(i);
				}
				if (u->s[down]->status == true){
					u->unionSet(i, down);
					setRows(i);
				}
			}
			else if (x == 0 && y == 0){                              // edge case
				right = i + 1;
				down = i + N;
				if (u->s[right]->status == true){
					u->unionSet(i, right);
					setRows(i);
				}
				if (u->s[down]->status == true){
					u->unionSet(i, down);
					setRows(i);
				}
			}
			else if (x == 0 && y == N - 1){                              // edge case
				left = i - 1;
				down = i + N;
				if (u->s[left]->status == true){
					u->unionSet(i, left);
					setRows(i);
				}
				if (u->s[down]->status == true){
					u->unionSet(i, down);
					setRows(i);
				}
			}
			else if (x == N - 1 && y == 0){                              // edge case
				right = i + 1;
				up = i - N;
				if (u->s[right]->status == true){
					u->unionSet(i, right);
					setRows(i);
				}
				if (u->s[up]->status == true){
					u->unionSet(i, up);
					setRows(i);
				}
			}
			else if (x == N - 1 && y == N - 1){                              // edge case
				left = i - 1;
				up = i - N;
				if (u->s[left]->status == true){
					u->unionSet(i, left);
					setRows(i);
				}
				if (u->s[up]->status == true){
					u->unionSet(i, up);
					setRows(i);
				}
			}
			else if (x > 0 && y == 0){                              // edge case
				right = i + 1;
				up = i - N;
				down = i + N;
				if (u->s[right]->status == true){
					u->unionSet(i, right);
					setRows(i);
				}
				if (u->s[up]->status == true){
					u->unionSet(i, up);
					setRows(i);
				}
				if (u->s[down]->status == true){
					u->unionSet(i, down);
					setRows(i);
				}
			}
			else if (x > 0 && y == N - 1){                              // edge case
				left = i - 1;
				up = i - N;
				down = i + N;
				if (u->s[left]->status == true){
					u->unionSet(i, left);
					setRows(i);
				}
				if (u->s[up]->status == true){
					u->unionSet(i, up);
					setRows(i);
				}
				if (u->s[down]->status == true){
					u->unionSet(i, down);
					setRows(i);
				}
			}
			else if (x == 0 && y > 0){                              // edge case
				left = i - 1;
				right = i + 1;
				down = i + N;
				if (u->s[left]->status == true){
					u->unionSet(i, left);
					setRows(i);
				}
				if (u->s[right]->status == true){
					u->unionSet(i, right);
					setRows(i);
				}
				if (u->s[down]->status == true){
					u->unionSet(i, down);
					setRows(i);
				}
			}
			else if (x == N - 1 && y > 0){                              // edge case
				left = i - 1;
				right = i + 1;
				up = i - N;
				if (u->s[left]->status == true){
					u->unionSet(i, left);
					setRows(i);
				}
				if (u->s[right]->status == true){
					u->unionSet(i, right);
					setRows(i);
				}
				if (u->s[up]->status == true){
					u->unionSet(i, up);
					setRows(i);
				}
			}
			if (checkPercolate(i) == true)             // if grid has percolated break from loop
				break;
			if (count % 50 == 0){                         // print grid after opening every 50 sites
				cout << "Count: " << count << endl;
				print();
				cout << endl;
			}
		}
		cout << "Final Grid (Count - " << count << "):\n";
		print();                           // print final grid
		cout << "Percolation Treshold = " << (float)count / (N*N) << endl;          // percolation treshold
	}

	int random(){                     // random site generator
		int x, y;
		x = rand() % N;
		y = rand() % N;
		i = N*x + y;
		return i;
	}

	bool checkPercolate(int n){                   // check if grid has percolated
		n = u->find(n);
		if (u->s[n]->lowRow == 0 && u->s[n]->highRow == N - 1)
			return true;
		else
			return false;
	}

	void setRows(int n){              //update and check lowRow and highRow
		int x, y;
		x = n / N;
		y = n % N;
		n = u->find(n);
		if (x < u->s[n]->lowRow){
			u->s[n]->lowRow = x;
		}
		else if (x > u->s[n]->highRow){
			u->s[n]->highRow = x;
		}
	}

	void print(){                 // print grid: " " is open site, "X" is closed site
		int n = -1;
		cout << " ";
		for (int x = 0; x < N; x++){
			cout << "_";
		}
		cout << endl;
		for (int x = 0; x < N; x++){
			cout << "|";
			for (int y = 0; y < N; y++){
				n = N*x + y;
				if (u->s[n]->status == true){
					cout << " ";
				}
				else{
					cout << "X";
				}
			}
			cout << "|" << endl;
		}
		cout << " ";
		for (int x = 0; x < N; x++){
			cout << "_";
		}
		cout << endl;
	}

private:
	UnionFind* u;
	int i = -1;
};

#endif