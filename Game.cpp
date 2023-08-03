#include "Game.h"
#include "catch.hpp"
#include <vector>
#include <iostream>
#include <string>
#include <random>
#include <sstream>
#include <cstring>

std::string SquareTypeStringify(SquareType sq){
    std::string sqString;
    switch(sq){
        case SquareType::Wall: 
            sqString = "Wall";
            break;
        case SquareType::Dots:
            sqString = "Dots";
            break;
        case SquareType::Pacman:
            sqString = "Pacman";
            break;
        case SquareType::Treasure:
            sqString = "Treasure";
            break;
        case SquareType::Enemies:
            sqString = "Enemies";
            break;
        case SquareType::Empty:
            sqString = "Empty";
            break;
        case SquareType::PowerfulPacman:
            sqString = "PowerfulPacman";
            break;
        case SquareType::Trap:
            sqString = "Trap";
            break;
        case SquareType::EnemySpecialTreasure:
            sqString = "EnemySpecialTreasure";
            break;
    }
    return sqString;
}

Board::Board(){
    std::vector<std::vector<SquareType>> boardVect = {
        {SquareType::Empty, SquareType::Dots, SquareType::Dots, SquareType::Dots, SquareType::Wall, SquareType::Wall, SquareType::Wall, SquareType::Wall, SquareType::Wall, SquareType::Dots}, //0
        {SquareType::Dots, SquareType::Dots, SquareType::Wall, SquareType::Wall, SquareType::Dots, SquareType::Wall, SquareType::Dots, SquareType::Dots, SquareType::Wall, SquareType::Dots},   //1
        {SquareType::Dots, SquareType::Dots, SquareType::Wall, SquareType::Wall, SquareType::Dots, SquareType::Wall, SquareType::Dots, SquareType::Dots, SquareType::Wall, SquareType::Dots},   //2
        {SquareType::Dots, SquareType::Dots, SquareType::Dots, SquareType::Dots, SquareType::Dots, SquareType::Wall, SquareType::Wall, SquareType::Dots, SquareType::Wall, SquareType::Dots},   //3
        {SquareType::Dots, SquareType::Wall, SquareType::Wall, SquareType::Dots, SquareType::Dots, SquareType::Dots, SquareType::Dots, SquareType::Dots, SquareType::Dots, SquareType::Dots},   //4
        {SquareType::Treasure, SquareType::Wall, SquareType::Wall, SquareType::Wall, SquareType::Wall, SquareType::Dots, SquareType::Dots, SquareType::Dots, SquareType::Dots, SquareType::Dots},   //5
        {SquareType::Dots, SquareType::Dots, SquareType::Dots, SquareType::Dots, SquareType::Dots, SquareType::Dots, SquareType::Dots, SquareType::Dots, SquareType::Dots, SquareType::Dots},   //6
        {SquareType::Dots, SquareType::Dots, SquareType::Dots, SquareType::Dots, SquareType::Dots, SquareType::Wall, SquareType::Wall, SquareType::Dots, SquareType::Dots, SquareType::Dots},   //7
        {SquareType::Dots, SquareType::Dots, SquareType::Dots, SquareType::Dots, SquareType::Dots, SquareType::Wall, SquareType::Wall, SquareType::Wall, SquareType::Wall, SquareType::Wall},   //8
        {SquareType::Dots, SquareType::Dots, SquareType::Dots, SquareType::Dots, SquareType::Dots, SquareType::Wall, SquareType::Wall, SquareType::Wall, SquareType::Wall, SquareType::Wall}    //9
        };
    //set values of the board arr

    for(int row = 0; row < 10; row++){
        for(int col = 0; col < 10; col++){
            arr_[row][col] = boardVect[row][col];
            if(boardVect[row][col] == SquareType::Dots){
                dotArr_[row][col] = SquareType::Dots;
            }
            else if(boardVect[row][col] == SquareType::Treasure){
                dotArr_[row][col] = SquareType::Treasure;
            }
            else{
                dotArr_[row][col] = SquareType::Empty;
            }
        }
    }
}

// void Board::SetSquareValue(Position pos, SquareType value){
//     arr_[pos.row][pos.col] = value;
// }

std::vector<Position> Board::GetMoves(Player *p){
    std::vector<Position> legalMoves;           //return vector of positions available to move to
    Position playerPos = p->get_position();     //temp Position variable to take current player position
    std::vector<int> dirPairs = {-1, 0,  0, 1,  1, 0,  0, -1};  //{row, col} positions ordered "N,E,S,W" OR "U,R,D,L"
    // int rowMax = 10;
    // int colMax = 10;
    Position temp;
    SquareType squareVal;
    for(int checkBounds = 0; checkBounds < 4; checkBounds++){
        temp.row = playerPos.row + dirPairs[2*checkBounds];
        temp.col = playerPos.col + dirPairs[2*checkBounds + 1];

        if(((0 <= temp.row) && (temp.row < 10)) && ((0 <= temp.col ) && (temp.col < 10))){
            squareVal = get_square_value(temp);
            if(!(squareVal == SquareType::Wall) && !((get_square_value(p->get_position()) == get_square_value(temp)))){  //checks if move is into a wall or a ghost onto a ghost
                legalMoves.push_back(temp);
            }
            else{
            }
        }
    }
    return legalMoves;
}

