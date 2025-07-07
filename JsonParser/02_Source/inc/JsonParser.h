#ifndef HML_JSONPARSER_H
#define HML_JSONPARSER_H    
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <iterator>
#include "JsonObject.h"
#include "JsonElement.h"
#include "JsonKey.h"
#include "JsonRoot.h"
#include "JsonArray.h"
#include "JsonContainer.h"
#include "JsonValue.h"

class CJsonParser
{
    public:
        CJsonParser();
        ~CJsonParser();
        JsonRoot* parse(std::string jsonFile);
        CJsonObject findNextToken(std::string& jsonStr,int start );
        JsonRoot* stepThrough(std::string& jsonStr);
        int findClosingStatementFrom(std::list<CJsonObject> list, int startPos, JsonObjectType openingStatement, JsonObjectType closingStatement);

        int buildTree(std::list<CJsonObject> objs, int startPos, int endPos, JsonElement* parent);
        int find(std::list<CJsonObject> objs, JsonObjectType type, int startPos);
        void print();
        std::string removeWhiteSpaces(std::string input);
        std::string stripString(std::string input);
        
    private:
        int parseObject(std::list<CJsonObject> list, int startPos, JsonElement* parent);
        int parseArray(std::list<CJsonObject> objs, int startPos, JsonElement* parent);
        int processStrValue(std::list<CJsonObject> objs, int startPos, JsonElement* parent);
        int processIntValue(std::list<CJsonObject> objs, int startPos, JsonElement* parent);
        int processFloatValue(std::list<CJsonObject> objs, int startPos, JsonElement* parent);
        std::string returnNumber(std::string str);
        bool belongsToNumber(const char& c);

        std::list<CJsonObject> createSubList(std::list<CJsonObject> list, int startPos, int endPos);
        std::list<CJsonObject> m_jsonObjects;
        
        

};
// Forward declarations
class JsonObject;
class JsonArray;
class JsonContainer;
class JsonValue;


#endif