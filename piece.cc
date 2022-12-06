#include "piece.h"

// Constructor
Piece::Piece(std::vector<std::vector<bool>> grid, int level, int colour, char type, bool heavy) : grid{grid}, colour{colour}, type{type}, level{level}, heavy{heavy}
{
    // Calculate the size of the piece
    for (auto row : grid)
    {
        for (auto cell : row)
        {
            if (cell)
            {
                size++;
            }
        }
    }

    // Calculate the width and height of the piece
    height = grid.size();
    if (height > 0)
    {
        width = grid[0].size();
    }
    else
    {
        width = 0;
    }
}

// Destructor
Piece::~Piece() {}

// Returns the piece shape grid
std::vector<std::vector<bool>> Piece::getGrid() const
{
    return grid;
}

// Returns the level of the piece
int Piece::getLevel() const
{
    return level;
}

// Returns the colour of the piece
int Piece::getColour() const
{
    return colour;
}

// Returns the type of the piece
char Piece::getType() const
{
    return type;
}

// Returns the width of the piece
int Piece::getWidth() const
{
    return width;
}

// Returns the height of the piece
int Piece::getHeight() const
{
    return height;
}

// Returns the size of the piece
int Piece::getSize() const
{
    return size;
}

// Returns whether the piece is heavy
bool Piece::isHeavy() const
{
    return heavy;
}

// Moves the piece to the bottom left corner of piece shape grid, used for rotation
void Piece::forceBottomLeft()
{
    // Find the bottom left corner of the piece
    int emptyLeftCols = width - 1;
    int emptyBottomRows = height - 1;
    for (int row = height - 1; row >= 0; --row)
    {
        for (int col = 0; col <= emptyLeftCols; ++col)
        {
            if (grid[row][col])
            {
                emptyLeftCols = col;
                if (emptyBottomRows == height - 1)
                {
                    emptyBottomRows = height - row - 1;
                }
                break;
            }
        }
    }

    // Move the piece to the bottom left corner
    if (emptyBottomRows > 0 || emptyLeftCols > 0)
    {
        std::vector<std::vector<bool>> newGrid(emptyBottomRows, std::vector<bool>(width, false));
        for (int row = 0; row < height - emptyBottomRows; ++row)
        {
            std::vector<bool> newRow;
            for (int i = emptyLeftCols; i < width; ++i)
            {
                newRow.push_back(grid[row][i]);
            }
            for (int i = 0; i < emptyLeftCols; ++i)
            {
                newRow.push_back(false);
            }
            newGrid.push_back(newRow);
        }
        grid = newGrid;
    }
}

// Rotates the piece clockwise
void Piece::rotateCW()
{
    // Create a new grid and rotate the piece
    std::vector<std::vector<bool>> newGrid;
    for (int i = 0; i < width; ++i)
    {
        std::vector<bool> row;
        for (int j = height - 1; j >= 0; --j)
        {
            row.push_back(grid[j][i]);
        }
        newGrid.push_back(row);
    }
    grid = newGrid;
    int temp = width;
    width = height;
    height = temp;
    forceBottomLeft();
}

// Rotates the piece counter-clockwise
void Piece::rotateCCW()
{
    // Create a new grid and rotate the piece
    std::vector<std::vector<bool>> newGrid;
    for (int i = width - 1; i >= 0; --i)
    {
        std::vector<bool> row;
        for (int j = 0; j < height; ++j)
        {
            row.push_back(grid[j][i]);
        }
        newGrid.push_back(row);
    }
    grid = newGrid;
    int temp = width;
    width = height;
    height = temp;
    forceBottomLeft();
}

// Changes the size of the piece
int Piece::chSize(int size)
{
    return this->size = size;
}
