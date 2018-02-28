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
            int newCost = costSoFar[current] + board[next.y][next.x];
            if (costSoFar.find(next) == costSoFar.end() || newCost < costSoFar[next])
            {
                costSoFar[next] = newCost;
                int priority = newCost + Heuristic(next, start);
                frontier.emplace(priority, next);
                cameFrom[next] = current;
            }
        }
    }


    return cameFrom[start];
}

int PathFinder::Heuristic(const Node& a, const Node& b)
{
    float dx = std::abs(static_cast<float>(a.x) - static_cast<float>(b.x));
    float dy = std::abs(static_cast<float>(a.y) - static_cast<float>(b.y));

    float D = 1.0f;
    float D2 = 1.0f;

    return static_cast<int>(D * (dx + dy) + (D2 - 2 * D) * std::fminf(dx, dy));
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
