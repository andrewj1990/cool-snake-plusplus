#pragma once

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/http_listener.h>

//using namespace web;
//using namespace http;
//using namespace utility;
//using namespace http::experimental::listener;

class Server
{
public:
    Server();
    Server(utility::string_t url);
    ~Server();

    pplx::task<void> open();
    pplx::task<void> close();

private:
    void HandleGet(web::http::http_request message);
    void HandlePut(web::http::http_request message);
    void HandlePost(web::http::http_request message);
    void HandleDelete(web::http::http_request message);

    void HandleStartRequest(const web::http::http_request& message);
    void HandleMoveRequest(const web::http::http_request& message);

private:
    web::http::experimental::listener::http_listener m_listener;
};