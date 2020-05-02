#include <regex>
#include <stdexcept>
#include <exception>
#include "./Parser.hpp"

#include <iostream>

Protocol RetrieveProtocol(std::string protocol)
{
    std::transform(protocol.begin(), protocol.begin(), protocol.end(), tolower);

	if (protocol == HTTPS_PROTOCOL)
	{
		return Protocol::HTTPS;
	}
	if (protocol == HTTP_PROTOCOL)
	{
		return Protocol::HTTP;
	}
	if (protocol == FTP_PROTOCOL)
	{
		return Protocol::FTP;
	}

    throw std::runtime_error("Bad protocol");
}

int RetrievePort(Protocol protocol, const std::string & port)
{
    if (port.empty())
    {
        return DEFAULT_PORTS.find(protocol)->second;
    }

    int resultPort = std::atoi(port.c_str());

    if (resultPort <= minPort || resultPort >= maxPort)
	{
        throw std::runtime_error("Incorrect port");
	}

    return resultPort;

}

bool ParseURL(const std::string & url, Protocol &  protocol, int & port, std::string & host, std::string & document)
{
    std::cmatch matches;

    std::regex regular("^([[:alpha:]]+)://([-.[:alnum:]]+)(:([[:digit:]]+))?(/(.*))?$");

    std::regex_search(url.c_str(), matches, regular);

    if (matches.empty())
    {
        return false;
    }

    try
    {
        protocol = RetrieveProtocol(matches[1]);

        port = RetrievePort(protocol, matches[4]);
    }
    catch(const std::runtime_error& e)
    {
        return false;
    }

    host = matches[2];
    document = matches[6];

    return true;
}
