#include "stdafx.h"
#include "Utils.h"

bool Utils::IsValidPosition(int row, int col, const BoardMatrix& board)
{
    if (row >= 0 && row < static_cast<int>(board.size()))
        if (col >= 0 && col < static_cast<int>(board.front().size()))
            return true;

    return false;
}

bool Utils::IsValidPosition(const Node& node, const BoardMatrix& board)
{
    return IsValidPosition(node.x, node.y, board);
}
