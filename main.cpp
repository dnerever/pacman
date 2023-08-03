#include <iostream>
#include <string>
#include "Game.h"
#include "Player.h"
#include "Game.cpp"
#include "Player.cpp"

/*
Steps to run the game:
1. In your terminal run 'make run'
2. Once the game loads you enter your first move. 
    a. Possible moves (w[UP], a[LEFT], s[DOWN], d[RIGHT])
    b. then press (enter)
3. Repeat step 2!
4. Now you have either won or lost 


Step 2: Improving the game
    - Added enemy respawn at a random location after enemy death
*/

using namespace std;

int main(){
    Game g;    // Initialize Game
    Player *me = new Player("Pacman", true);   // Create human character (Pacman)
    std::vector<Player*> enemyList;             // Initialize a vector to store enemies
    int numOfEnemies = 2;                       //Select number of enemies (0-65)
    for (int eLoop = 0; eLoop < numOfEnemies; eLoop++){
        enemyList.push_back(new Player("Ghost", false));
        enemyList[eLoop]->SetPosition(g.getBoard().randomPosition());
    }
    g.NewGame(me, enemyList, enemyList.size());

    string msg = "\nAvailable moves: RIGHT(D) DOWN(S)"; //Initial available moves
    bool playerMoved = false;
    while(!g.IsGameOver(me)){                   // Only keep playing if the game is still going
        // Display board along with other data
        cout << g.getBoard() << "\n"
            "Number of moves by human player: " << me->getMoves() <<
            "  ||  Lives Remaining " << me->getLives() <<
            msg <<endl << "Please enter your move: ";


        playerMoved = g.TakeTurn(me, enemyList);              // Have player take their turn
        if(playerMoved){
            for(int enemyTurn = 0; enemyTurn < enemyList.size(); enemyTurn++){
                g.TakeTurnEnemy(enemyList[enemyTurn]);  // Have each enemy take their turn
            }
        }
        std::vector<Position> moves = g.getBoard().GetMoves(me);    // Calculate player's possible moves
        
        // Store data to display users legal moves
        msg = "\nAvailable moves: ";
        for(int i = 0; i < moves.size(); i++){
            msg = msg + me->ToRelativePosition(moves[i]) + " ";
        }
    }
    
    cout << g.getBoard() << "\n------Game Over------\n";
    cout << g.GenerateReport(me);

    // Free Allocated Memory
    delete me;                                      // Pacman
    for (int i = 0; i < enemyList.size(); i++){
        delete enemyList[i];                        // Enemies
    }

    return 0;
}