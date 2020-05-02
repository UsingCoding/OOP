#pragma once

#include <string>
#include <map>

static const char HTML_ENTITY_BEGINS = '&';
static const char HTML_ENTITY_ENDS = ';';

static const std::string DOUBLE_QUOTE = "quot";
static const std::string APOSTROPHE = "apos";
static const std::string MARK_LESS = "lt";
static const std::string MARK_GREATER = "gt";
static const std::string AMPERSAND = "amp";

static std::map<std::string, char> htmlEntitiesMap = {
    { DOUBLE_QUOTE, '"' },
    { APOSTROPHE, '`' },
    { MARK_LESS, '<' },
    { MARK_GREATER, '>' },
    { AMPERSAND, '&' }
};

std::string HtmlDecode(const std::string &html);