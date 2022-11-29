#ifndef PIECEFACTORY_H
#define PIECEFACTORY_H

#include <vector>
#include <string>
#include "piece.h"

class PieceFactory
{
private:
    std::vector<char> pieces;
    bool random;
    int currentPiece;
    int seed;

public:
    PieceFactory(std::string sequence, bool random, int seed);
    ~PieceFactory();

    void updatePieces(std::string sequence);
    void updateRandom(bool random);

    Piece *getPiece(int level);
    static Piece *getPiece(char type, int level);
};

#endif
