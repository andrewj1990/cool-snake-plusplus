#include "stdafx.h"
#include "Server.h"

using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

Server::Server()
{
}

Server::Server(utility::string_t url)
    : m_listener(url)
{
    m_listener.support(methods::GET, std::bind(&Server::HandleGet, this, std::placeholders::_1));
    m_listener.support(methods::PUT, std::bind(&Server::HandlePut, this, std::placeholders::_1));
    m_listener.support(methods::POST, std::bind(&Server::HandlePost, this, std::placeholders::_1));
    m_listener.support(methods::DEL, std::bind(&Server::HandleDelete, this, std::placeholders::_1));
}

Server::~Server()
{
}

pplx::task<void> Server::open()
{
    return m_listener.open();
}

pplx::task<void> Server::close()
{
    return m_listener.close();
}

void Server::HandleGet(web::http::http_request message)
{
    std::wcout << message.to_string() << "\n";
    message.reply(status_codes::OK);
}

void Server::HandlePut(web::http::http_request message)
{
    std::wcout << message.to_string() << "\n";
    message.reply(status_codes::OK);
}

void Server::HandlePost(web::http::http_request message)
{
    auto paths = http::uri::split_path(http::uri::decode(message.relative_uri().path()));
    auto data = http::uri::split_query(message.relative_uri().query());

    // response data
    if (!paths.empty())
    {
        if (paths[0] == L"start")
        {
            HandleStartRequest(message);
        }
        if (paths[0] == L"move")
        {

        }

    }

    //std::wcout << message.to_string() << "\n";
    message.reply(status_codes::OK);
}

void Server::HandleDelete(web::http::http_request message)
{
    std::wcout << message.to_string() << "\n";
    message.reply(status_codes::OK);
}

void Server::HandleStartRequest(const web::http::http_request& message)
{
    message.extract_json().then([](pplx::task<json::value> task)
    {
        try
        {
            auto jvalue = task.get();

            if (!jvalue.is_null())
            {
                std::wcout << jvalue.serialize() << "\n";
            }
        }
        catch (http_exception const& e)
        {
            std::wcout << e.what() << std::endl;
        }
    }).wait();


    auto response = json::value::object();
    response[L"color"] = json::value::string(L"#ffffff");
    response[L"name"] = json::value::string(L"Cool Snake++");
    response[L"head_url"] = json::value::string(L"http://www.placecage.com/c/200/200");
    response[L"taunt"] = json::value::string(L"Let's do thisss thang!++");

    message.reply(status_codes::OK, response);
}

void Server::HandleMoveRequest(const web::http::http_request& message)
{
}


#if 0:
{
  "food": {
    "data": [
      {
        "object": "point",
        "x": 0,
        "y": 9
      }
    ],
    "object": "list"
  },
  "height": 20,
  "id": 1,
  "object": "world",
  "snakes": {
    "data": [
      {
        "body": {
          "data": [
            {
              "object": "point",
              "x": 13,
              "y": 19
            },
            {
              "object": "point",
              "x": 13,
              "y": 19
            },
            {
              "object": "point",
              "x": 13,
              "y": 19
            }
          ],
          "object": "list"
        },
        "health": 100,
        "id": "58a0142f-4cd7-4d35-9b17-815ec8ff8e70",
        "length": 3,
        "name": "Sonic Snake",
        "object": "snake",
        "taunt": "Gotta go fast"
      },
      {
        "body": {
          "data": [
            {
              "object": "point",
              "x": 8,
              "y": 15
            },
            {
              "object": "point",
              "x": 8,
              "y": 15
            },
            {
              "object": "point",
              "x": 8,
              "y": 15
            }
          ],
          "object": "list"
        },
        "health": 100,
        "id": "48ca23a2-dde8-4d0f-b03a-61cc9780427e",
        "length": 3,
        "name": "Typescript Snake",
        "object": "snake",
        "taunt": ""
      }
    ],
    "object": "list"
  },
  "turn": 0,
  "width": 20,
  "you": {
    "body": {
      "data": [
        {
          "object": "point",
          "x": 8,
          "y": 15
        },
        {
          "object": "point",
          "x": 8,
          "y": 15
        },
        {
          "object": "point",
          "x": 8,
          "y": 15
        }
      ],
      "object": "list"
    },
    "health": 100,
    "id": "48ca23a2-dde8-4d0f-b03a-61cc9780427e",
    "length": 3,
    "name": "Typescript Snake",
    "object": "snake",
    "taunt": ""
  }
}

response:
{
"move": "up"
}

end:
{
  "game_id": 10,
  "winners": [ "a46b558b-f31b-418f-bb07-6017dd91f653" ],
  "dead_snakes": {
    "object": "list",
    "data": [{
      "id": "4a35fd1c-434b-431b-839c-edf958d67e9a",
      "length": 3,
      "death": {
        "turn": 4,
        "causes": ["self collision"]
      }
    }]
  }
}

#endif