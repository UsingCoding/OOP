#include "HttpUrl.hpp"

#include <stdexcept>
#include <regex>
#include "../UrlParsingError/UrlParsingError.hpp"
#include "../../../Utils/StringUtils.hpp"

const std::string HttpUrl::HTTPS_PROTOCOL = "https";
const std::string HttpUrl::HTTP_PROTOCOL = "http";
const std::string HttpUrl::PROTOCOL_DOMAIN_SEPARATOR = "://";
const char HttpUrl::SLASH = '/';
const char HttpUrl::COLON = ':';

HttpUrl::HttpUrl(const std::string & url)
{
    ParseURL(url);
}

HttpUrl::HttpUrl(const std::string & domain, const std::string & document, Protocol protocol):
domain(domain), document(document), protocol(protocol), port(NON_SPECIFIED_PORT_VALUE) {}


HttpUrl::HttpUrl(const std::string & domain, const std::string & document, Protocol protocol, unsigned short port):
domain(domain), document(document), protocol(protocol), port(port) {}

void HttpUrl::ParseURL(const std::string & url)
{
    std::cmatch matches;

    std::regex regular("^([[:alpha:]]+)://([-.[:alnum:]]+)(:([[:digit:]]+))?(/(.*))?$");

    std::regex_search(url.c_str(), matches, regular);

    if (matches.empty())
    {
        throw UrlParsingError("No correct url info found");
    }

    protocol = RetrieveProtocolFromString(matches[1]);

    port = std::atoi(((std::string) matches[4]).c_str()) ?: NON_SPECIFIED_PORT_VALUE;

    domain = matches[2];
    document = matches[6];
}

HttpUrl::Protocol HttpUrl::RetrieveProtocolFromString(std::string protocol)
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

    throw UrlParsingError("Bad protocol");
}

std::string HttpUrl::GetURL() const
{
    auto concatenator = StringUtils::StringConcatenator();

    concatenator << (HTTP ? HTTP_PROTOCOL : HTTPS_PROTOCOL) << PROTOCOL_DOMAIN_SEPARATOR << domain;

    if (port != NON_SPECIFIED_PORT_VALUE && port != DEFAULT_HTTPS_PORT && port != DEFAULT_HTTP_PORT)
    {
        concatenator << COLON << port;
    }

    return concatenator << GetDocument();
}
std::string HttpUrl::GetDomain() const
{
    return domain;
}
std::string HttpUrl::GetDocument() const
{
    return StringUtils::StartsWith(document, StringUtils::StringConcatenator() << SLASH) ? document : StringUtils::StringConcatenator() << SLASH << document;
}

HttpUrl::Protocol HttpUrl::GetProtocol() const
{
    return protocol;
}
unsigned short HttpUrl::GetPort() const
{
    if (port == NON_SPECIFIED_PORT_VALUE)
    {
        return protocol == Protocol::HTTP ? DEFAULT_HTTP_PORT : DEFAULT_HTTPS_PORT;
    }

    return port;
}
