#pragma once
#include<string>
#include <map>

enum class Protocol
{
    HTTP,
    HTTPS,
    FTP
};

extern std::string HTTPS_PROTOCOL;
extern std::string HTTP_PROTOCOL;
extern std::string FTP_PROTOCOL;

extern int HTTPS_PORT;
extern int HTTP_PORT;
extern int FTP_PORT;

extern int MIN_PORT;
extern int MAX_PORT;

extern std::map<Protocol, int> DEFAULT_PORTS;

bool ParseURL(const std::string & url, Protocol &  protocol, int & port, std::string & host, std::string & document);
