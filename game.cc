#include "game.h"
#include "gameSubject.h"
#include "piece.h"
#include "pieceFactory.h"
#include "gameBoard.h"
#include "blindBoard.h"
#include <algorithm>

// Constructor
// Initializes the game with the given level, rows, cols, name, and sequence of pieces
Game::Game(std::string name, int level, int rows, int cols, bool random, int seed, std::string sequence)
    : GameSubject{level, rows, cols, name}, player{player}, factory{new PieceFactory{sequence, random, seed}},
      blindBoard{new BlindBoard(board, 6, 2, 9, 6)}, gameOver{false}, heavyAttack{false}, splitting{false}, blind{false}, heavyPieces{false}, dropsSinceClear{0},
      lastClearCount{0}, level0Seq{sequence}
{
    // Initializes the level and creates the first piece
    setLevel(level);
    newPiece();
}

// Destructor
Game::~Game()
{
    // Deletes all the pieces, including the current piece
    for (auto p : oldPieces)
    {
        delete p;
    }
    if (currentPiece)
    {
        delete currentPiece;
    }

    // Deletes the factory
    delete factory;
}

// Returns the last amount of lines cleared
int Game::getLastClearCount() const
{
    return lastClearCount;
}

// Returns the game over flag
bool Game::getGameOver()
{
    return gameOver;
}

// Moves the current piece right or left by the given amount
// Recursively calls itself if the piece is heavy
void Game::move(int right, int down, bool recurCall)
{

    // Checks if the piece can move in the given direction
    if (board->intersects(currentPiece, row + down, col + right))
    {
        // Performs drop if the move was called due to heavyAttack
        if (heavyAttack && recurCall && down == 1)
        {
            drop();
        }
        return;
    }

    // Erases the piece from the board
    board->erasePiece(currentPiece, row, col);

    // Updates the row and col
    row += down;
    col += right;

    // Draws the piece on the board, in the new position
    board->drawPiece(currentPiece, row, col);

    // Performs a down move if piece is heavy
    if (currentPiece->isHeavy() && !recurCall)
    {
        move(0, 1, true);
    }

    // Performs a down move if under heavyAttack
    if (heavyAttack && !recurCall && down == 0)
    {
        move(0, 1, true);
    }
}

// Drops the current piece to the bottom of the board
void Game::drop()
{
    // Moves the piece down until it intersects with the board
    while (!board->intersects(currentPiece, row + 1, col))
    {
        // Erases the piece from the board before moving it down
        board->erasePiece(currentPiece, row, col);

        // Moves the piece down and draws it on the board
        board->drawPiece(currentPiece, ++row, col);
    }

    // Saves the piece to the oldPieces vector, for later deletion
    oldPieces.push_back(currentPiece);

    // CLears the lines and updates the score
    clearlines();

    // Checks if splitting is enabled, and if so, places splitting piece when appropriate
    if (splitting && ++dropsSinceClear % 5 == 0)
    {
        // Creates and places the splitting piece
        currentPiece = factory->getPiece('*', level, heavyPieces);
        col = (board->getCols() - currentPiece->getWidth()) / 2;
        row = 0;

        // Checks for a game over
        if (board->intersects(currentPiece, row, col))
        {
            gameOver = true;
            return;
        }

        // Drops the piece
        drop();
    }
    else
    {
        // Creates a new piece
        newPiece();
    }

    // Removes effects of heavy attack and blind
    blind = false;
    heavyAttack = false;
}

// Rotates the current piece clockwise
void Game::rotateCW()
{
    // Erases the piece from the board
    board->erasePiece(currentPiece, row, col);

    // Rotates the piece clockwise
    currentPiece->rotateCW();

    // Checks if the piece intersects with the board
    if (board->intersects(currentPiece, row, col))
    {
        // Rotates the piece back if it intersects
        currentPiece->rotateCCW();
    }

    // Draws the piece on the board
    board->drawPiece(currentPiece, row, col);

    // Performs a down move if piece is heavy
    if (currentPiece->isHeavy())
    {
        move(0, 1);
    };
}

// Rotates the current piece counter-clockwise
void Game::rotateCCW()
{
    // Erases the piece from the board
    board->erasePiece(currentPiece, row, col);

    // Rotates the piece counter-clockwise
    currentPiece->rotateCCW();

    // Checks if the piece intersects with the board
    if (board->intersects(currentPiece, row, col))
    {
        // Rotates the piece back if it intersects
        currentPiece->rotateCW();
    }

    // Draws the piece on the board
    board->drawPiece(currentPiece, row, col);

    // Performs a down move if piece is heavy
    if (currentPiece->isHeavy())
    {
        move(0, 1);
    };
}