bool Board::MovePlayer(Player *p, Position pos, std::vector<Player*> enemylist){
    std::vector<Position> availableMoves = GetMoves(p);
    Position oldPos = p->get_position();

    for(int enemyVect = 0; enemyVect < enemylist.size(); enemyVect++){  //checks enemy conflicts
        if(pos == enemylist[enemyVect]->get_position() && !(enemylist[enemyVect]->isDead())){
            if(p->hasTreasure()){
                p->SetPosition(pos);
                p->setHasTreasure(false);
                enemylist[enemyVect]->setLives(enemylist[enemyVect]->getLives() - 1);
                enemylist[enemyVect]->SetPosition(randomPosition());
                SetSquareValue(enemylist[enemyVect]->get_position(), SquareType::Enemies);
                
                SetSquareValue(pos, SquareType::Pacman);
                SetSquareValue(oldPos, SquareType::Empty);
            }
            else{
                p->SetPosition(pos);
                p->setLives(p->getLives() - 1);
                SetSquareValue(pos, SquareType::HitPacman);
                SetSquareValue(oldPos, SquareType::Empty);
                set_dots_value(pos);
            }
            
            p->incrementMoves();
            return true;
        }
    }
    
    for(int vect = 0; vect < availableMoves.size(); vect++){
        if(pos == availableMoves[vect]){
            if(get_dots_value(pos) == SquareType::Dots){
                p->ChangePoints(1);     //player dot count
                set_dots_value(pos);
            }
            else if(get_square_value(pos) == SquareType::Treasure){
                p->ChangePoints(100);
                p->setHasTreasure(true);
                set_dots_value(pos);
            }
            SquareType sqPlayerType;
            if(p->hasTreasure()){ sqPlayerType = SquareType::PowerfulPacman;  }
            else{  sqPlayerType = SquareType::Pacman;  }
            p->SetPosition(pos);
            SetSquareValue(p->get_position(), sqPlayerType);
            SetSquareValue(oldPos, SquareType::Empty);
            p->incrementMoves();
            return true;
        }
    }
    return false;
}

bool Board::MoveEnemy(Player *p, Position pos, Player *Pacman){
    std::vector<Position> availableMoves = GetMoves(p);
    Position oldPos = p->get_position();
    
    for(int vect = 0; vect < availableMoves.size(); vect++){
        if(pos == availableMoves[vect]){
            if(get_square_value(pos) == SquareType::Pacman){    //killed Pacman
                Pacman->setLives(Pacman->getLives() - 1);
                SetSquareValue(Pacman->get_position(), SquareType::HitPacman);
            }
            else if(get_square_value(pos) == SquareType::PowerfulPacman){   // killed by pacman
                p->SetPosition(randomPosition());
                // p->setIsDead(true);
                p->setLives((p->getLives() - 1));
                SetSquareValue(pos, SquareType::Pacman);
                Pacman->setHasTreasure(false);
                SetSquareValue(oldPos, get_dots_value(oldPos));
                return true;
            }
            else{
                SetSquareValue(pos, SquareType::Enemies);
            }
            p->SetPosition(pos);
            if(Pacman->get_position() == oldPos){
                SetSquareValue(oldPos, SquareType::HitPacman);
            }
            else{ //set what used to be there pre-ghost
                SetSquareValue(oldPos, get_dots_value(oldPos));     //edge case of two ghosts stacking when one stacks then the other leaves.
            }
            return true;
        }
    }
    return false;
}


std::ostream & operator<<(std::ostream & os, const Board & b){
    os << std::endl << std::endl;
    for(int row = 0; row < 10; row++){
        os << "   " << "[" << row << "] ";
        for(int col = 0; col < 10; col++){
            switch(b.arr_[row][col]){
                case SquareType::Wall: 
                    os << " ❎ ";
                    break;
                case SquareType::Dots: 
                    os << " 🟣 ";
                    break;
                case SquareType::Pacman: 
                    os << " 😃 ";
                    break;
                case SquareType::Treasure:
                    os << " 🏆 ";
                    break;
                case SquareType::Enemies:
                    os << " 👻 ";
                    break;
                case SquareType::Empty:
                    os << " ⬛ ";
                    break;
                case SquareType::PowerfulPacman:
                    os << " 🐘 ";
                    break;
                case SquareType::Trap:
                    os << " 💥 ";
                    break;
                case SquareType::EnemySpecialTreasure:
                    os << " 🧠 ";
                    break;
                case SquareType::HitPacman:
                    os << " 🤒 ";
                    break;
                case SquareType::DeadPacman:
                    os << " 😵 ";
                    break;
            }
        }
        os <<std::endl;
    }
    return os;
}

