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
        m_value = std::vector<JsonElement*>();
    }

    // Destructor
    ~JsonRoot()
    {}
    virtual void attach(JsonElement* child) override
    {
        std::get<std::vector<JsonElement*>>(m_value).push_back(child);
    }
    virtual std::string serialize() override
    {
        std::string serialized = "{";
        for (auto element : std::get<std::vector<JsonElement*>>(m_value))
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