// Creates a new piece and places it on the board
void Game::newPiece()
{
    // Checks if the next piece is null, and if so, creates a new one
    if (nextPiece == nullptr)
    {
        nextPiece = factory->getPiece(level, heavyPieces);
    }

    // Sets the current piece to the next piece, and creates a new next piece
    currentPiece = nextPiece;
    nextPiece = factory->getPiece(level, heavyPieces);

    // Places the piece in the middle of the board, right below reserved rows
    col = (board->getCols() - currentPiece->getWidth()) / 2;
    row = std::min(0, 4 - currentPiece->getHeight());

    // Checks for a game over
    if (board->intersects(currentPiece, row, col))
    {
        gameOver = true;
    }

    // draws the piece on the board
    board->drawPiece(currentPiece, row, col);
}

// Sets the level of the game
void Game::setLevel(int level)
{

    // Sets the level to the given level, or the closest valid level
    level = std::min(4, std::max(0, level));
    this->level = level;

    // Sets default values for heavy pieces and splitting
    factory->setRandom(true);
    heavyPieces = splitting = false;

    // Updates the pieces in the factory, based on the level
    // Also sets heavy pieces and splitting if appropriate
    if (level == 0)
    {
        factory->updatePieces(level0Seq);
        factory->setRandom(false);
    }
    if (level == 1)
    {
        factory->updatePieces("IJLOTIJLOTSZ");
    }
    else if (level == 2)
    {
        factory->updatePieces("IJLOTSZ");
    }
    else if (level >= 3)
    {
        factory->updatePieces("IJLOTSZSZ");
        heavyPieces = true;
    }
    if (level >= 4)
    {
        splitting = true;
    }
}

// Replaces current piece with piece of given type
void Game::setPiece(char type)
{
    // Checks if the piece is valid, and if so, replaces the current piece
    Piece *temp = factory->getPiece(type, level, heavyPieces);
    if (temp = nullptr)
    {
        delete temp;
        return;
    }

    // Removes the current piece from the board
    board->erasePiece(currentPiece, row, col);
    delete currentPiece;

    // Sets the current piece to the new piece
    currentPiece = temp;

    // Places the piece in the middle of the board, right below reserved rows
    col = (board->getCols() - currentPiece->getWidth()) / 2;
    row = std::min(0, 4 - currentPiece->getHeight());

    // Checks for a game over
    if (board->intersects(currentPiece, row, col))
    {
        gameOver = true;
    }
    board->drawPiece(currentPiece, row, col);
}

// Sets the heavy attack flag
void Game::setHeavy(bool heavy)
{
    this->heavyAttack = heavy;
}

// Sets the blind flag
void Game::setBlind(bool blind)
{
    this->blind = blind;
}

// Sets the random flag
void Game::setRandom()
{
    factory->setRandom(true);
}

// Sets the sequence of pieces
void Game::setSequence(std::string sequence)
{
    factory->updatePieces(sequence);
    factory->setRandom(false);
}

// Returns the current board, or the board decorated with effects
GameBoard *Game::getBoard() const
{
    if (blind)
    {
        return blindBoard;
    }
    return board;
}

// Restarts the game
void Game::restart()
{
    // Clears the pieces on the board
    board->clear();

    // Deletes all old pieces
    for (auto p : oldPieces)
    {
        delete p;
    }
    oldPieces.clear();

    // Deletes the current piece
    if (currentPiece)
    {
        delete currentPiece;
    }

    // Resets all values
    currentPiece = nullptr;
    gameOver = false;
    dropsSinceClear = 0;
    lastClearCount = 0;
    score = 0;
    setLevel(0);
    newPiece();
}

// Clears lines on the board and updates the score
void Game::clearlines()
{
    // Checks number of lines cleared
    int lines = 0;

    // Checks for full lines
    for (int i = 0; i < board->getRows(); ++i)
    {
        bool full = true;
        for (int j = 0; j < board->getCols(); ++j)
        {
            if (board->getPiece(i, j) == nullptr)
            {
                full = false;
                break;
            }
        }

        // Clears the line if it is full
        if (full)
        {

            // Loops through full line, clearing and adding it to score.
            for (int j = 0; j < board->getCols(); ++j)
            {

                // Gets the piece at the square
                Piece *p = board->getPiece(i, j);

                // Checks if entire piece is cleared
                if (p->chSize(p->getSize() - 1) == 0)
                {
                    score += (p->getLevel() + 1) * (p->getLevel() + 1);
                }

                // Erases the square from the board
                board->setPiece(nullptr, i, j);
            }

            // Moves all pieces above the cleared line down
            for (int k = i; k > 0; --k)
            {
                for (int j = 0; j < board->getCols(); ++j)
                {
                    board->setPiece(board->getPiece(k - 1, j), k, j);
                }
            }

            // Decrements i to check the new line at the same index
            --i;

            // Increments the number of lines cleared
            ++lines;
        }
    }

    // Updates the score
    if (lines > 0)
    {
        score += (level + lines) * (level + lines);
        dropsSinceClear = 0;
    }

    // Updates high score
    if (score > highScore)
    {
        highScore = score;
    }

    // Records number of lines cleared
    lastClearCount = lines;
}