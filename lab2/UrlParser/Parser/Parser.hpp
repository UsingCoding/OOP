#pragma once
#include<string>
#include <map>

enum Protocol
{
    HTTP,
    HTTPS,
    FTP
};

static std::string HTTPS_PROTOCOL = "https";
static std::string HTTP_PROTOCOL = "http";
static std::string FTP_PROTOCOL = "ftp";

static int HTTPS_PORT = 443;
static int HTTP_PORT = 80;
static int FTP_PORT = 21;

static int minPort = 1;
static int maxPort = 65535;

static const std::map<Protocol, int> DEFAULT_PORTS = {
    { HTTP, HTTP_PORT },
    { HTTPS, HTTPS_PORT },
    { FTP, FTP_PORT }
};

bool ParseURL(const std::string & url, Protocol &  protocol, int & port, std::string & host, std::string & document);
