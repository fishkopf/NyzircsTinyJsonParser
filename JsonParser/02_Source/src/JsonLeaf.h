#ifndef HML_JSONLEAF_H
#define HML_JSONLEAF_H
#include <string>
#include "JsonObject.h"



class CJsonLeaf : public CJsonObject
{
    public:
        CJsonLeaf();
        ~CJsonLeaf();
    private:
        std::string m_value;

};
#endif