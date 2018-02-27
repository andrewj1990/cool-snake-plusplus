#include "stdafx.h"
#include "HttpRequests.h"
#include <assert.h>
#include <iostream>
#include <vector>

constexpr unsigned int MAX_BUFF_LENGTH = 4096;

HttpRequests::HttpRequests(const std::string& url, WORD port)
    : m_url(url), m_port(port)
{
    // initialize server, filepath, and filename
    ParseUrl();
    m_connection = ConnectToServer();

    assert(m_connection && "Failed to connect to server!");
}

HttpRequests::~HttpRequests()
{
    closesocket(m_connection);
}

SOCKET HttpRequests::ConnectToServer()
{
    struct hostent* hp;
    unsigned int addr;
    struct sockaddr_in server;
    SOCKET conn;

    //conn = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    conn = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (conn == INVALID_SOCKET)
        return NULL;

    if (inet_addr(m_serverName.c_str()) == INADDR_NONE)
    {
        hp = gethostbyname(m_serverName.c_str());
    }
    else
    {
        addr = inet_addr(m_serverName.c_str());
        hp = gethostbyaddr(reinterpret_cast<char*>(addr), sizeof(addr), AF_INET);
    }

    if (hp == NULL)
    {
        closesocket(conn);
        return NULL;
    }

    server.sin_addr.s_addr = *((unsigned long*)hp->h_addr);
    server.sin_family = AF_INET;
    server.sin_port = htons(m_port);
    if (connect(conn, (struct sockaddr*)&server, sizeof(server)))
    {
        closesocket(conn);
        return NULL;
    }

    return conn;
}

std::string HttpRequests::Get(const std::string& path)
{
    std::string header;
    header  = "GET " + path + " HTTP/1.0\r\n";
    header += "Host: " + m_serverName + ":" + std::to_string(m_port) + "\r\n\r\n";

    return Route(header);
}

std::string HttpRequests::Post(const std::string& path, const std::string& data)
{
    std::string header;
    header =  "POST " + path + " HTTP/1.1\r\n";
    header += "Host: " + m_serverName + ":" + std::to_string(m_port) + "\r\n";
    header += "User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:40.0) Gecko/20100101 Firefox/40.0\r\n";
    header += "Referer: http://" + m_serverName + "\r\n";
    header += "Content-Type: application/x-www-form-urlencoded\r\n";
    header += "Content-Length: " + std::to_string(data.length()) + "\r\n";
    header += "Accept-Charset: utf-8\r\n";
    header += "Connection: close\r\n\r\n";
    header += data + "\r\n";
    header += "\r\n";

    return Route(header);
}

void HttpRequests::ParseUrl()
{
    std::string url = m_url;
    std::string::size_type n;

    // remove http tags from url
    if (url.substr(0, 7) == "http://")
        url.erase(0, 7);
    if (url.substr(0, 8) == "https://")
        url.erase(0, 8);

    n = url.find('/');
    if (n != std::string::npos)
        m_serverName = url.substr(0, n);
    else
        m_serverName = url;
}

std::string HttpRequests::Route(const std::string& header)
{
    std::string res = "";
    if (send(m_connection, header.c_str(), static_cast<int>(header.length()), 0))
    {
        // Receive 
        std::vector<char> recvBuffer(MAX_BUFF_LENGTH);
        std::string receiveString;
        int bytesReceived = 0;
        int totalBytes = 0;
        while (true)
        {
            bytesReceived = recv(m_connection, &recvBuffer[0], static_cast<int>(recvBuffer.size()), 0);
            totalBytes += bytesReceived;

            if (bytesReceived <= 0)
                break;
            else
                receiveString.append(recvBuffer.cbegin(), recvBuffer.cbegin() + bytesReceived);
        }

        if (totalBytes > 0)
        {
            int headerLen = GetHeaderLength(receiveString.c_str());
            int contentLen = totalBytes - headerLen;
            res.append(receiveString.cbegin() + headerLen, receiveString.cbegin() + totalBytes);
        }
    }

    return res;
}

int HttpRequests::GetHeaderLength(const char* content)
{
    const char* srchStr1 = "\r\n\r\n";
    const char* srchStr2 = "\n\r\n\r";
    const char* findPos;
    int offset = -1;

    findPos = strstr(content, srchStr1);
    if (findPos != NULL)
    {
        offset = findPos - content;
        offset += strlen(srchStr1);
    }
    else
    {
        findPos = strstr(content, srchStr2);
        if (findPos != NULL)
        {
            offset = findPos - content;
            offset += strlen(srchStr2);
        }
    }

    return offset;
}
