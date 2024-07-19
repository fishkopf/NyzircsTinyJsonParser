#include "JsonParser.h"
CJsonParser::CJsonParser()
{
    const char* ObjStart = "{";
}
CJsonParser::~CJsonParser()
{

}
void CJsonParser::parse(std::string jsonFile)
{
    //@Todo remove all white spaces
    stepThrough(jsonFile);
}

CJsonObject CJsonParser::findNextToken(std::string& jsonStr, int start)
{
    const char str = jsonStr.at(start);
    if(str == '{')
    {
        CJsonObject obj;
        obj.m_type = JsonObjectType::OBJECT_START;
         obj.m_value = "OBJECT_START";
        jsonStr.erase(start,1);
        return obj;
    }
    if(str == '}')
    {
        CJsonObject obj;
        obj.m_type = JsonObjectType::OBJECT_END;
        obj.m_value = "OBJECT_END";
        jsonStr.erase(start,1);
        return obj;
    }
    else if(str == '[')
    {
        CJsonObject obj;
        obj.m_type = JsonObjectType::ARRAY_START;
        obj.m_value = "ARRAY_START";
        jsonStr.erase(start, 1);
        return obj;
    }
    else if(str == ']')
    {
        CJsonObject obj;
        obj.m_type = JsonObjectType::ARRAY_END;
         obj.m_value = "ARRAY_END";
        jsonStr.erase(start,1);
        return obj;
    }
    else if(str == '\"')
    {
        CJsonObject obj;
        int i = jsonStr.find("\"", start+1);
        
        //@Todo ERROR Handling
        obj.m_type = JsonObjectType::STRING;
        obj.m_value = jsonStr.substr(start+1, jsonStr.find("\'",start+1)-1);
        jsonStr.erase(start,(i-start)+1);
        return obj;
    }
    else if(str == '\'')
    {
        CJsonObject obj;
        int i  = jsonStr.find("\'",start+1);
        //@Todo ERROR Handling
        obj.m_type = JsonObjectType::STRING;
        obj.m_value = jsonStr.substr(start+1, jsonStr.find("\'",start+1)-1);
        jsonStr.erase(start,(i-start)+1);
        return obj;      
    }
    else if(str == ':')
    {
        CJsonObject obj;
        obj.m_type = JsonObjectType::SEPARATOR;
        obj.m_value = "SEPARATOR";
        jsonStr.erase(start, 1);
        return obj;      
    }
    else if(str == ',')
    {
        CJsonObject obj;
        obj.m_type = JsonObjectType::COMMA;
        obj.m_value = "COMMA";
        jsonStr.erase(start, 1);
        return obj; 
    }
    else if( belongsToNumber(str) )
    {    
        
        CJsonObject obj;
        std::string value = returnNumber(jsonStr);
        if(value.find(".") != std::string::npos)
        {
            obj.m_type = JsonObjectType::FLOAT;
        }else{  
            obj.m_type = JsonObjectType::INTEGER;
        }
        obj.m_value = value;
        jsonStr.erase(start, value.size());
        return obj;
    }else{
        CJsonObject obj;
        obj.m_type = JsonObjectType::UNKNOWN;
        obj.m_value = "UNKNOWN";
        jsonStr.erase(start, 1);
        return obj;
    }
    for(CJsonObject obj : m_jsonObjects)
    {
        std::cout << obj.m_value << std::endl;
    }
    
}

void CJsonParser::stepThrough(std::string& jsonStr)
{
    int start = 0;
    CJsonObject obj;
    do{
        if(jsonStr.empty())
        {
            break;
        }
        obj = findNextToken(jsonStr, start);
        m_jsonObjects.push_back(obj);
    }while(obj.m_type != JsonObjectType::UNKNOWN);

    JsonRoot* root = new JsonRoot();  
    int ret = buildTree(m_jsonObjects, 1, m_jsonObjects.size()-1, root);
    
    // tell us that there has been an error
    if(ret == -1){std::cout<<"Error"<<std::endl;}
    std::cout << root->serialize() << std::endl;


}


