#include "textWrapper.h"
#include "gameSubject.h"
#include "gameBoard.h"
#include "piece.h"

#include <vector>
#include <iostream>
#include <sstream>
#include <string>

// Constructor
TextWrapper::TextWrapper(std::vector<GameSubject *> games)
{
    for (auto game : games)
    {
        observers.emplace_back(new TextObserver{game});
        game->attach(observers.back());
    }
}

// Destructor
TextWrapper::~TextWrapper()
{
    for (auto ob : observers)
    {
        delete ob;
    }
}

// Prints a string, padded to the specified length
void TextWrapper::printLine(std::string curline, int padding)
{
    std::cout << curline;
    for (int i = curline.size(); i < padding; ++i) {
        std::cout << " ";
    }
}

// Notifies all text observers of a change, but delays printing
// so the boards can later be printed side by side 
void TextWrapper::notifyAll()
{
    std::vector<std::stringstream> boards;
    // Store the generated boards in a stringstream vector instead of printing
    for (auto ob : observers)
    {
        boards.push_back(ob->generateBoard());
    }
    int boardNum = boards.size();
    std::string curline;
    while (getline(boards[0], curline)) // Get the next line of the first board
    {
        printLine(curline, 20); // Print line of first board
        // Iterate through the rest of the boards and prints a line for each of them
        for (int i = 1; i < boardNum; ++i) {
            getline(boards[i], curline);
            printLine(curline, 20);
        }
        std::cout << std::endl;
    }
}

// Constructor for TextObserver
TextWrapper::TextObserver::TextObserver(GameSubject *game) : GameObserver{game} {}

// Destructor for TextObserver
TextWrapper::TextObserver::~TextObserver() {}

// Notifies the TextObserver, but returns the output as a stringstream instead of printing
std::stringstream TextWrapper::TextObserver::generateBoard()
{
    GameBoard *board = game->getBoard();
    std::stringstream ss;
    ss << "+";
    for (int cols = 0; cols < board->getCols(); ++cols)
    {
        ss << "-";
    }
    ss << "+" << std::endl;
    ss << "| Level   : " << game->getLevel() << std::endl;
    ss << "| Score   : " << game->getScore() << std::endl;
    ss << "| Hi Score: " << game->getHighScore() << std::endl;

    ss << "+";
    for (int cols = 0; cols < board->getCols(); ++cols)
    {
        ss << "-";
    }
    ss << "+" << std::endl;
    for (int rows = 0; rows < board->getRows(); ++rows)
    {
        ss << "|";
        for (int cols = 0; cols < board->getCols(); ++cols)
        {
            Piece *p = board->getPiece(rows, cols);
            if (p != nullptr)
            {
                ss << p->getType();
            }
            else
            {
                ss << " ";
            }
        }
        ss << "|" << std::endl;
    }
    ss << "+";
    for (int cols = 0; cols < board->getCols(); ++cols)
    {
        ss << "-";
    }
    ss << "+" << std::endl;

    // Store the next piece image in a stringstream
    std::stringstream nexts;
    nexts << "Next:" << std::endl;
    Piece *np = game->getNextPiece();
    auto grid = np->getGrid();
    for (auto vec : grid)
    {
        for (auto cell : vec)
        {
            if (cell)
            {
                nexts << np->getType();
            }
            else
            {
                nexts << " ";
            }
        }
        nexts << std::endl;
    }
    // Pad extra lines if needed keep the number of lines consistent
    if (np->getType() == 'O')
    {
        nexts << std::endl;
    }
    if (np->getType() != 'I')
    {
        nexts << std::endl;
    }

    // If there is a held piece, draw the next and held pieces side by side
    if (game->getHeldPiece()) {
        std::stringstream helds;
        helds << "Held:" << std::endl;
        Piece *hp = game->getHeldPiece();
        auto grid = hp->getGrid();
        for (auto vec : grid)
        {
            for (auto cell : vec)
            {
                if (cell)
                {
                    helds << hp->getType();
                }
                else
                {
                    helds << " ";
                }
            }
            helds << std::endl;
        }

        // Iterate through the two stringsteams add them to the main ss
        std::string curline;
        while (getline(nexts, curline))
        {
            ss << curline;
            for (int i = curline.size(); i < 8; ++i)
            {
                ss << " ";
            }
            if (getline(helds, curline)) {
                ss << curline;
            }
            ss << std::endl;
        }
    }
    else {
        ss << nexts.str();
    }

    return ss;
}

// Notify the observer of a change
void TextWrapper::TextObserver::notify()
{
    std::cout << generateBoard().str();
}
