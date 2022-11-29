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
    g->setPiece('S');
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
        g->notifyObservers();
    }
    return 0;
}