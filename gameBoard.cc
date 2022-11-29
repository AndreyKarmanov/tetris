#include "gameBoard.h"

GameBoard::GameBoard(int rows, int cols) : rows{rows}, cols{cols}, board{std::vector<std::vector<Piece *>>(rows, std::vector<Piece *>(cols, nullptr))} {}

GameBoard::~GameBoard() {}

int GameBoard::getRows() { return rows; }

int GameBoard::getCols() { return cols; }

void GameBoard::setPiece(Piece *piece, int row, int col) { board[row][col] = piece; }

Piece *GameBoard::getPiece(int row, int col) { return board[row][col]; }
