#include "stdafx.h"
#include "Snake.h"
#include "FloodFill.h"

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
        { 0, 0, 1, 0 },
        { 1, 0, 1, 0 },
        { 1, 0, 0, 1 },
        { 0, 1, 0, 0 },
    };

    int area = FloodFill::Flood(3, 2, board);

    std::cout << "area : " << area << "\n";

    for (;;)
    {
        //std::string output = m_httpRequest.Post("/t/d3nyp-1519620552/post", "name=tester&name2=teasdas");
        //std::string output2 = m_httpRequest.Get("/t/d3nyp-1519620552/");

        //std::cout << "output : \n" << output << "\n";
        //std::cout << "output2 : \n" << output2 << "\n";
    }
}
