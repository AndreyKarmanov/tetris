#ifndef PIECEFACTORY_H
#define PIECEFACTORY_H

#include <vector>
#include "piece.h"

class PieceFactory
{
private:
    std::vector<Piece *> pieces;
    bool random;
    int currentPiece;
    int seed;

public:
    PieceFactory(int level, bool random, int seed);
    ~PieceFactory();

    void updatePieces(int level);
    void updateRandom(bool random);

    Piece *getPiece(int level);
    Piece *getPiece(char type, int level);
};

#endif
