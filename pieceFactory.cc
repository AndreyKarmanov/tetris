#include "pieceFactory.h"
#include "piece.h"
#include <cstdlib>

PieceFactory::PieceFactory(std::string sequence, bool random, int seed) : random{random}, seed{seed}
{
    updatePieces(sequence);
}

PieceFactory::~PieceFactory() {}

Piece *PieceFactory::getPiece(char type, int level, bool heavy)
{
    switch (type)
    {
    case 'I':
        return new Piece({{false, false, false, false},
                          {false, false, false, false},
                          {false, false, false, false},
                          {true, true, true, true}},
                         level, 1, 'I', heavy);
    case 'J':
        return new Piece({{false, false, false},
                          {true, false, false},
                          {true, true, true}},
                         level, 2, 'J', heavy);
    case 'L':
        return new Piece({{false, false, false},
                          {false, false, true},
                          {true, true, true}},
                         level, 3, 'L', heavy);
    case 'O':
        return new Piece({{true, true},
                          {true, true}},
                         level, 4, 'O', heavy);
    case 'S':
        return new Piece({{false, false, false},
                          {false, true, true},
                          {true, true, false}},
                         level, 5, 'S', heavy);
    case 'Z':
        return new Piece({{false, false, false},
                          {true, true, false},
                          {false, true, true}},
                         level, 6, 'Z', heavy);
    case 'T':
        return new Piece({{false, false, false},
                          {true, true, true},
                          {false, true, false}},
                         level, 7, 'T', heavy);
    case '*':
        return new Piece({{true}},
                         level, 8, '*', heavy);
    default:
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