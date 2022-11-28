#include "piece.h"
#include "pieceFactory.h"
#include "graphicsWrapper.h"
#include "textObserver.h"
#include "game.h"

#include <vector>
#include <string>
#include <iostream>

int main(int argc, char *argv[])
{
    using namespace std;
    // Create pieces
    vector<vector<bool>> Igrid =
        {{true, true, true, true}};
    Piece *Ipiece = new Piece(Igrid, 0, 0, 'I');
    vector<vector<bool>> Jgrid =
        {{true, true, true},
         {false, false, true}};
    Piece *Jpiece = new Piece(Jgrid, 0, 0, 'J');
    vector<vector<bool>> Lgrid =
        {{true, true, true},
         {true, false, false}};
    Piece *Lpiece = new Piece(Lgrid, 0, 0, 'L');
    vector<Piece *> pieces = {Ipiece, Jpiece, Lpiece};
    // Create a game
    PieceFactory *pf = new PieceFactory(pieces, true, 0);
    Game *g = new Game("Andrey", pf, 10, 10);
    // Create a text observer
    TextObserver *to = new TextObserver(g);
    g->setPiece('I');
    g->attach(to);
    g->notifyObservers();
    g->move(1, 0);
    g->notifyObservers();
    string input;
    while (cin >> input)
    {
        if (input == "left")
        {
            g->move(-1, 0);
        }
        else if (input == "right")
        {
            g->move(1, 0);
        }
        else if (input == "down")
        {
            g->move(0, 1);
        }
        else if (input == "CW")
        {
            g->rotateCW();
        }
        else if (input == "CCW")
        {
            g->rotateCCW();
        }
        else if (input == "drop")
        {
            g->drop();
        }
        else if (input == "quit" || g->getGameOver())
        {
            break;
        }
        g->notifyObservers();
    }
    return 0;
}