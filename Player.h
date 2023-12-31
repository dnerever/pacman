#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <string>
#include <vector>

struct Position {
	int row;
	int col;

	// // already implemented for you!
	bool operator==(const Position &other) {
		return row == other.row && col == other.col;
	}
};

class Player {
public:
	// TODO: implement
	Player(const std::string name, const bool is_human);  // constructor

	// // These are already implemented for you
	std::string get_name() const {return name_; }  // inline member function
	int get_points() const {return points_; }  // inline member function
	Position get_position() const {return pos_; }  // inline member function
	bool is_human() const {return is_human_; }  // inline member function
	bool hasTreasure() const {return has_Treasure_; }  // inline member function
	bool isDead() const {return isDead_; }  // inline member function
	int getLives() const {return lives_; }


	// // TODO: implement the following functions
	// // You MUST implement the following functions
	void ChangePoints(const int x);

	// // set a new position for this player
	void SetPosition(Position pos);

	// // checks if the player owns a treasure	//this comment seems wrong
	void setHasTreasure(bool has){  has_Treasure_ = has;  };	//implementing when called to set has_Treasure = true

	// //checks if the enemy is dead
	void setIsDead(bool isdead);	//implementing when called to set player to dead

	// //updates the lives for a player
	void setLives(int lives);


	// // You may want to implement these functions as well
	// // ToRelativePosition is a function we used to translate positions
	// // into direction s relative to the player (up, down, etc)
	std::string ToRelativePosition(Position other);

	// // Convert this player to a string representation of their name and points
	std::string Stringify();

	// // this method should return the number of moves made by the player in this game 
	int getMoves(){  return moves_;  };

	// // update the number of moves in each human player's turn
	void incrementMoves(){  moves_++;  };

	// You may add other functions as needed/wanted
	
	// To initialize ghosts at random points
	Position randomPosition();

	Position moveToPlayer(Player *target, std::vector<Position> availableMoves);

private:
	std::string name_;
	int points_;
	Position pos_;
	bool is_human_;
	bool has_Treasure_;
	bool isDead_;
	int lives_ = 3;
	int moves_;

	// You may add other fields as needed

}; // class Player

#endif  // _PLAYER_H_
