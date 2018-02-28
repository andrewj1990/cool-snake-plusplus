#pragma once

#include "HttpRequests.h"
#include "Node.h"

class Snake
{
public:
    Snake();
    ~Snake();

    void Run();

private:
    void DrawBoard(const Node& node, BoardMatrix& board);

private:
    HttpRequests m_httpRequest;

};