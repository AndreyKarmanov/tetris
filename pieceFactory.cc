#include "pieceFactory.h"
#include "piece.h"
#include <cstdlib>
#include <sstream>
#include <iostream>

std::vector<Piece *> PieceFactory::customPieceList = std::vector<Piece *>();

PieceFactory::PieceFactory(std::string sequence, bool random, int seed) : random{random}, seed{seed}
{
    updatePieces(sequence);
}

PieceFactory::~PieceFactory()
{
    for (auto p : PieceFactory::customPieceList)
    {
        delete p;
    }
}

Piece *PieceFactory::getPiece(char type, int level, bool heavy)
{
    switch (type)
    {
    case 'I':
        return new Piece({{false, false, false, false},
                          {false, false, false, false},
                          {false, false, false, false},
                          {true, true, true, true}},
                         level, 4, 'I', heavy);
    case 'J':
        return new Piece({{false, false, false},
                          {true, false, false},
                          {true, true, true}},
                         level, 3, 'J', heavy);
    case 'L':
        return new Piece({{false, false, false},
                          {false, false, true},
                          {true, true, true}},
                         level, 8, 'L', heavy);
    case 'O':
        return new Piece({{true, true},
                          {true, true}},
                         level, 6, 'O', heavy);
    case 'S':
        return new Piece({{false, false, false},
                          {false, true, true},
                          {true, true, false}},
                         level, 3, 'S', heavy);
    case 'Z':
        return new Piece({{false, false, false},
                          {true, true, false},
                          {false, true, true}},
                         level, 2, 'Z', heavy);
    case 'T':
        return new Piece({{false, false, false},
                          {true, true, true},
                          {false, true, false}},
                         level, 7, 'T', heavy);
    case '*':
        return new Piece({{true}},
                         level, 8, '*', heavy);
    default:
        // find the custom piece
        for (auto p : PieceFactory::customPieceList)
        {
            if (p->getType() == type)
            {
                return new Piece(*p, level, heavy);
            }
        }
        return nullptr; // can add extra pieces here
    }
}

// Updates the sequence of pieces to be created
void PieceFactory::updatePieces(std::string sequence)
{
    // Clear the sequence of pieces
    pieces.clear();
    // Add the new sequence of pieces
    for (auto c : sequence)
    {
        pieces.push_back(c);
    }
    // Reset the index of the next piece to be created
    currentPiece = 0;
}

void PieceFactory::addPieces(std::ifstream &in)
{
    using namespace std;
    string line;
    stringstream ss;
    while (getline(in, line))
    {
        ss.str(line);
        ss.clear();
        char type;
        int gridSize;

        ss >> line >> type >> line >> gridSize;
        if (ss.fail())
        {
            return;
        }

        vector<vector<bool>> grid(gridSize, vector<bool>(gridSize, false));
        for (int i = 0; i < gridSize; i++)
        {
            getline(in, line);
            ss.str(line);
            ss.clear();
            int c;
            for (int j = 0; j < gridSize; j++)
            {
                ss >> c;
                if (c == 1)
                {
                    grid[i][j] = true;
                }
            }
        }
        // print grid
        for (int i = 0; i < gridSize; i++)
        {
            for (int j = 0; j < gridSize; j++)
            {
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }

        PieceFactory::customPieceList.push_back(new Piece(grid, 0, 0, type, false));
    }
}

// Sets whether the pieces should be created randomly
void PieceFactory::setRandom(bool random)
{
    this->random = random;
}

// Returns the next piece to be created
Piece *PieceFactory::getPiece(int level, bool heavy)
{
    if (random)
    {
        // If random is true, create a random piece
        return getPiece(pieces[rand() % pieces.size()], level, heavy);
    }
    else
    {
        // Return next piece in sequence
        // If the sequence of pieces has been exhausted, start over
        return getPiece(pieces[currentPiece++ % pieces.size()], level, heavy);
    }
}
