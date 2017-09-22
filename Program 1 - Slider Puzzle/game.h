#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "queue.h"

class Game {
public:
	Game();
	void playGiven(string title, int game[]);          // play game with a given board
	void playRandom(string title, int jumbleCT);       // play game with a randomly jumbled board
	bool solvePuzzle(Board &b);          // solve the puzzle
	Queue boards;         // possible board to solution
	Queue history;        // history queue to keep track of all considered possiblities
	Board solved;         // winning board

private:
	Board puzzle;        // board to be solved
	Board orig;          // copy of original board
	string str;          // string to hold the number of moves used
};

#endif