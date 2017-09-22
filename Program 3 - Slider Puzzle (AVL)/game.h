#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "queue.h"

class Game {
public:
	Game();
	string playGiven(string title, int game[]);          // play game with a given board
	string playRandom(string title, int jumbleCT);       // play game with a randomly jumbled board
	void solvePuzzle(Board &b);          // solve the puzzle
	Queue boards;         // possible board to solution
	Queue history;        // history queue to keep track of all considered possiblities
	Board solved;         // winning board

private:
	Board puzzle;        // board to be solved
	Board orig;          // copy of original board
	string str;          // string to hold the number of moves used
};

#endif