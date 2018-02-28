#pragma once

struct Node
{
    Node()
        : x(0), y(0)
    { }

    Node(int px, int py)
        : x(px), y(py)
    { }

    // TODO: fix tie priority queue tie breakers.. 
    //       maybe get calculate the distance between end node with the current and other node
    bool operator<(const Node& other) const
    {
        return false;
    }

    bool operator==(const Node& other) const
    {
        return (x == other.x && y == other.y);
    }

    int x;
    int y;
};

struct NodeHasher
{
    std::size_t operator()(const Node& node) const
    {
        return std::hash<int>()(node.x) ^ (std::hash<int>()(node.y) << 1);
    }
};
