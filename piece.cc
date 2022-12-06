#include "piece.h"
Piece::Piece(std::vector<std::vector<bool>> grid, int level, int colour, char type, bool heavy) : grid{grid}, colour{colour}, type{type}, level{level}, heavy{heavy}
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

bool Piece::isHeavy() const
{
    return heavy;
}

void Piece::forceBottomLeft()
{
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
    forceBottomLeft();
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
    forceBottomLeft();
}

int Piece::chSize(int size)
{
    return this->size = size;
}