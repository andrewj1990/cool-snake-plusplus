//https://www.redblobgames.com/pathfinding/a-star/implementation.html

#include "stdafx.h"
#include "PathFinder.h"
#include "Utils.h"

#include <queue>
#include <functional>
#include <unordered_map>

Node PathFinder::AStar(const Node& start, const Node& end, const BoardMatrix& board)
{
    using PQNode = std::pair<int, Node>;
    
    Node node(end);
    std::priority_queue<PQNode, std::vector<PQNode>, std::greater<PQNode>> frontier;
    std::unordered_map<Node, Node, NodeHasher> cameFrom;
    std::unordered_map<Node, int, NodeHasher> costSoFar;

    frontier.emplace(0, node);

    cameFrom[end] = end;
    costSoFar[end] = 0;

    while (!frontier.empty())
    {
        Node current = frontier.top().second;
        frontier.pop();

        if (current == start)
            break;

        std::vector<Node> neighbors = GetNeighbors(current, board);
        for (const Node& next : neighbors)
        {
            int newCost = costSoFar[current] + (board[next.y][next.x] * 5000) + 10;
            if (costSoFar.find(next) == costSoFar.end() || newCost < costSoFar[next])
            {
                costSoFar[next] = newCost;

                int dx1 = next.x - start.x;
                int dy1 = next.y - start.y;
                int dx2 = end.x - start.x;
                int dy2 = end.y - start.y;
                int cross = static_cast<int>(std::abs(dx1 * dy2 - dx2 * dy1) * 0.0001);

                int priority = newCost + Heuristic(next, start) * cross;
                frontier.emplace(priority, next);
                cameFrom[next] = current;
            }
        }
    }


#if 0
    auto tempBoard(board);

    Node v(start);
    while (1)
    {
        if (v == end)
            break;
        Node n = cameFrom[v];
        tempBoard[n.y][n.x] = 7;
        v = n;
    }

    for (const auto& row : tempBoard)
    {
        for (const int col : row)
        {
            std::cout << col << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
#endif

    return cameFrom[start];
}

int PathFinder::Heuristic(const Node& node, const Node& goal)
{
    //float dx = std::abs(static_cast<float>(node.x) - static_cast<float>(goal.x));
    //float dy = std::abs(static_cast<float>(node.y) - static_cast<float>(goal.y));

    //float D = 1.0f;
    //float D2 = 1.0f;

    //return static_cast<int>(D * (dx + dy) + (D2 - 2 * D) * std::fminf(dx, dy));

    int dx = abs(node.x - goal.x);
    int dy = abs(node.y - goal.y);
    return 1 * (dx + dy);
}

std::vector<Node> PathFinder::GetNeighbors(const Node& currentLocation, const BoardMatrix& board)
{
    std::vector<Node> neighbors;
    neighbors.reserve(4);

    Node left(currentLocation.x - 1, currentLocation.y);
    Node right(currentLocation.x + 1, currentLocation.y);
    Node top(currentLocation.x, currentLocation.y - 1);
    Node bottom(currentLocation.x, currentLocation.y + 1);

    if (Utils::IsValidPosition(left, board))
        neighbors.push_back(left);
    if (Utils::IsValidPosition(right, board))
        neighbors.push_back(right);
    if (Utils::IsValidPosition(top, board))
        neighbors.push_back(top);
    if (Utils::IsValidPosition(bottom, board))
        neighbors.push_back(bottom);

    return neighbors;
}
