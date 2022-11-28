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
    vector<vector<bool>> Ogrid =
        {{true, true},
         {true, true}};
    Piece *Opiece = new Piece(Ogrid, 0, 0, 'O');
    vector<vector<bool>> Sgrid =
        {{false, true, true},
         {true, true, false}};
    Piece *Spiece = new Piece(Sgrid, 0, 0, 'S');
    vector<vector<bool>> Tgrid =
        {{true, true, true},
         {false, true, false}};
    Piece *Tpiece = new Piece(Tgrid, 0, 0, 'T');
    vector<vector<bool>> Zgrid =
        {{true, true, false},
         {false, true, true}};
    Piece *Zpiece = new Piece(Zgrid, 0, 0, 'Z');
    vector<Piece *> pieces = {Ipiece, Jpiece, Lpiece, Opiece, Spiece, Tpiece, Zpiece};
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
        else if (input == "quit")
        {
            break;
        }
        if (g->getGameOver())
        {
            break;
        }
        g->notifyObservers();
    }
    return 0;
}