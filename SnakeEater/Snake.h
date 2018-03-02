#pragma once

#include "HttpRequests.h"
#include "Node.h"
#include "Server.h"

class Snake
{
public:
    Snake();
    ~Snake();

    void Run();

private:
    void InitServer();
    void DrawBoard(const Node& node, BoardMatrix& board);

    void TestCasablanca();

private:
    HttpRequests m_httpRequest;

    std::unique_ptr<Server> m_server;

};