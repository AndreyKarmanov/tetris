#ifndef PIECEFACTORY_H
#define PIECEFACTORY_H

#include <vector>
#include <string>
#include <fstream>
#include "piece.h"

// PieceFactory is a factory class that creates pieces
class PieceFactory
{
private:

    // Stores the sequence of pieces to be created, if random is false
    std::vector<char> pieces;
    // Stores whether the pieces should be created randomly
    bool random;

    // Stores the index of the next piece to be created
    int currentPiece;

    // Stores the seed for the random number generator
    int seed;

    static std::vector<Piece*> customPieceList;
public:

    // Constructor
    PieceFactory(std::string sequence, bool random, int seed);
    ~PieceFactory();

    // Updates the sequence of pieces to be created 
    void updatePieces(std::string sequence);

    // add a custom pieces to the list
    static void addPieces(std::ifstream &filename);

    // Sets whether the pieces should be created randomly
    void setRandom(bool random);

    // Returns the next piece to be created
    Piece *getPiece(int level, bool heavy);

    // Returns the next piece to be created, given the type
    static Piece *getPiece(char type, int level, bool heavy);
};

#endif
