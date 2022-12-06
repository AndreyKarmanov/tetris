#include "piece.h"
#include "graphicsWrapper.h"
#include "textWrapper.h"
#include "game.h"

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>

std::string getSequence(std::ifstream &file);
void loadCommandSequence(std::stringstream &ss, std::ifstream &file);

void getCommand(std::stringstream &ss, std::string &command, int &multiplier);
void loadCommands(std::stringstream &ss, std::ifstream &file);

std::map<std::string, std::string> commands{
    {"left", "left"},
    {"right", "right"},
    {"down", "down"},
    {"clockwise", "clockwise"},
    {"counterclockwise", "counterclockwise"},
    {"drop", "drop"},
    {"levelup", "levelup"},
    {"leveldown", "leveldown"},
    {"norandom", "norandom"},
    {"random", "random"},
    {"sequence", "sequence"},
    {"restart", "restart"},
    {"I", "I"},
    {"J", "J"},
    {"L", "L"},
    {"O", "O"},
    {"S", "S"},
    {"Z", "Z"},
    {"T", "T"},
    {"heavy", "heavy"},
    {"blind", "blind"},
    {"force", "force"},
    {"", ""}};

int main(int argc, char *argv[])
{
    using namespace std;
    // command line args
    string scriptfile1 = "sequence1.txt";
    string scriptfile2 = "sequence2.txt";
    bool textOnly = false;
    int seedNum = 0;
    int startLevel = 0;
    int rows = 18;
    int cols = 11;

    for (int i = 1; i < argc; ++i)
    {
        string arg = argv[i];
        if (arg == "-text")
        {
            textOnly = true;
        }
        else if (arg == "-seed")
        {
            seedNum = stoi(argv[++i]);
        }
        else if (arg == "-scriptfile1")
        {
            scriptfile1 = argv[++i];
        }
        else if (arg == "-scriptfile2")
        {
            scriptfile2 = argv[++i];
        }
        else if (arg == "-startlevel")
        {
            startLevel = stoi(argv[++i]);
        }
        else if (arg == "-rows")
        {
            rows = stoi(argv[++i]);
        }
        else if (arg == "-cols")
        {
            cols = stoi(argv[++i]);
        }
    }
    ifstream file1(scriptfile1);
    ifstream file2(scriptfile2);
    // name, level, rows, cols, random, seed, player#
    vector<Game *>
        games{
            new Game("Andrey", startLevel, rows, cols, true, seedNum, getSequence(file1)),
            new Game("John", startLevel, rows, cols, true, seedNum, getSequence(file2))
            // , new Game("Nolan", 0, 18, 11, true, 0, 3)
        };
    file1.close();
    file2.close();
    GraphicsWrapper *gw;
    TextWrapper *tw;

    tw = new TextWrapper(vector<GameSubject *>(games.begin(), games.end()));
    tw->notifyAll();

    if (!textOnly)
    {
        gw = new GraphicsWrapper(vector<GameSubject *>(games.begin(), games.end()));
        gw->notifyAll();
    }

    string input;
    int multiplier;
    stringstream ss;

    for (int i = 0;; i = (i + 1) % games.size())
    {
        Game *g = games[i];
        cout << "Player " << g->getName() << "'s turn" << endl;
        getCommand(ss, input, multiplier);
        if (input == "left")
        {

            g->move(-1, 0, multiplier);
        }
        else if (input == "right")
        {

            g->move(1, 0, multiplier);
        }
        else if (input == "down")
        {
            g->move(0, 1, multiplier);
        }
        else if (input == "clockwise")
        {
            for (int j = multiplier; j > 0; --j)
            {
                g->rotateCW();
            }
        }
        else if (input == "counterclockwise")
        {
            for (int j = multiplier; j > 0; --j)
            {
                g->rotateCCW();
            }
        }
        else if (input == "drop")
        {
            for (int j = multiplier; j > 0; --j)
            {
                g->drop();
                if (g->getLastClearCount() >= 2)
                {
                    cout << "Player " << g->getName() << " has cleared " << g->getLastClearCount() << " lines!" << endl;
                    cout << "Choose a bonus: heavy, blind, or force [IJLOTSZ]" << endl;
                    while (true)
                    {
                        getCommand(ss, input, multiplier);
                        if (input == "heavy")
                        {
                            games[(i + 1) % games.size()]->setHeavy(true);
                            break;
                        }
                        else if (input == "blind")
                        {
                            games[(i + 1) % games.size()]->setBlind(true);
                            break;
                        }
                        else if (input == "force")
                        {
                            getCommand(ss, input, multiplier);
                            games[(i + 1) % games.size()]->setPiece(input[0]);
                            break;
                        }
                        cout << "Invalid bonus" << endl;
                    }
                    games[(i + 1) % games.size()]->notifyObservers();
                }
            }
        }
        else if (input == "levelup")
        {
            g->setLevel(g->getLevel() + 1 * multiplier);
        }
        else if (input == "leveldown")
        {
            g->setLevel(g->getLevel() - 1 * multiplier);
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
            string file;
            getCommand(ss, file, multiplier);
            ifstream f(file);
            if (f.is_open())
            {
                loadCommandSequence(ss, f);
                f.close();
            }
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

    if (!textOnly)
    {
        delete gw;
    }
    for (Game *g : games)
    {
        delete g;
    }
    return 0;
}

std::string findSimilarCommand(std::string command)
{
    bool foundCommand = false;
    std::string similarCommand = command;
    for (auto pair : commands)
    {
        if (pair.first.find(command) == 0)
        {
            if (foundCommand)
            {
                return command;
            }
            else
            {
                foundCommand = true;
                similarCommand = pair.second;
            }
        }
    }
    return similarCommand;
}

void getCommand(std::stringstream &ss, std::string &command, int &multiplier)
{
    using namespace std;
    string input;
    if (ss.eof() || ss.str().empty())
    {
        getline(cin, input);
        ss.str(input);
        ss.clear();
    }
    ss >> input;
    int nonDigit = input.find_first_not_of("0123456789");
    multiplier = 1;

    if (nonDigit < input.size())
    {
        command = findSimilarCommand(input.substr(nonDigit, input.length()));
    }
    else
    {
        command = findSimilarCommand(input);
    }
    if (isdigit(input[0]))
    {
        multiplier = stoi(input.substr(0, nonDigit));
    }
    cout << "Command: " << command << " Multiplier: " << multiplier << endl;
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

void loadCommandSequence(std::stringstream &ss, std::ifstream &file)
{
    std::string line;
    ss.str("");
    ss.clear();
    while (getline(file, line))
    {
        ss.str(ss.str() + line);
    }
}