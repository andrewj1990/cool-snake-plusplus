#pragma once

#include <vector>

#include "Defines.h"

class FloodFill
{
private:
    FloodFill() { }
    ~FloodFill() { }

public:
    static int Flood(int row, int col, const BoardMatrix& board);

private:
    static bool IsValidPosition(int row, int col, const BoardMatrix& board);
    static bool IsVisited(int row, int col, const BoardMatrix& visited);
    static void AddCoordinate(std::vector<std::pair<int, int>>& coords, int row, int col, const BoardMatrix& visited);
};