#include "Game.h"

Game::Game(){
	//empty
}

void Game::playGiven(string title, int game[]){
	puzzle.makeBoard(game);
	cout << "Original Board (" << title << ": Given):\n" << puzzle.toString() << endl;         // print out original board
	puzzle.moves = "";                 //reset moves and LastMove
	puzzle.LastMove = ' ';
	orig = puzzle;
	solvePuzzle(puzzle);           // solve
	puzzle.LastMove = ' ';            // reset last move
	str = puzzle.moves;
	cout << "Show Me:\n";                  // print out moves needed to reach solution
	for (int i = 0; i < str.size(); i++){
		cout << puzzle.moves[i] << "==>\n";
		orig.makeMove(puzzle.moves[i], puzzle.LastMove);
		cout << orig.toString() << endl;
	}
	cout << "Moves required: " << str.size() << endl;
	cout << "Queue: Added - " << boards.getAdded() << ", Removed - " << boards.getRemoved() << ", Current Size - " << boards.getSize() << endl;
	puzzle.moves = "";
	puzzle.LastMove = ' ';
	history.empty();
	boards.empty();
}

void Game::playRandom(string title, int jumbleCT){              // play with a ramdom board
	puzzle.makeBoard(jumbleCT);         // make random board
	cout << "Original Board ("<< title << ": Random):\n" << puzzle.toString() << endl;
	puzzle.moves = "";
	puzzle.LastMove = ' ';
	orig = puzzle;
	solvePuzzle(puzzle);
	puzzle.LastMove = ' ';
	str = puzzle.moves;
	cout << "Show Me:\n";
	for (int i = 0; i < str.size(); i++){
		cout << puzzle.moves[i] << "==>\n";
		orig.makeMove(puzzle.moves[i], puzzle.LastMove);
		cout << orig.toString() << endl;
	}
	cout << "Moves required: " << str.size() << endl;
	cout << "Queue: Added - " << boards.getAdded() << ", Removed - " << boards.getRemoved() << ", Current Size - " << boards.getSize() << endl;
	puzzle.moves = "";
	puzzle.LastMove = ' ';
	history.empty();
	boards.empty();
}

bool Game::solvePuzzle(Board &b){
	if (b.operator==(solved))
		return true;

	if (b.checkRight()){                                // check if move is possible, then put inside boards move if it is
		Board b_copy = Board(b);
		b_copy.makeMove('R', b_copy.LastMove);
		if (!(history.find(b_copy))){
			history.add(b_copy);
			boards.add(b_copy);
		}
	}
	if (b.checkLeft()){
		Board b_copy = Board(b);
		b_copy.makeMove('L', b_copy.LastMove);
		if (!(history.find(b_copy))){
			history.add(b_copy);
			boards.add(b_copy);
		}
	}
	if (b.checkUp()){
		Board b_copy = Board(b);
		b_copy.makeMove('U', b_copy.LastMove);
		if (!(history.find(b_copy))){
			history.add(b_copy);
			boards.add(b_copy);
		}
	}
	if (b.checkDown()){
		Board b_copy = Board(b);
		b_copy.makeMove('D', b_copy.LastMove);
		if (!(history.find(b_copy))){
			history.add(b_copy);
			boards.add(b_copy);
		}
	}
	b = boards.remove();                  // next board to be tested
	return solvePuzzle(b);
}