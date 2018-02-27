#pragma once

#include <string>
#include <stdio.h>
#include <winsock.h>

#pragma comment(lib, "ws2_32.lib")

class HttpRequests
{
public:

    HttpRequests(const std::string& url, WORD port);
    ~HttpRequests();

    std::string Get(const std::string& path);
    std::string Post(const std::string& path, const std::string& data);

private:
    SOCKET ConnectToServer();
    void ParseUrl();
    std::string Route(const std::string& header);
    int GetHeaderLength(const char* content);

private:
    WORD m_port;

    std::string m_url;
    std::string m_serverName;

    SOCKET m_connection;
};