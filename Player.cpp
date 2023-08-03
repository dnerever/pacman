#include "Player.h"
#include "catch.hpp"
#include <vector>
#include <iostream>
#include <random>
#include <vector>
#include <cmath>

Player::Player(const std::string name, const bool is_human){
    name_ = name;
    points_ = 0;
    
    if(is_human == true){
        pos_.row = 0;
        pos_.col = 0;
    }
    else{   //Only a single enemy. Also would like to add randomization to enemy spawns.
        pos_.row = 4;
        pos_.col = 6;
    }

    is_human_ = is_human;
    if(!is_human_){  lives_ - 2;  }
    has_Treasure_ = false;
    isDead_ = false;
    moves_ = 0;
}

void Player::ChangePoints(const int x){ //Done
    points_ = get_points();
    points_ += x;
}

void Player::SetPosition(Position pos){ //Done
    pos_.row = pos.row;
    pos_.col = pos.col;
}

void Player::setIsDead(bool isdead){    //Done
    isDead_ = isdead;
}

void Player::setLives(int lives){   //Done
    lives_ = lives;
}

std::string Player::ToRelativePosition(Position other){
    if(get_position().row == other.row){     //move is horizontal
        if(get_position().col-1 == other.col){  return "LEFT(A)";  }
        else{  return "RIGHT(D)";  }
    }
    else{   //move is vertical
        if(get_position().row-1 == other.row){  return "UP(W)";  }
        else{  return "DOWN(S)";  }
    }
    return "(Error)";
}

std::string Player::Stringify(){
    std::string playerReport = "Points: " + std::to_string(get_points());   // "Player: " + get_name() + 
    return playerReport;
}

Position Player::randomPosition(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0,10);
    Position random;
    random.row = dis(gen);
    random.col = dis(gen);
    return random;
}

Position Player::moveToPlayer(Player *target, std::vector<Position> availableMoves){
    Position currentPos = get_position();           //enemy starting pos
    Position targetPos = target->get_position();     //pacman
    Position newMove = currentPos;
    int col = 0;
    int row = 0;
    int colDiff = currentPos.col - targetPos.col;       // +: enemy is to the right of pacman 
    int rowDiff = currentPos.row - targetPos.row;       // +: enemy is below of pacman
    
    int xVal;
    int yVal;
    int dist;
    std::vector<int> distances;

    // std::cout << "Distance vector: ( ";
    for(int j = 0; j < availableMoves.size(); j++){
        xVal = availableMoves[j].col - targetPos.col;
        yVal = availableMoves[j].row - targetPos.row;
        dist = abs(xVal) + abs(yVal);
        distances.push_back(dist);
        // std::cout << dist << ", ";
    }
    // std::cout << ")" <<std::endl;

    int min = 100;
    int index;
    for(int m = 0; m < availableMoves.size(); m++){
        if(min > distances[m]){
            min = distances[m];
            index = m;
        }
    }
    // std::cout << "Best distance selected: " << distances[index] <<std::endl;

    return availableMoves[index];
}