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

private:

};

#endif // JSONKEY_H