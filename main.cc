#include "piece.h"
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
    // Create a game
    Game *g = new Game("Andrey", 0, 10, 11, true, 0, 1);
    // Create a text observer
    TextObserver *to = new TextObserver(g);
    vector<GameSubject*> games{g};
    GraphicsWrapper *gw = new GraphicsWrapper(games);
    g->attach(to);
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
        else if (input == "levelup")
        {
            g->setLevel(g->getLevel() + 1);
        }
        else if (input == "leveldown")
        {
            g->setLevel(g->getLevel() - 1);
        }
        else if (input == "restart")
        {
            g->restart();
        }
        else if (input == "random")
        {

        }
        else if (input == "sequence")
        {

        }
        else if (input == "I")
        {
            g->setPiece('I');
        }
        else if (input == "J")
        {
            g->setPiece('J');
        }
        else if (input == "L")
        {
            g->setPiece('L');
        }
        else if (input == "O")
        {
            g->setPiece('O');
        }
        else if (input == "S")
        {
            g->setPiece('S');
        }
        else if (input == "Z")
        {
            g->setPiece('Z');
        }
        else if (input == "T")
        {
            g->setPiece('T');
        }
        else if (input == "quit")
        {
            break;
        }
        g->notifyObservers();
    }
    return 0;
}