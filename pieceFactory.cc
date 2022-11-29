#include "pieceFactory.h"
#include "piece.h"
#include <cstdlib>

PieceFactory::PieceFactory(std::string sequence, bool random, int seed) : random{random}, seed{seed}
{
    updatePieces(sequence);
}

PieceFactory::~PieceFactory() {
    for (auto p : pieces) {
        delete p;
    }
}

void PieceFactory::updatePieces(std::string sequence)
{
    using namespace std;
    vector<vector<bool>> Igrid =
        {{false, false, false, false},
         {false, false, false, false},
         {false, false, false, false},
         {true, true, true, true}};
    Piece *Ipiece = new Piece(Igrid, 0, 0, 'I');
    vector<vector<bool>> Jgrid =
        {{false, false, false},
         {true, true, true},
         {false, false, true}};
    Piece *Jpiece = new Piece(Jgrid, 0, 0, 'J');
    vector<vector<bool>> Lgrid =
        {{false, false, false},
         {true, true, true},
         {true, false, false}};
    Piece *Lpiece = new Piece(Lgrid, 0, 0, 'L');
    vector<vector<bool>> Ogrid =
        {{true, true},
         {true, true}};
    Piece *Opiece = new Piece(Ogrid, 0, 0, 'O');
    vector<vector<bool>> Sgrid =
        {{false, false, false},
         {false, true, true},
         {true, true, false}};
    Piece *Spiece = new Piece(Sgrid, 0, 0, 'S');
    vector<vector<bool>> Tgrid =
        {{false, false, false},
         {true, true, true},
         {false, true, false}};
    Piece *Tpiece = new Piece(Tgrid, 0, 0, 'T');
    vector<vector<bool>> Zgrid =
        {{false, false, false},
         {true, true, false},
         {false, true, true}};
    Piece *Zpiece = new Piece(Zgrid, 0, 0, 'Z');
    pieces = {Ipiece, Jpiece, Lpiece, Opiece, Spiece, Tpiece, Zpiece};
}

void PieceFactory::updateRandom(bool random)
{
    this->random = random;
}

// fix random generations, add level generation
Piece *PieceFactory::getPiece(int level)
{
    if (random)
    {
        return new Piece(*pieces[rand() % pieces.size()], level);
    }
    else
    {
        return new Piece(*pieces[++currentPiece % pieces.size()], level);
    }
}

Piece *PieceFactory::getPiece(char type, int level)
{
    for (auto piece : pieces)
    {
        if (piece->getType() == type)
        {
            return new Piece(*piece, level);
        }
    }
    return nullptr;
}
