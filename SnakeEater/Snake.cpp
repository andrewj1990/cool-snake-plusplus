#include "stdafx.h"
#include "Snake.h"
#include "FloodFill.h"
#include "PathFinder.h"

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/http_listener.h>

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
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0 },
        { 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 0, 0, 0 },
        { 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    };

    int area = FloodFill::Flood(3, 2, board);

    InitServer();

    Node start(12, 7);
    Node current(start);
    Node end(16, 7);
    PathFinder::AStar(start, end, board);

    std::cout << "area : " << area << "\n";

    TestCasablanca();

    for (;;)
    {

        //DrawBoard(current, board);
        current = PathFinder::AStar(current, end, board);

        std::cin.get();
    }
}

void Snake::InitServer()
{
    using namespace web;
    using namespace http;
    using namespace utility;
    using namespace http::experimental::listener;

    utility::string_t port = U("8080");
    utility::string_t address = U("http://localhost:");
    address.append(port);

    uri_builder uri(address);
    uri.append_path(U("/"));

    auto addr = uri.to_uri().to_string();
    
    m_server = std::make_unique<Server>(addr);
    m_server->open().wait();

    std::wcout << utility::string_t(U("Listening for requests at: ")) << addr << "\n";

    return;
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

void Snake::TestCasablanca()
{
    //https://github.com/Microsoft/cpprestsdk/wiki/Getting-Started-Tutorial
    using namespace utility;                    // Common utilities like string conversions
    using namespace web;                        // Common features like URIs.
    using namespace web::http;                  // Common HTTP functionality
    using namespace web::http::client;          // HTTP client features
    using namespace concurrency::streams;

    auto fileStream = std::make_shared<concurrency::streams::ostream>();
    auto requestTask = fstream::open_ostream(U("results.html")).then([=](ostream outFile)
    {
        *fileStream = outFile;

        http_client client(U("http://www.bing.com/"));

        uri_builder builder(U("/search"));
        builder.append_query(U("q"), U("cpprestsdk github"));
        return client.request(methods::GET, builder.to_string());
    }).then([=](http_response response)
    {
        std::cout << "Received response status code : " << response.status_code() << "\n";
        //response.extract_json();
        //response.extract_string();
        return response.body().read_to_end(fileStream->streambuf());
    }).then([=](size_t)
    {
        return fileStream->close();
    });

    try
    {
        requestTask.wait();
    }
    catch (const std::exception& e)
    {
        std::cout << "Error exception : " << e.what() << "\n";
    }


}
