#pragma once

#include "Node.h"

struct Utils
{
    static bool IsValidPosition(int row, int col, const BoardMatrix& board);
    static bool IsValidPosition(const Node& node, const BoardMatrix& board);
};