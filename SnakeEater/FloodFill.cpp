#include "stdafx.h"
#include "FloodFill.h"


int FloodFill::Flood(int row, int col, const BoardMatrix& board)
{
    std::vector<std::vector<int>> visited(board);
    std::vector<std::pair<int, int>> coords;
    coords.reserve(board.size() * board.size());

    coords.push_back({ row, col });
    int count = 0;
    while (!coords.empty())
    {
        const auto& coord = coords.front();
        int curRow = coord.first;
        int curCol = coord.second;

        // check if the current coordinate is valid
        if (!IsVisited(curRow, curCol, visited))
        {
            AddCoordinate(coords, curRow - 1, curCol, visited); // left
            AddCoordinate(coords, curRow + 1, curCol, visited); // right
            AddCoordinate(coords, curRow, curCol - 1, visited); // bottom
            AddCoordinate(coords, curRow, curCol + 1, visited); // top

            count++;
            visited[curRow][curCol] = 1;
        }

        coords.erase(coords.begin());
    }

    return count;
}

bool FloodFill::IsValidPosition(int row, int col, const BoardMatrix& board)
{
    if (row >= 0 && row < static_cast<int>(board.size()))
        if (col >= 0 && col < static_cast<int>(board.front().size()))
            return true;

    return false;
}

bool FloodFill::IsVisited(int row, int col, const BoardMatrix& visited)
{
    if (IsValidPosition(row, col, visited))
    {
        return (visited[row][col] != 0);
    }
    return true;
}

void FloodFill::AddCoordinate(std::vector<std::pair<int, int>>& coords, int row, int col, const BoardMatrix& visited)
{
    if (!IsVisited(row, col, visited))
        coords.push_back({ row, col });
}

