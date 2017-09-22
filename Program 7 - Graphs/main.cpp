#include "graph.h"
#include <assert.h>

int main()
{
	ifstream fin;
	int ans;
	string file = " ";
	cout << "Choose Which File You Want to Input:\n";
	cout << "1 - digraph1.txt\n";
	cout << "2 - digraph2.txt\n";
	cout << "3 - digraph3.txt\n";
	cout << "\nFile Choice: ";
	cin >> ans;
	while (file == " "){
		switch (ans)
		{
		case 1:
			file = "digraph1.txt";
			break;
		case 2:
			file = "digraph2.txt";
			break;
		case 3:
			file = "digraph3.txt";
			break;
		default:
			cout << "Please enter 1, 2, or 3: ";
			cin >> ans;
			break;
		}
	}
	fin.open(file);
	int size = 0;
	//int edges = 0;
	fin >> size;
	Graph g(size);
	g.BuildGraph(fin);
	int n1, n2;
	char input = ' ';
	while (input != 'N'){
		cout << "\nEnter two nodes to find ancestral path:\n";
		cout << "Node 1: ";
		cin >> n1;
		cout << "Node 2: ";
		cin >> n2;
		cout << endl;
		g.findShortestPath(n1, n2);
		cout << "Continue? (Enter Y for yes and N for no): ";
		cin >> input;
		input = toupper(input);
	}
	fin.close();
	return 0;
}