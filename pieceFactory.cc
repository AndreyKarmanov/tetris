#include "pieceFactory.h"
#include "piece.h"
#include <cstdlib>

PieceFactory::PieceFactory(std::string sequence, bool random, int seed) : random{random}, seed{seed}
{
    updatePieces(sequence);
}

PieceFactory::~PieceFactory() {}

Piece *PieceFactory::createPiece(char type, int level)
{
    switch (type)
    {
    case 'I':
        return new Piece({{false, false, false, false},
                          {false, false, false, false},
                          {false, false, false, false},
                          {true, true, true, true}},
                         level, 0, 'I');
    case 'J':
        return new Piece({{false, false, false},
                          {true, true, true},
                          {false, false, true}},
                         level, 1, 'J');
    case 'L':
        return new Piece({{false, false, false},
                          {true, true, true},
                          {true, false, false}},
                         level, 2, 'L');
    case 'O':
        return new Piece({{true, true},
                          {true, true}},
                         level, 3, 'O');
    case 'S':
        return new Piece({{false, false, false},
                          {false, true, true},
                          {true, true, false}},
                         level, 4, 'S');
    case 'Z':
        return new Piece({{false, false, false},
                          {true, true, false},
                          {false, true, true}},
                         level, 5, 'Z');
    case 'T':
        return new Piece({{false, false, false},
                          {true, true, true},
                          {false, true, false}},
                         level, 6, 'T');
    default:
        return nullptr;
    }
}

void PieceFactory::updatePieces(std::string sequence)
{
    pieces.clear();
    for (auto c : sequence)
    {
        pieces.push_back(c);
    }
    currentPiece = 0;
}

void PieceFactory::updateRandom(bool random)
{
    this->random = random;
}

Piece *PieceFactory::getPiece(int level)
{
    if (random)
    {
        return createPiece(pieces[rand() % pieces.size()], level);
    }
    else
    {
        return createPiece(pieces[currentPiece++ % pieces.size()], level);
    }
}