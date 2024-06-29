#include "JsonNode.h"

CJsonNode::CJsonNode()
{
    m_beginTokenPos = -1;
    m_endTokenPos = -1;
}
CJsonNode::~CJsonNode()
{

}
int CJsonNode::parse(std::string jsonStr)
{
    std::vector<int> beginTokens;
    std::vector<int> endTokens;
    int balanced = 0;
    //finde opening bracket
    std::string inptStr = jsonStr;
    int foundInitialToken = jsonStr.find("{");
    if(jsonStr.size() == 0)
    {
        return 0;
    }
    if( foundInitialToken == std::string::npos)
    {


        return 0;
    }
    int nextTokenPos = foundInitialToken;

    unsigned int foundBeginTokenPos = -1;
    unsigned int foundEndTokenPos = -1;
    int end = findMatchingCloseToken(jsonStr, "}");
    m_jsonStr = jsonStr.substr(foundInitialToken +1, end - (foundInitialToken + 1));
    m_beginTokenPos = foundInitialToken;
    m_endTokenPos = end;
    
    CJsonNode node;
    if(m_jsonStr.size() != 0)
    {
        node.parse(m_jsonStr);
        m_children.push_back(node);
    }

    CJsonNode node2;
    jsonStr = jsonStr.substr(end + 1);
    if(jsonStr.size() != 0)
    {
        node2.parse(jsonStr);
        m_children.push_back(node2);
    }
    if(node.m_endTokenPos == -1 || node.m_beginTokenPos == -1)
    {
        std::cout<<m_jsonStr<<std::endl;
        return 0;
    }   
    m_jsonStr.erase(node.m_beginTokenPos, node.m_endTokenPos - node.m_beginTokenPos);
    std::cout<<m_jsonStr<<std::endl;



    std::cout<<"------------------"<<std::endl;
#if 0
    if((node.m_endTokenPos == -1)|| (node.m_beginTokenPos == -1)|| jsonStr.size() != 0)
    {
        std::cout<<m_jsonStr<<std::endl;
        return 0;
    }
    m_jsonStr.erase(node.m_beginTokenPos, node.m_endTokenPos - node.m_beginTokenPos);
    if((node2.m_endTokenPos == -1)|| (node2.m_beginTokenPos == -1) || jsonStr.size() != 0)
    {
        std::cout<<m_jsonStr<<std::endl;
        return 0;
    }
    m_jsonStr.erase(node2.m_beginTokenPos, node2.m_endTokenPos - node2.m_beginTokenPos);
    std::cout<<m_jsonStr<<std::endl;
    std::cout<<"------------------"<<std::endl;
#endif
    return 0;
}
int CJsonNode::identifyObject(int &beginTokenPos, int &endTokenPos, std::string BeginToken, std::string EndToken, std::string jsonStr)
{

}
int CJsonNode::findMatchingCloseToken( std::string jsonStr,std::string EndToken)
{
    int balanced = 0;
    unsigned int foundBeginTokenPos = -1;
    unsigned int foundEndTokenPos = -1;
    int nextTokenPos = 0;
    do
    {
        //find next endTokenPos
        foundEndTokenPos = jsonStr.find("}", nextTokenPos);

        foundBeginTokenPos= jsonStr.find("{", nextTokenPos);
        //if begin token is found before end token, no end of the current object has been identified, keep on searching till we balanced begin/end tokens again
        if((foundBeginTokenPos < foundEndTokenPos) && (foundBeginTokenPos != std::string::npos))
        {
            nextTokenPos = foundBeginTokenPos + 1;
            balanced++;
        }else{
            nextTokenPos = foundEndTokenPos + 1;
            balanced--;
        }
    }while(balanced != 0);
    return foundEndTokenPos;
}

#if 0
int CJsonNode::parse(std::string jsonStr)
{
    std::vector<int> beginTokens;
    std::vector<int> endTokens;
    int balanced = 0;
    //finde opening bracket

    int foundInitialToken = jsonStr.find("{");
    if( foundInitialToken == std::string::npos)
    {
        std::cout<<jsonStr<<std::endl;
        std::cout<<"------------------"<<std::endl;

        return 0;
    }
    int nextTokenPos = foundInitialToken;

    unsigned int foundBeginTokenPos = -1;
    unsigned int foundEndTokenPos = -1;
    do
    {
        //find next endTokenPos
        foundEndTokenPos = jsonStr.find("}", nextTokenPos);

        foundBeginTokenPos= jsonStr.find("{", nextTokenPos);
        //if begin token is found before end token, no end of the current object has been identified, keep on searching till we balanced begin/end tokens again
        if((foundBeginTokenPos < foundEndTokenPos) && (foundBeginTokenPos != std::string::npos))
        {
            nextTokenPos = foundBeginTokenPos + 1;
            balanced++;
        }else{
            nextTokenPos = foundEndTokenPos + 1;
            balanced--;
        }
        std::cout<<"balanced: "<<balanced<<std::endl;
        if(balanced == 0)
        {
            CJsonNode node;
            m_jsonStr = jsonStr.substr(foundInitialToken +1 , foundEndTokenPos - (foundInitialToken+1));
            node.parse(m_jsonStr);
            m_children.push_back(node);
            balanced = 0;
        }
    } while (foundBeginTokenPos != std::string::npos && foundEndTokenPos != std::string::npos && balanced >= 0);
    for(int i = 0; i < m_children.size(); i++)
    {
        std::cout<< m_children.at(i).m_jsonStr<<std::endl;
    }

    /* @TODO check if */

    return 0;
}
#endif