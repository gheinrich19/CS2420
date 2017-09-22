// SliderProject.cpp : Defines the entry point for the console application.

#include "Game.h"   // game class
#include <time.h>

const int SIZE = 3;       // Dimension of board
int main()
{
	srand((int)time(NULL));
	char response;
	Game g;
	int game0[SIZE*SIZE] = { 1, 2, 3, 7, 4, 0, 6, 5, 8 };     // given puzzle
	g.playGiven("Test 1", game0);                   // play game with given input
	cout << "\nClick any key to continue\n";
	cin >> response;
	cout << endl;

	const int JUMBLECT = 5;           // how much jumbling to do in random board
	g.playRandom("Test 2", JUMBLECT);      // play game with random jumbling
	cout << "\nClick any key to continue\n";
	cin >> response;
	cout << "\nEnd of Tests\n";
	return 0;
}

