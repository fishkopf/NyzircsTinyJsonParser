#ifndef JSON_OBJECT_H
#define JSON_OBJECT_H
#include <string>
#include <vector>
#include "JsonElement.h"
enum class JsonObjectType
{
    STRING,
    KEY,
    VALUE,
    OBJECT_START,
    OBJECT_END,
    ARRAY_START,
    ARRAY_END,
    SEPARATOR,
    COMMA,
    INTEGER,
    FLOAT,
    WHITESPACE,
    UNKNOWN

};

class CJsonObject
{
    public:
        CJsonObject(){}
        ~CJsonObject(){}
        
        JsonObjectType m_type;
        std::string m_value;
    private:
        std::vector<JsonElement*> m_elements;

};
#endif