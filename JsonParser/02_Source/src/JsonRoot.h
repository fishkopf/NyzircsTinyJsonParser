#ifndef JSON_ROOT_H
#define JSON_ROOT_H
#include "JsonElement.h"

class JsonRoot : public JsonElement
{
public:
    // Constructor
    JsonRoot()
    {
        m_type = JsonElementType::ROOT;
    }

    // Destructor
    ~JsonRoot()
    {}

    std::vector<JsonElement*> m_children;


private:
};

#endif // JSONROOT_H