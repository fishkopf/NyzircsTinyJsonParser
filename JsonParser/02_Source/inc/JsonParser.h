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
        void parse(std::string jsonFile);
        CJsonObject findNextToken(std::string& jsonStr,int start );
        void stepThrough(std::string& jsonStr);
        int BuildTree(std::list<CJsonObject> objs, int depth,JsonElement* parent);
        int findClosingStatement( std::list<CJsonObject> list, JsonObjectType type, JsonObjectType closingStatement);
        int matchKeytoValue(std::list<CJsonObject> list, int startPos);

        int find(std::list<CJsonObject> objs, JsonObjectType type, int startPos);
        void print();
        
        
    private:
        std::list<CJsonObject> createSubList(std::list<CJsonObject> list, int startPos, int endPos);
        std::list<CJsonObject> m_jsonObjects;
        

};

#endif