Position Board::randomPosition(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0,9);
    Position random{dis(gen), dis(gen)};
    while(get_square_value(random) != SquareType::Dots){
        random.row = dis(gen);
        random.col = dis(gen);
    }
    return random;
}

//Game Class -------------------------------

Game::Game(){
    Board *base = new Board();
    board_ = base;
    turn_count_ = 0;
    dots_count_ = 64;  //default setup
    GameOver = false;
}

void Game::NewGame(Player *human, std::vector<Player*> enemylist, const int enemies){    
    players_.push_back(human);  //add human player (Pacman) to players vector
    for(int enemyIndex = 0; enemyIndex < enemylist.size(); enemyIndex++){   //Add each enemy to the player vector
        players_.push_back(enemylist[enemyIndex]);
    }
    for(int playerVect = 0; playerVect < players_.size(); playerVect++){
        SquareType playerType;
        if(players_[playerVect]->is_human()){  playerType = SquareType::Pacman;  }
        else{  playerType = SquareType::Enemies;  }
        getBoard().SetSquareValue(players_[playerVect]->get_position(), playerType);
    }
    turn_count_ = 0;
    dots_count_ = 64;           //default setup dots count
    GameOver = false;
}

bool Game::TakeTurn(Player *p, std::vector<Player*> enemylist){
    bool moveMade = false;                          //tracks if a move has been made
    Position move = p->get_position();

    std::string moveError = "\n------Move couldn't be made, try again------";
    std::string commandError = "\n------Move is too long/short, try again------";

    std::string userInput;
    std::getline(std::cin, userInput);
    if(!(userInput.length())){                      //case if the user inputs more than one key/char
        std::cout << commandError <<std::endl;      //prompts user to retry input
        return false;
    }
    if(userInput == "w"){
        move.row--;
        if(getBoard().MovePlayer(p, move, enemylist)){  moveMade = 1; turn_count_++;  }
        else{ std::cout << moveError <<std::endl;  }
    }
    else if(userInput == "d"){
        move.col++;
        if(getBoard().MovePlayer(p, move, enemylist)){  moveMade = 1; turn_count_++;  }
        else{ std::cout << moveError <<std::endl;  }
    }
    else if(userInput == "s"){
        move.row++;
        if(getBoard().MovePlayer(p, move, enemylist)){  moveMade = 1; turn_count_++;  }
        else{ std::cout << moveError <<std::endl;  }
    }
    else if(userInput == "a"){
        move.col--;
        if(getBoard().MovePlayer(p, move, enemylist)){  moveMade = 1; turn_count_++;  }
        else{ std::cout << moveError <<std::endl; }
    }
    else{
        std::cout << "\n------Invalid input: (" << (userInput) << "), try again------" <<std::endl;
    }
    return moveMade;
}

void Game::TakeTurnEnemy(Player *p){
    if(p->isDead()){  return;  }

    //If random ghost moves are desired
    // std::vector<Position> enemyMoves = getBoard().GetMoves(p);
    // std::random_device rd;
    // std::mt19937 gen(rd());
    // std::uniform_int_distribution<> dis(0,enemyMoves.size()-1);
    // getBoard().MoveEnemy(p, enemyMoves[dis(gen)], players_[0]);      //for random ghost movement

    //Calculated ghost moves
    Position bestMove = p->moveToPlayer(players_[0], getBoard().GetMoves(p));
    getBoard().MoveEnemy(p, bestMove, players_[0]);
}

bool Game::IsGameOver(Player *p){
    if((p->getLives() <= 0) || checkIfDotsOver()){  return true;  } //checks if the player has died OR collected all dots
    return false;
}

bool Game::checkIfDotsOver(){
    int dotCount = 0;
    Position pos;
    for(int checkDotsRow = 0; checkDotsRow < 9; checkDotsRow++){
        pos.row = checkDotsRow;
        for(int checkDotsCol = 0; checkDotsCol < 9; checkDotsCol++){
            pos.col = checkDotsCol;
            if(getBoard().get_dots_value(pos) == SquareType::Dots){
                dotCount++;
            }
        }
    }
    if(!dotCount){  return true;  }
    return false;
}


std::string Game::GenerateReport(Player *p){
    std::string report;
    int remainingEnemyLives = 0;
    int numOfPlayers = players_.size();
    int numOfEnemies = numOfPlayers - 1;
    for(int eKills = 1; eKills < numOfPlayers; eKills++){
        remainingEnemyLives += players_[eKills]->getLives();
    }
    int kills = 0;
    kills = (numOfEnemies*3) - remainingEnemyLives;

    report = p->Stringify() + "\nEnemies killed: " + std::to_string(kills);
    report = report + "\nPlayer Moves: " + std::to_string(p->getMoves()) + "\n";
    return report;
}