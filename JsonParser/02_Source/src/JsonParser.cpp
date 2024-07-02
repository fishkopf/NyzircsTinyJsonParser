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
    else if( (str == '1') || (str == '2') ||(str == '3') || (str == '4') ||(str == '5') ||(str == '6') ||(str == '7') ||(str == '8') ||(str == '9') ||(str == '0') )
    {    
        CJsonObject obj;
        obj.m_type = JsonObjectType::NUMBER;
        obj.m_value = "NUMBER";
        jsonStr.erase(start, 1);
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
    JsonElement* root = new JsonRoot();  
    BuildTree(m_jsonObjects, 0, root);
    std::cout<<"Root"<<std::endl;


}
int CJsonParser::BuildTree(std::list<CJsonObject> objs, int depth, JsonElement* parent)
{

    int closingStatementPos = 0;
    while(!objs.empty())
    {
        
        if(objs.begin()->m_type == JsonObjectType::OBJECT_START)
        {
            for(int i = 0; i < depth; i++)
            {
                std::cout<<" ";
            }
            std::cout<<"{"<<std::endl;
            closingStatementPos = findClosingStatement(objs, JsonObjectType::OBJECT_START, JsonObjectType::OBJECT_END);
            std::list<CJsonObject> subobj1 = createSubList(objs, 1, closingStatementPos);

            JsonContainer* container = new JsonContainer();
            BuildTree(subobj1, depth+1, container);
            parent->m_children.push_back(container);

            std::list<CJsonObject> tmp = createSubList(objs, closingStatementPos+1, -1);
            objs = tmp;

            for(int i = 0; i < depth; i++)
            {
                std::cout<<" ";
            }
            std::cout<<"}"<<std::endl;
        }
        else if(objs.begin()->m_type == JsonObjectType::ARRAY_START)
        {
            for(int i = 0; i < depth; i++)
            {
                std::cout<<" ";
            }
            std::cout<<"["<<std::endl;
            closingStatementPos = findClosingStatement( objs, JsonObjectType::ARRAY_START, JsonObjectType::ARRAY_END);
            std::list<CJsonObject> subobj1 = createSubList(objs, 1, closingStatementPos);
            JsonElement* arr = new JsonElement();
            BuildTree(subobj1, depth+1, arr);
            parent->m_children.push_back(arr);
            std::list<CJsonObject> tmp = createSubList(objs, closingStatementPos+1, -1);
            objs = tmp;
            for(int i = 0; i < depth; i++)
            {
                std::cout<<" ";
                
            }
            std::cout<<"]"<<std::endl;
        }
        else if(objs.begin()->m_type == JsonObjectType::NUMBER)
        {
            for(int i = 0; i < depth; i++)
            {
                std::cout<<" ";
            }
            std::cout<<"NUMBER "<<objs.begin()->m_value<<std::endl;
            JsonValue* value = new JsonValue();
            value->m_value = objs.begin()->m_value;
            parent->attach(value);

            //create number to return
            std::list<CJsonObject> tmp = createSubList(objs, 1, -1);
            objs = tmp;
            //return nullptr;
        }
        else if(objs.begin()->m_type == JsonObjectType::STRING)
        {
            for(int i = 0; i < depth; i++)
            {
                std::cout<<" ";
            }
            std::cout<<"STRING "<<objs.begin()->m_value<<std::endl;

            JsonKey* key = new JsonKey();
            key->m_name = objs.begin()->m_value;
            parent->attach(key);

            auto iter = objs.begin();
            std::advance(iter, 1);
            if(iter->m_type != JsonObjectType::SEPARATOR)
            {   
                return -1; //ERROR
            }
            std::advance(iter, 1);
            if((iter->m_type == JsonObjectType::ARRAY_START) || (iter->m_type == JsonObjectType::OBJECT_START))
            {
                std::list<CJsonObject> tmp = createSubList(objs, 2, -1);
                BuildTree(tmp, depth+1, key);
                objs = tmp;
                return 0; //ERROR
            }else if((iter->m_type == JsonObjectType::STRING) || (iter->m_type == JsonObjectType::NUMBER))
            {
                
                JsonValue* value = new JsonValue();
                value->m_value = iter->m_value;
                key->attach(value);
                std::list<CJsonObject> tmp = createSubList(objs, 2, -1);
                objs = tmp;
            }

        }
        else if((objs.begin()->m_type == JsonObjectType::SEPARATOR) || (objs.begin()->m_type == JsonObjectType::COMMA))
        {
            std::list<CJsonObject> tmp = createSubList(objs, 1, -1);
            objs = tmp;
        }
        else if(objs.begin()->m_type == JsonObjectType::UNKNOWN)
        {
            return -1; //ERROR
        }
       
    }
    return 0;
}

int CJsonParser::findClosingStatement(std::list<CJsonObject> list ,JsonObjectType openingStatement, JsonObjectType closingStatement)
{
    int openings = 0;
    int closing = 0;
    int foundBeginTokenPos = 0;
    int foundEndTokenPos = 0;
    int nextTokenPos = 0;
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