int CJsonParser::buildTree(std::list<CJsonObject> objs, int startPos, int endPos, JsonElement* parent)
{
    std::vector<JsonKey*> keys;
    auto iter = objs.begin();
    auto endIter = objs.end();
    //loop through this object?
    std::advance(iter, startPos);
    if(endPos != -1)
    {
        endIter = objs.begin();
        std::advance(endIter, endPos);
    }
    for(;iter != endIter; ++iter)
    {
        if(iter->m_type == JsonObjectType::STRING)
        {       
            JsonKey* key = new JsonKey();
            key->m_name = iter->m_value;
            parent->attach(key);

            //this must be a key Advance to the next token
            ++iter;

            if (iter->m_type == JsonObjectType::SEPARATOR) {
                // Advance to the next token
                ++iter;
                // Check if the next token is a value
                if (iter->m_type == JsonObjectType::STRING) 
                {
                    processStrValue(objs, std::distance(objs.begin(), iter), key);
                }else if (iter->m_type == JsonObjectType::FLOAT)
                {
                    processFloatValue(objs, std::distance(objs.begin(), iter), key);
                }else if (iter->m_type == JsonObjectType::INTEGER)
                {
                    processIntValue(objs, std::distance(objs.begin(), iter), key);
                }
                else if(iter->m_type == JsonObjectType::OBJECT_START)
                {
                    int startPos = std::distance(objs.begin(), iter);
                    int objectEnd = parseObject(objs, startPos, key);
                    std::advance(iter, objectEnd-startPos);
                    
                }
                else if(iter->m_type == JsonObjectType::ARRAY_START)
                {
                    JsonArray* arr = new JsonArray();
                    key->attach(arr);
                    int arrayEnd = parseArray(objs, std::distance(objs.begin(), iter), arr);
                    int startPos = std::distance(objs.begin(), iter);
                    std::advance(iter, arrayEnd-startPos);
                }
                else if((iter->m_type == JsonObjectType::COMMA) || (iter->m_type == JsonObjectType::SEPARATOR))
                {
                    return -3;
                }else{
                    return -4;
                }
            }else
            {

                return -2;

            }
        }
        else
        {
            if(iter->m_type != JsonObjectType::COMMA)
            {
                CJsonObject obj = *iter;
                int position = std::distance(objs.begin(), iter);
                return -1;
            }

        }

    }

    return 0;
}


int CJsonParser::findClosingStatementFrom(std::list<CJsonObject> list, int startPos, JsonObjectType openingStatement, JsonObjectType closingStatement)
{
    int openings = 0;
    int closing = 0;
    int foundBeginTokenPos = 0;
    int foundEndTokenPos = 0;
    int nextTokenPos = startPos;
    do
    {
        //find next endTokenPos
        foundEndTokenPos = find(list, closingStatement, nextTokenPos);

        foundBeginTokenPos= find(list, openingStatement, nextTokenPos);

        //if begin token is found before end token, no end of the current object has been identified, keep on searching till we balanced begin/end tokens again
        if((foundBeginTokenPos < foundEndTokenPos) && (foundBeginTokenPos != -1))
        {
            nextTokenPos = foundBeginTokenPos + 1;
            openings++;
        }else{
            nextTokenPos = foundEndTokenPos + 1;
            closing++;

        }

    }while((openings-closing > 0));

    return foundEndTokenPos;
}

int CJsonParser::find(std::list<CJsonObject> objs, JsonObjectType type, int startPos)
{
    auto iter = objs.begin();
    std::advance(iter, startPos);
    for (; iter != objs.end(); ++iter)
    {
           
            if(iter->m_type == type)
            {
                int i = std::distance(objs.begin(), iter);

                return i;
            }
    }

    return -1;
}

