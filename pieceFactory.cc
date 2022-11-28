#include "pieceFactory.h"
#include "piece.h"
#include <cstdlib>

PieceFactory::PieceFactory(std::vector<Piece *> pieces, bool random, int seed) : pieces{pieces}, random{random}, seed{seed} {}

PieceFactory::~PieceFactory() {}

void PieceFactory::updatePieces(std::vector<Piece *> Pieces) {
    pieces = Pieces;
}

void PieceFactory::updateRandom(bool random) {
    this->random = random;
}

// fix random generations, add level generation
Piece *PieceFactory::getPiece(int level) {
    if (random) {
        return new Piece(*pieces[rand() % pieces.size()], level);
    } else {
        return new Piece(*pieces[++currentPiece % pieces.size()], level);
    }
}

Piece *PieceFactory::getPiece(char type, int level) {
    for (auto piece : pieces) {
        if (piece->getType() == type) {
            return new Piece(*piece, level);
        }
    }
    return nullptr;
}
