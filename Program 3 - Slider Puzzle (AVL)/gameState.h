#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "Board.h"

class GameState{
public:
	Board b;
	Board solved;
	int cost;
	int estimateCost;
	int priority;
	GameState(){
		//empty
	}
	GameState(Board B){
		b = B;
		update();
	}

	void update()
	{
		calculateEstimateCost();
		calculateCost();
		calculatePriority();
	}

	void calculatePriority()
	{
		priority = estimateCost + cost;
	}
	void calculateEstimateCost(){
		estimateCost = b.manhattanDist(solved);
	}
	void calculateCost(){
		cost = b.moves.size();
	}

	string toString(){
		stringstream ss;
		for (int i = 0; i < b.SIZE; i++){
			for (int j = 0; j < b.SIZE; j++){
				ss << b.board[i][j] << " ";
			}
			ss << endl;
		}
		ss << "Moves: " << b.moves << endl;
		ss << "Priority: " << priority << endl;
		ss << "Expected Moves Remaining: " << estimateCost << endl;
		return ss.str();
	}

	bool operator<(const GameState & rhs) const{
		return priority < rhs.priority;
	}
};

ostream&  operator<<(ostream& ss, GameState& gs) {
	ss << gs.toString() << endl;
	return ss;
}

#endif
