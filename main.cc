#include "piece.h"
#include "graphicsWrapper.h"
#include "textWrapper.h"
#include "pieceFactory.h"
#include "game.h"

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>

// Loads custom pieces from a file, passing the file into the PieceFactory
void loadCustomPieces(std::ifstream &file);

// Loads a sequence of commands from a file, returning a string of the commands
std::string getSequence(std::ifstream &file);

// Loads a sequence of commands from a file, passing the file into the stringstream
void loadCommandSequence(std::stringstream &ss, std::ifstream &file);

// Gets a command from the stringstream, returning the command and the multiplier
void getCommand(std::stringstream &ss, std::string &command, int &multiplier);

// Loads a sequence of commands from a file, passing the file into the stringstream
void loadCommands(std::stringstream &ss, std::ifstream &file);

// Map of commands to their string representations
// Used to check for command autocomplete and adding renamed commands
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
    {"hold", "hold"},
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

    // Default values for command line arguments
    string scriptfile1 = "sequence1.txt";
    string scriptfile2 = "sequence2.txt";
    string customPieceFile = "";
    bool textOnly = false;
    int seedNum = 0;
    int startLevel = 0;
    int rows = 18;
    int cols = 11;
    int players = 3;

    // Parse command line arguments
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
        else if (arg == "-custom")
        {
            customPieceFile = argv[++i];
        }
        else if (arg == "-players")
        {
            players = stoi(argv[++i]);
        }
        else if (arg == "-help")
        {
            cout << "Usage: ./quadris [-text] [-seed n] [-scriptfile1 f] [-scriptfile2 f] [-startlevel n] [-rows n] [-cols n] [-custom f] [-players n]" << endl;
            return 0;
        }
    }

    // Load custom pieces, if any file provided
    if (customPieceFile != "")
    {
        ifstream f(customPieceFile);
        if (f.is_open())
        {
            PieceFactory::addPieces(f);
            f.close();
        }
    }

    // Load command sequences
    ifstream file1(scriptfile1);
    ifstream file2(scriptfile2);
    std::string seq1 = getSequence(file1);
    std::string seq2 = getSequence(file2);
    file1.close();
    file2.close();

    // Create games
    vector<Game *> games;
    for (int i = 1; i <= min(players, 4); ++i)
    {
        games.push_back(new Game(string("Player " + to_string(i)), startLevel, rows, cols, true, seedNum, i % 2 == 1 ? seq1 : seq2));
    }

    // Create wrappers for graphics and text
    GraphicsWrapper *gw;
    TextWrapper *tw;

    tw = new TextWrapper(vector<GameSubject *>(games.begin(), games.end()));

    // Create graphics window if not text only
    if (!textOnly)
    {
        gw = new GraphicsWrapper(vector<GameSubject *>(games.begin(), games.end()), rows, cols);
        gw->notifyAll();
    }

    // Main game loop variables
    string input;
    int multiplier;
    bool dropped = false; // sets true when a player has dropped a piece to break the turn loop
    bool playing = true;  // sets false when a player has quit to break the game loop

    // String stream that buffers commands from files or user input
    stringstream ss;

    for (int i = 0; playing; i = (i + 1) % games.size())
    {
        // Update to next player
        Game *g = games[i];
        cout << g->getName() << "'s turn" << endl;
        tw->notifyAll();

        // Keep looping until a player drops a piece, or quits
        while (true && playing && !dropped)
        {
            // Get command using helper function
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
                // Repeat command multiple time if multiplier is provided
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
                dropped = true;
                for (int j = multiplier; j > 0; --j)
                {
                    // Drop piece
                    g->drop();

                    // Check if user gets a bonus
                    if (g->getLastClearCount() >= 2)
                    {
                        cout << "Player " << g->getName() << " has cleared " << g->getLastClearCount() << " lines!" << endl;
                        cout << "Choose a bonus: heavy, blind, or force [IJLOTSZ]" << endl;
                        // Loop until user enters a valid bonus
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
                                if (commands.find(input) == commands.end())
                                {
                                    cout << "Invalid bonus" << endl;
                                    continue;
                                }
                                games[(i + 1) % games.size()]->setPiece(input[0]);
                                break;
                            }
                            else if (input == "quit")
                            {
                                playing = false;
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
                // Load command sequence from file
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
            else if (input == "hold")
            {
                g->switchPiece();
            }
            else if (input == "I" || input == "J" || input == "L" || input == "O" || input == "S" || input == "Z" || input == "T")
            {
                // Set piece to input for default piecees. 
                g->setPiece(input[0]);
            }
            else if (input == "quit")
            {
                playing = false;
                break;
            }
            else if (input == "rename")
            {
                string name;
                getCommand(ss, name, multiplier);
                string command;
                getCommand(ss, command, multiplier);

                // Check if command exists, to prevent overwriting
                if (commands.count(command) == 0)
                {
                    commands[command] = name;
                }
                else
                {
                    cout << "Command already exists" << endl;
                }
                --i;
            }
            else
            {
                // if command is not a valid command, check if it is a valid piece
                if (input.length() == 1)
                {
                    g->setPiece(input[0]);
                }

                cout << "Invalid command" << endl;
                --i;
            }
            if (g->getGameOver())
            {
                g->restart();
            }
            g->notifyObservers();
        }
    }

    // Clean up
    delete tw;
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

// Returns a similar command if one exists, otherwise returns the original command
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

// Loads a command from string stream or cin if string stream is empty
void getCommand(std::stringstream &ss, std::string &command, int &multiplier)
{
    using namespace std;
    string input;

    // Check if string stream is empty
    if (ss.eof() || ss.str().empty())
    {
        // Get input from cin
        getline(cin, input);

        // Check if cin is empty, if so, set command to quit
        if (cin.eof())
        {
            command = "quit";
            multiplier = 1;
            return;
        }
        ss.str(input);
        ss.clear();
    }

    // take in command
    ss >> input;

    size_t nonDigit = input.find_first_not_of("0123456789");
    multiplier = 1;

    // Check if there was a multiplier
    if (nonDigit < input.size())
    {
        command = findSimilarCommand(input.substr(nonDigit, input.length()));
    }
    else
    {
        command = findSimilarCommand(input);
    }

    // Check if there was a multiplier, if so, set multiplier
    if (isdigit(input[0]))
    {
        multiplier = stoi(input.substr(0, nonDigit));
    }

    // Print command and multiplier
    cout << "Command: " << command << " Multiplier: " << multiplier << endl;
}

// Loads a sequence of pieces from a file
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

// Loads a command sequence from a file
void loadCommandSequence(std::stringstream &ss, std::ifstream &file)
{
    std::string line;
    if (ss.eof() || ss.str().empty())
    {
        getline(file, line);
        ss.str(line);
        ss.clear();
    }
    while (getline(file, line))
    {
        ss << " " << line;
    }
}
