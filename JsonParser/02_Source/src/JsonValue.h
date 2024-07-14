#ifndef JSON_VALUE_H
#define JSON_VALUE_H
#include <string>

#include "JsonElement.h"

class JsonValue : public JsonElement
{
public:
    // Constructor
    JsonValue()
    {
        m_type = JsonElementType::VALUE;
    }

    // Destructor
    ~JsonValue()
    {
        
    }
    std::string m_value;
    virtual void attach(JsonElement* child) override
    {
        // Do nothing
    }
    
private:


};

#endif // JSON_VALUE_H