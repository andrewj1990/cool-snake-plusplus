#include "stdafx.h"
#include "Snake.h"
#include "FloodFill.h"
#include "PathFinder.h"

Snake::Snake()
    : m_httpRequest("http://ptsv2.com", 80)
{
}

Snake::~Snake()
{
}

void Snake::Run()
{
    BoardMatrix board = 
    {
        { 0, 5, 1, 0 },
        { 0, 5, 0, 0 },
        { 0, 5, 0, 1 },
        { 0, 0, 0, 0 },
    };

    int area = FloodFill::Flood(3, 2, board);

    Node start(0, 0);
    Node current(start);
    Node end(3, 1);
    PathFinder::AStar(start, end, board);

    std::cout << "area : " << area << "\n";

    for (;;)
    {
        //std::string output = m_httpRequest.Post("/t/d3nyp-1519620552/post", "name=tester&name2=teasdas");
        //std::string output2 = m_httpRequest.Get("/t/d3nyp-1519620552/");

        //std::cout << "output : \n" << output << "\n";
        //std::cout << "output2 : \n" << output2 << "\n";

        DrawBoard(current, board);

        current = PathFinder::AStar(current, end, board);

        std::cin.get();
    }
}

void Snake::DrawBoard(const Node& node, BoardMatrix& board)
{
    board[node.y][node.x] = 2;
    for (const auto& row : board)
    {
        for (const int col : row)
        {
            std::cout << col << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
    board[node.y][node.x] = 0;
}
