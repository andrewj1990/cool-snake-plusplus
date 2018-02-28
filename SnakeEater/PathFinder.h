#pragma once

#include "Node.h"
#include "Defines.h"

enum class Direction
{
    LEFT = 0,
    UP,
    RIGHT,
    DOWN
};

class PathFinder
{
    PathFinder() { }
    ~PathFinder() { }
public:

    static Node AStar(const Node& start, const Node& end, const BoardMatrix& board);

private:
    static int Heuristic(const Node& node, const Node& goal);
    static std::vector<Node> GetNeighbors(const Node& currentLocation, const BoardMatrix& board);

};