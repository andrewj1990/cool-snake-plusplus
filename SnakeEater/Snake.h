#pragma once

#include "HttpRequests.h"

class Snake
{
public:
    Snake();
    ~Snake();

    void Run();

private:
    HttpRequests m_httpRequest;

};