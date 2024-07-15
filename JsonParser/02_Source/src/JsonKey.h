#ifndef JSON_KEY_H
#define JSON_KEY_H
#include <string>
#include "JsonElement.h"
class JsonKey : public JsonElement
{
public:
    // Constructor
    JsonKey()
    {
        m_type = JsonElementType::KEY;
    
    }

    // Destructor
    ~JsonKey()
    {
        
    }
    std::string serialize() override
    {
        std::string serialized = "\""+ m_name + "\""+ ":";
        serialized += m_children[0]->serialize();
        return serialized;
    }
private:

};

#endif // JSONKEY_H