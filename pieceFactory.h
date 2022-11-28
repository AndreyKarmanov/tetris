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
    PieceFactory(std::vector<Piece *> Pieces, bool random, int seed);
    ~PieceFactory();

    void updatePieces(std::vector<Piece *> Pieces);
    void updateRandom(bool random);

    Piece *getPiece(int level);
    Piece *getPiece(char type, int level);
};

#endif
