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
    //Ellie ist süß
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
    BuildTree(m_jsonObjects, 0);

}
void CJsonParser::BuildTree(std::list<CJsonObject> objs, int startPos)
{
    if(objs.empty())
    {
        return;
    }
    int closingStatementPos = 0;
    for(CJsonObject obj : objs)
    {
        std::cout << obj.m_value<<" ";
    }
    std::cout <<std::endl<<"================="<< std::endl;
    auto iter = objs.begin(); //iter != objs.end(); ++iter)
    {
        
        std::advance(iter, startPos);
        if(iter->m_type == JsonObjectType::OBJECT_START)
        {
            //@Todo finde end of object
            closingStatementPos = findClosingStatement(objs, JsonObjectType::OBJECT_START, JsonObjectType::OBJECT_END, 0);

            std::list<CJsonObject> subobj1;
            auto subIterBegin = iter;
            std::advance(subIterBegin, startPos+1);
            auto subIterEnd = objs.begin();
            std::advance(subIterEnd, closingStatementPos);
            objs.splice(subobj1.begin(), objs, subIterBegin, subIterEnd);
            BuildTree(subobj1, startPos);

            std::list<CJsonObject> subobj2;
            objs.splice(subobj2.begin(), objs, subIterEnd, objs.end());

            BuildTree(subobj2, startPos);


            

        }
        else if(iter->m_type == JsonObjectType::ARRAY_START)
        {
            //@Todo finde end of array
            closingStatementPos = findClosingStatement( objs, JsonObjectType::ARRAY_START, JsonObjectType::ARRAY_END, 0);
            std::list<CJsonObject> subobj1;
            auto subIterBegin = iter;
            std::advance(subIterBegin, startPos+1);
            auto subIterEnd = objs.begin();
            std::advance(subIterEnd, closingStatementPos);
            objs.splice(subobj1.begin(), objs, subIterBegin, subIterEnd);
            BuildTree(subobj1, startPos);
        }
        else if(iter->m_type == JsonObjectType::NUMBER)
        {
            //@Todo we have only entries
            std::cout<<"Number "<<iter->m_value<<std::endl;
            std::cout <<"###################"<< std::endl;
            std::advance(iter, 1);
            std::list<CJsonObject> subobj1;
            objs.splice(subobj1.begin(), objs, iter, objs.end());
            

            BuildTree(subobj1, startPos);
        }
        else if(iter->m_type == JsonObjectType::STRING)
        {
            //@Todo we have only entries
            std::cout<<"STRING "<<iter->m_value<<std::endl;
            std::cout <<"###################"<< std::endl;
            std::advance(iter, 1);
            std::list<CJsonObject> subobj1;
            objs.splice(subobj1.begin(), objs, iter, objs.end());
            BuildTree(subobj1, startPos);

        }
        else if((iter->m_type == JsonObjectType::SEPARATOR) || (iter->m_type == JsonObjectType::COMMA))
        {
            std::advance(iter, 1);
            std::list<CJsonObject> subobj1;
            objs.splice(subobj1.begin(), objs, iter, objs.end());
            BuildTree(subobj1, startPos);

        }
        else if(iter->m_type == JsonObjectType::UNKNOWN)
        {
            return ;
        }
       
        //BUild TREE
    }
}

int CJsonParser::findClosingStatement(std::list<CJsonObject> list ,JsonObjectType openingStatement, JsonObjectType closingStatement,  int openingStatementPos)
{
    int openings = 0;
    int closing = 0;
    int foundBeginTokenPos = openingStatementPos;
    int foundEndTokenPos = openingStatementPos;
    int nextTokenPos = openingStatementPos;
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