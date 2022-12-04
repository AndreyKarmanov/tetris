#include "piece.h"
#include "graphicsWrapper.h"
#include "textObserver.h"
#include "game.h"

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

std::string getSequence(std::ifstream &file);

int main(int argc, char *argv[])
{
    using namespace std;
    // new game setup:
    // name, level, rows, cols, random, seed, player#
    vector<Game *> games{
        new Game("Andrey", 0, 18, 11, true, 0, 1), new Game("John", 0, 18, 11, true, 0, 2)
        // , new Game("Nolan", 0, 18, 11, true, 0, 3)
    };

    GraphicsWrapper *gw = new GraphicsWrapper(vector<GameSubject *>(games.begin(), games.end()));
    string input;
    Game *g;
    gw->notifyAll();
    for (int i = 0;; i = (i + 1) % games.size())
    {
        g = games[i];
        cout << "Player " << g->getName() << "'s turn" << endl;
        cin >> input;
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
            if (g->getLastClearCount() >= 2)
            {
                cout << "Player " << g->getName() << " has cleared " << g->getLastClearCount() << " lines!" << endl;
                cout << "Choose a bonus: heavy, blind, or force [IJLOTSZ]" << endl;
                while (cin >> input)
                {
                    if (input == "heavy")
                    {
                        games[(i + 1) % games.size()]->setHeavy(true);
                        break;
                    }
                    else if (input == "blind")
                    {
                        //  games[(i + 1) % games.size()]->setBlind(true);
                        break;
                    }
                    else if (input == "force")
                    {
                        cin >> input;
                        games[(i + 1) % games.size()]->setPiece(input[0]);
                        break;
                    }
                    cout << "Invalid bonus" << endl;
                }
            }
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
            g->setRandom();
        }
        else if (input == "sequence")
        {
            // needs a sequenc of commands
        }
        else if (input == "norandom")
        {
            string file;
            if (cin >> file)
            {
                ifstream f(file);
                if (f.is_open())
                {
                    g->setSequence(getSequence(f));
                    f.close();
                }
            }
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
        else
        {
            cout << "Invalid command" << endl;
            --i;
        }
        g->notifyObservers();
    }

    delete gw;
    for (Game *g : games)
    {
        delete g;
    }
    return 0;
}

std::string getSequence(std::ifstream &file)
{
    std::ostringstream iss;
    std::string line;
    while (file >> line)
    {
        iss << line;
    }
    return iss.str();
}
