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

    virtual std::string serialize() override
    {
        std::string serialized = "{";
        for (auto element : m_children)
        {
            serialized += element->serialize();
            serialized += ",";
        }
        serialized.pop_back(); // remove last comma, any better way?
        serialized += "}";
        return serialized;
    }
};

#endif // JSONROOT_H