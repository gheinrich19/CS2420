#ifndef SLIDER_GAME_H
#define SLIDER_GAME_H

#include "avlTree.h"
#include "game.h"

class SliderGame{
public:
	SliderGame(){
		//empty
	}
	string bruteForceSolve(string title, int game[]){
		stringstream ss;
		ss << "----Brute Force Method---- (" << title << "):\n\n";
		Game g;
		ss << g.playGiven(title, game);
		//ss << endl;
		return ss.str();
	}

	string aStarSolve(string title, int game[]){
		stringstream ss;
		ss << "----A* Method---- (" << title << "):\n\n";
		puzzle.makeBoard(game);
		ss << "Original Board (" << title << "):\n" << puzzle.toString() << endl;         // print out original board
		puzzle.moves = "";                 //reset moves and LastMove
		puzzle.LastMove = ' ';
		orig = puzzle;
		solvePuzzle(puzzle);           // solve
		puzzle.LastMove = ' ';            // reset last move
		str = puzzle.moves;
		ss << "Moves: " << str << endl;
		ss << "Show Me:\n";                  // print out moves needed to reach solution
		for (unsigned int i = 0; i < str.size(); i++){
			ss << puzzle.moves[i] << "==>\n";
			orig.makeMove(puzzle.moves[i], puzzle.LastMove);
			ss << orig.toString() << endl;
		}
		ss << "Moves required: " << str.size() << endl;
		ss << "Queue: Removed - " << priorityQueue.removed << endl << endl;
		puzzle.moves = "";
		puzzle.LastMove = ' ';
		priorityQueue.makeEmpty();
		history.makeEmpty();
		return ss.str();
	}

	void solvePuzzle(Board &b){
		while (!b.operator==(solved)){
			if (b.checkRight()){                                // check if move is possible, then put inside boards move if it is
				Board b_copy = Board(b);
				b_copy.makeMove('R', b_copy.LastMove);
				g.b = b_copy;
				g.update();
				if (!history.findBoard(g.b)){
					history.insert(g);
					priorityQueue.insert(g);
				}
			}
			if (b.checkLeft()){
				Board b_copy = Board(b);
				b_copy.makeMove('L', b_copy.LastMove);
				g.b = b_copy;
				g.update();
				if (!history.findBoard(g.b)){
					history.insert(g);
					priorityQueue.insert(g);
				}
			}
			if (b.checkUp()){
				Board b_copy = Board(b);
				b_copy.makeMove('U', b_copy.LastMove);
				g.b = b_copy;
				g.update();
				if (!history.findBoard(g.b)){
					history.insert(g);
					priorityQueue.insert(g);
				}
			}
			if (b.checkDown()){
				Board b_copy = Board(b);
				b_copy.makeMove('D', b_copy.LastMove);
				g.b = b_copy;
				g.update();
				if (!history.findBoard(g.b)){
					history.insert(g);
					priorityQueue.insert(g);
				}
			}
			b = priorityQueue.removeMin()->element.b;                  // next board to be tested
		}
	}

private:
	AvlTree<GameState> priorityQueue;
	AvlTree<GameState> history;
	Board puzzle;
	Board solved;
	Board orig;
	GameState g;
	string str;
};

#endif