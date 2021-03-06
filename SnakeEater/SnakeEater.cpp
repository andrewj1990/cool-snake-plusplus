// SnakeEater.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "HttpRequests.h"
#include "Snake.h"

int main()
{
    // initialize
    WSADATA wsaData;
    if (WSAStartup(0x101, &wsaData) != 0)
        return -1;


    Snake snake;
    snake.Run();

    WSACleanup();
    // pause
    std::cin.get();

    return 0;
}