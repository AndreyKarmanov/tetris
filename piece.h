#ifndef PIECE_H
#define PIECE_H

#include <vector>

class Piece
{
private:
    // Dimensions
    int width, height;

    // Piece Shape, stored as a 2D vector of booleans
    std::vector<std::vector<bool>> grid;

    // Piece properties for display
    const int colour;
    const char type;

    // Piece properties for gameplay
    const int level;
    int size;
    bool heavy;

    // Moves the piece to the bottom left corner of piece shape grid, used for rotation
    void forceBottomLeft();

public:
    // Constructor & Destructor
    Piece(std::vector<std::vector<bool>> grid, int level, int colour, char type, bool heavy);
    Piece(Piece &p, int level, bool heavy);
    ~Piece();

    // Accessors
    std::vector<std::vector<bool>> getGrid() const;
    int getLevel() const;
    int getColour() const;
    char getType() const;
    int getWidth() const;
    int getHeight() const;
    int getSize() const;
    bool isHeavy() const;

    // Mutators
    void rotateCW();
    void rotateCCW();
    int chSize(int size);
};

#endif