void CJsonParser::print()
{
    for (auto iter = m_jsonObjects.begin(); iter != m_jsonObjects.end(); ++iter)
    {

        std::cout <<"Entry "<<std::distance(m_jsonObjects.begin(), iter) <<" at "<<iter->m_value << std::endl;
    }
}
std::list<CJsonObject> CJsonParser::createSubList(std::list<CJsonObject> list, int startPos, int endPos)
{

    std::list<CJsonObject> subList;
    auto subIterBegin = list.begin();
    std::advance(subIterBegin, startPos);
    std::list<CJsonObject>::iterator subIterEnd;
    if(endPos == -1)
    {
        subIterEnd = list.end();
    }else{
        subIterEnd = list.begin();
        std::advance(subIterEnd, endPos);
    }
    list.splice(subList.begin(), list, subIterBegin, subIterEnd);
    return subList;
}

int CJsonParser::parseObject(std::list<CJsonObject> objs, int startPos, JsonElement* parent)
{
    JsonContainer* container = new JsonContainer();
    parent->attach(container);
    int closingStatementPos = findClosingStatementFrom(objs, startPos, JsonObjectType::OBJECT_START, JsonObjectType::OBJECT_END);
    buildTree(objs, startPos+1, closingStatementPos, container);
    return closingStatementPos;
}

int CJsonParser::parseArray(std::list<CJsonObject> objs, int startPos, JsonElement* parent)
{
    int closingStatementPos = findClosingStatementFrom(objs, startPos, JsonObjectType::ARRAY_START, JsonObjectType::ARRAY_END);
    auto iter = objs.begin();
    std::advance(iter, startPos);
    auto endIter = objs.begin();
    std::advance(endIter, closingStatementPos);
    for(; iter != endIter; ++iter)
    {          
        if(iter->m_type == JsonObjectType::INTEGER)
        {
            JsonValue* arrElement = new JsonValue(std::stoi(iter->m_value));
            arrElement->m_type = JsonElementType::INTEGER;
            arrElement->m_name = iter->m_value;
            parent->attach(arrElement);
        }
        else if(iter->m_type == JsonObjectType::FLOAT)
        {
            JsonValue* arrElement = new JsonValue(std::stold(iter->m_value));
            arrElement->m_type = JsonElementType::FLOAT;
            arrElement->m_name = iter->m_value;
            parent->attach(arrElement);
        }
        else if (iter->m_type == JsonObjectType::STRING)
        {
            JsonValue* arrElement = new JsonValue(iter->m_value);
            arrElement->m_type = JsonElementType::STRING;
            arrElement->m_name = iter->m_value;
            parent->attach(arrElement);
        }else if (iter->m_type == JsonObjectType::OBJECT_START)
        {
            // @TODO
        }
        
    }    
    return closingStatementPos;
}
int CJsonParser::processIntValue(std::list<CJsonObject> objs, int startPos, JsonElement* parent)
{
    auto iter = objs.begin();
    std::advance(iter, startPos);
    JsonValue* arrElement = new JsonValue(std::stoi(iter->m_value));
    arrElement->m_type = JsonElementType::INTEGER;
    arrElement->m_name = iter->m_value;
    parent->attach(arrElement);
    return ++startPos;
}
int CJsonParser::processFloatValue(std::list<CJsonObject> objs, int startPos, JsonElement* parent)
{
    auto iter = objs.begin();
    std::advance(iter, startPos);
    JsonValue* arrElement = new JsonValue(std::stold(iter->m_value));
    arrElement->m_type = JsonElementType::FLOAT;
    arrElement->m_name = iter->m_value;
    parent->attach(arrElement);
    return ++startPos;
}
int CJsonParser::processStrValue(std::list<CJsonObject> objs, int startPos, JsonElement* parent)
{
    // Process the value
    auto iter = objs.begin();
    std::advance(iter, startPos);
    JsonValue* value = new JsonValue(iter->m_value);
    parent->attach(value);
    return ++startPos;
}

std::string CJsonParser::returnNumber(std::string str)
{
        int i = 0;
        char next = 'a';
        do{
            next = str.at(i);
            ++i;
        }while(belongsToNumber(next));        
        return str.substr(0,i-1);
}

bool CJsonParser::belongsToNumber(const char &c)
{
    if ((c == '1') || (c == '2') ||(c == '3') || (c == '4') ||(c == '5') ||(c == '6') ||(c == '7') ||(c == '8') ||(c == '9') ||(c == '0') ||(c == '.'))
    {
        return true;
    }
    return false;
}
