#include "SliderGame.h"
#include <time.h>

const int SIZE = 3;

int main(){
	clock_t t1, t2, t3, t4, t5, t6, t7, t8, t9;
	float diff, seconds;
	ofstream fout;
	fout.open("SliderPuzzle Output.txt");

	/*•	Add: 1 3 5 7 9 11 2 4 8  (now print tree)
•	Remove 7 9(now print tree) 
•	Add 50 30 15 18 (now print tree)
•	Remove Min (now print tree)
•	Remove Min (now print tree)
•	Remove Min (now print tree)
•	Add 17(now print tree)
*/
	fout << "-----------------------Avl Tree Test: Integers-----------------------\n" << endl;
	AvlTree<int> tree;
	fout << "Add: 1, 3, 5, 7, 9, 11, 2, 4, 8" << endl;
	tree.insert(1);
	tree.insert(3);
	tree.insert(5);
	tree.insert(7);
	tree.insert(9);
	tree.insert(11);
	tree.insert(2);
	tree.insert(4);
	tree.insert(8);
	fout << "Print Tree:\n";
	fout << tree.toString() << endl;
	fout << "Remove: 7, 9\n";
	tree.remove(7);
	fout << tree.toString() << endl;
	tree.remove(9);
	fout << "Print Tree:\n";
	fout << tree.toString() << endl;
	fout << "Add: 50, 30, 15, 18\n";
	tree.insert(50);
	tree.insert(30);
	tree.insert(15);
	tree.insert(18);
	fout << "Print Tree:\n";
	fout << tree.toString() << endl;
	fout << "Remove Min:\n";
	tree.removeMin();
	fout << "Print Tree:\n";
	fout << tree.toString() << endl;
	fout << "Remove Min:\n";
	tree.removeMin();
	fout << "Print Tree:\n";
	fout << tree.toString() << endl;
	fout << "Remove Min:\n";
	tree.removeMin();
	fout << "Print Tree:\n";
	fout << tree.toString() << endl;
	fout << "Add: 17\n";
	tree.insert(17);
	fout << "Print Tree:\n";
	fout << tree.toString() << endl;

	fout << "-----------------------Slider Game-----------------------\n\n";

	SliderGame g;
	int game0[SIZE*SIZE] = {4, 0, 1, 3, 5, 2, 6, 8, 7};
	int game1[SIZE*SIZE] = { 1, 3, 8, 6, 2, 0, 5, 4, 7 };
	int game2[SIZE*SIZE] = { 1, 3, 2, 4, 5, 6, 8, 7, 0 };
	int game3[SIZE*SIZE] = { 1, 2, 3, 7, 4, 0, 6, 5, 8 };

	t1 = clock();
	fout << g.bruteForceSolve("Game 0", game0);
	t2 = clock();
	diff = ((float)t2 - (float)t1);
	seconds = diff / CLOCKS_PER_SEC;
	fout << "Game 0: Brute Force Method took " << seconds << " seconds solve\n\n\n";
	fout << g.aStarSolve("Game 0", game0);
	t3 = clock();
	diff = ((float)t3 - (float)t2);
	seconds = diff / CLOCKS_PER_SEC;
	fout << "Game 0: A* Method took " << seconds << " seconds solve\n";
	fout << "The A* Method for Game 0 was " << (((float)t2 - (float)t1) / CLOCKS_PER_SEC) - (((float)t3 - (float)t2) / CLOCKS_PER_SEC);
	fout << " seconds faster\n\n\n";

	fout << g.bruteForceSolve("Game 1", game1);
	t4 = clock();
	diff = ((float)t4 - (float)t3);
	seconds = diff / CLOCKS_PER_SEC;
	fout << "Game 1: Brute Force Method took " << seconds << " seconds solve\n\n\n";
	fout << g.aStarSolve("Game 1", game1);
	t5 = clock();
	diff = ((float)t5 - (float)t4);
	seconds = diff / CLOCKS_PER_SEC;
	fout << "Game 1: A* Method took " << seconds << " seconds solve\n\n\n";

	fout << g.bruteForceSolve("Game 2", game2);
	t6 = clock();
	diff = ((float)t6 - (float)t5);
	seconds = diff / CLOCKS_PER_SEC;
	fout << "Game 2: Brute Force Method took " << seconds << " seconds to solve\n\n\n";
	fout << g.aStarSolve("Game 2", game2);
	t7 = clock();
	diff = ((float)t7 - (float)t6);
	seconds = diff / CLOCKS_PER_SEC;
	fout << "Game 2: A* Method took " << seconds << " seconds solve\n\n\n";

	fout << g.bruteForceSolve("Game 3", game3);
	t8 = clock();
	diff = ((float)t8 - (float)t7);
	seconds = diff / CLOCKS_PER_SEC;
	fout << "Game 3: Brute Force Method took " << seconds << " seconds to solve\n\n\n";
	fout << g.aStarSolve("Game 3", game3);
	t9 = clock();
	diff = ((float)t9 - (float)t8);
	seconds = diff / CLOCKS_PER_SEC;
	fout << "Game 3: A* Method took " << seconds << " seconds solve\n\n\n";
	ifstream fin;
	fin.open("SliderPuzzle Output.txt");
	string x;
	while (!fin.eof()) {
		getline(fin, x);
		cout << x << endl;
	}
	fin.close();
	fout.close();
	return 0;
}