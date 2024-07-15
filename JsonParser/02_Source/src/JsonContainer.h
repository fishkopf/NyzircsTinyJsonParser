#ifndef JSON_CONTAINER_H
#define JSON_CONTAINER_H

#include "JsonElement.h"

class JsonContainer : public JsonElement 
{
public:
    JsonContainer()
    {
        m_type = JsonElementType::CONTAINER;

    }

    ~JsonContainer()
    {}
    std::string serialize() override
    {
        if(m_children.empty())
        {
            return "{}";
        }
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

#endif // JSON_CONTAINER_H