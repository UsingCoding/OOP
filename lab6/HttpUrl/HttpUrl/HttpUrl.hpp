#pragma once

#include <string>
#include <optional>
#include <functional>

class HttpUrl
{
public:
    enum Protocol
    {
    	HTTP,
    	HTTPS
    };

	// выполняет парсинг строкового представления URL-а, в случае ошибки парсинга
	// выбрасыват исключение CUrlParsingError, содержащее текстовое описание ошибки
	HttpUrl(const std::string & url);

	/* инициализирует URL на основе переданных параметров.
		При недопустимости входных параметров выбрасывает исключение
		std::invalid_argument
		Если имя документа не начинается с символа /, то добавляет / к имени документа
	*/
	HttpUrl(const std::string & domain, const std::string & document, Protocol protocol = HTTP);

	/* инициализирует URL на основе переданных параметров.
		При недопустимости входных параметров выбрасывает исключение
		std::invalid_argument
		Если имя документа не начинается с символа /, то добавляет / к имени документа
	*/
	HttpUrl(const std::string & domain, const std::string & document, Protocol protocol, unsigned short port);

	// возвращает строковое представление URL-а. Порт, являющийся стандартным для
	// выбранного протокола (80 для http и 443 для https) в эту строку
	// не должен включаться
	std::string GetURL() const;

	// возвращает доменное имя
	std::string GetDomain() const;

	/*
		Возвращает имя документа. Примеры:
			/
			/index.html
			/images/photo.jpg
	*/
	std::string GetDocument() const;

	// возвращает тип протокола
	Protocol GetProtocol() const;

	// возвращает номер порта
	unsigned short GetPort() const;
private:
	std::string domain;
	std::string document;
	Protocol protocol;
	unsigned short port;

	const static std::string HTTPS_PROTOCOL;
	const static std::string HTTP_PROTOCOL;
	const static std::string PROTOCOL_DOMAIN_SEPARATOR;

	const static char SLASH;
	const static char COLON;
	const static int NON_SPECIFIED_PORT_VALUE = 0;
	const static int DEFAULT_HTTP_PORT = 80;
	const static int DEFAULT_HTTPS_PORT = 443;

    void ParseURL(const std::string & url);
	Protocol static RetrieveProtocolFromString(std::string protocol);
};
