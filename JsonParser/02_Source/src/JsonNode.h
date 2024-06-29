#ifndef HML_JSONNODE_H
#define HML_JSONNODE_H
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include "JsonObject.h"

enum class JsonNodeType
{
    VALUE,
    OBJECT,
    STRING,
    ARRAY
};

class CJsonNode : public CJsonObject
{
    public:
        CJsonNode();
        ~CJsonNode();
        int parse(std::string jsonStr);
        int identifyObject(int &beginTokenPos, int &endTokenPos, std::string BeginToken, std::string EndToken, std::string jsonStr);
        int findMatchingCloseToken( std::string jsonStr, std::string EndToken);
        std::string m_jsonStr;
        int m_beginTokenPos, m_endTokenPos;
    private:
        std::vector<CJsonNode> m_children;
        JsonNodeType m_type;

        

};

#endif