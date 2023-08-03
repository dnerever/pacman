#define CATCH_CONFIG_MAIN
#include <iostream>
#include "Game.h"
#include "Player.h"
#include "Game.cpp"
#include "Player.cpp"


TEST_CASE ("Move Pacman down 1", "[Board::MovePlayer]"){
    Game g;
    Player *me = new Player("Pac", true);
    std::vector<Player*> eList;
    for (int eLoop = 0; eLoop < 3; eLoop++){
        eList.push_back(new Player("Ghost", false));
        eList[eLoop]->SetPosition(eList[eLoop]->randomPosition());
    }
    g.NewGame(me, eList, eList.size());

    g.TakeTurn(me, eList);

    // CHECK()
    for (int i = 0; i < eList.size(); i++){
        delete eList[i];
    }
}



// Board board1;
//     cout << board1 <<endl;

//     Position p1;
//     p1.row = 0;
//     p1.col = 0;
//     SquareType valPac = board1.get_square_value(p1);    //idk if this works yet
//     // std::cout << valPac <<endl;

//     // board1.SetSquareValue(p1, SquareType::Wall);
//     // cout << board1 <<endl;

//     Player enemy1("blue ghost", false);
//     int pointsTest = enemy1.get_points();
//     cout << pointsTest <<endl;
//     enemy1.ChangePoints(10);
//     pointsTest = enemy1.get_points();
//     cout << pointsTest <<endl;

//     Position temp1 = enemy1.get_position();
//     cout << "Enemy initial position: row = " << temp1.row << ",  col = " << temp1.col <<endl;
//     Position enemyMove;
//     enemyMove.row = 5;
//     enemyMove.col = 7;
//     enemy1.SetPosition(enemyMove);
//     Position temp2 = enemy1.get_position();
//     cout << "Enemy initial position: row = " << temp2.row << ",  col = " << temp2.col <<endl;

    
//     Player pac("Pacman", true);
//     // Player *pacPtr = &pac;
//     cout << "has_treasure == " << pac.hasTreasure() <<endl;
//     pac.setHasTreasure();
//     cout << "has_treasure == " << pac.hasTreasure() <<endl;

//     // cout << "isDead == " << pac.isDead() <<endl;
//     // pac.setIsDead(true);
//     // cout << "isDead == " << pac.isDead() <<endl;

//     cout << "Lives == " << pac.getLives() <<endl;
//     pac.setLives(2);
//     cout << "Lives == " << pac.getLives() <<endl;

//     Game g1;

//     Player *player1 = new Player("Pacman3", true);

//     std::vector<Position> moves = board1.GetMoves(player1);

//     cout << board1 <<endl;

//     cout << "Vector of moves: ";
//     for(int vecPrint = 0; vecPrint < moves.size(); vecPrint++){
//         cout << "(" << moves[vecPrint].row << ", " << moves[vecPrint].col << "), ";
//     }
//     cout <<endl;

//     Player *enemy2 = new Player("enemy2", false);

//     std::vector<Position> movesEnemy2 = board1.GetMoves(enemy2);
//     // Position origin;
//     // origin.row = 0;
//     // origin.col = 0;
//     // enemy2->SetPosition(origin);
//     Position tempPos = enemy2->get_position();
//     cout << "Enemy initial position: row = " << tempPos.row << ",  col = " << tempPos.col <<endl;

//     cout << board1 <<endl;

//     cout << "Vector of movesEnemy2: ";
//     for(int vecPrint = 0; vecPrint < movesEnemy2.size(); vecPrint++){
//         cout << "(" << movesEnemy2[vecPrint].row << ", " << movesEnemy2[vecPrint].col << "), ";
//     }
//     cout <<endl;
