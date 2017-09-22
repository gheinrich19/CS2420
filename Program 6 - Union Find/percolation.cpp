#include "percolation.h"

int main(){
	cout << "------------------------------------------------------------" << endl;
	cout << "PART 1 - UNION FIND TEST\n";
	cout << "------------------------------------------------------------" << endl;
	UnionFind u(30);
	cout << "Print Initial Elements:\n\n";
	u.print();
	cout << "------------------------------------------------------------" << endl;
	cout << "Union(2, 3)\n";
	cout << "Union(6, 9)\n";
	cout << "Union(3, 9)\n";
	cout << "Union(4, 2)\n";
	cout << "Union(3, 23)\n";
	cout << "Union(14, 7)\n";
	cout << "Union(13, 16)\n";
	cout << "Union(17, 19)\n";
	cout << "Union(24, 29)\n";
	cout << "Union(7, 29)\n";
	u.unionSet(2, 3);
	u.unionSet(6, 9);
	u.unionSet(3, 9);
	u.unionSet(4, 2);
	u.unionSet(3, 23);
	u.unionSet(14, 7);
	u.unionSet(13, 16);
	u.unionSet(17, 19);
	u.unionSet(24, 29);
	u.unionSet(7, 29);
	cout << "\nPrint Elements (Parents and Sizes):\n\n";
	u.print();
	cout << "------------------------------------------------------------" << endl;
	cout << "\nFind(3) = " << u.find(3) << endl;
	cout << "Find(23) = " << u.find(23) << endl;
	cout << "Find(9) = " << u.find(9) << endl;
	cout << "Find(3) = Find(23) = Find(9) = " << u.find(9) << endl;
	cout << "Find(14) = " << u.find(14) << endl;
	cout << "Find(7) = " << u.find(7) << endl;
	cout << "Find(29) = " << u.find(29) << endl;
	cout << "Find(14) = Find(7) = Find(29) = " << u.find(29) << endl;
	cout << "\nEND OF TEST\n\n";

	cout << "------------------------------------------------------------" << endl;
	cout << "PART 2 - PERCOLATION (20x20 grid)\n";
	cout << "------------------------------------------------------------" << endl;
	Percolation p;
	cout << "Print Grid After Opening 50 Sites\n\n";
	p.percolate();
	return 0;
}

