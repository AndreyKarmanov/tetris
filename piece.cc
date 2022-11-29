#include "piece.h"
Piece::Piece(std::vector<std::vector<bool>> grid, int level, int colour, char type) : grid{grid}, colour{colour}, type{type}, level{level}
{
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

Piece::Piece(const Piece &other, int level) : width{other.width}, height{other.height}, grid{other.grid}, colour{other.colour}, type{other.type}, level{level}, size{other.size} {}

Piece::~Piece() {}

std::vector<std::vector<bool>> Piece::getGrid() const
{
    return grid;
}

int Piece::getLevel() const
{
    return level;
}

int Piece::getColour() const
{
    return colour;
}

char Piece::getType() const
{
    return type;
}

int Piece::getWidth() const
{
    return width;
}

int Piece::getHeight() const
{
    return height;
}

int Piece::getSize() const
{
    return size;
}

void Piece::rotateCW()
{
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
}

void Piece::rotateCCW()
{
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
}

int Piece::chSize(int size)
{
    return this->size = size;
}