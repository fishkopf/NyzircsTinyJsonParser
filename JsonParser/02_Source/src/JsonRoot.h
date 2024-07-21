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
    virtual JsonElement* operator[] (std::string s) override
    {
        for (auto element : std::get<std::vector<JsonElement*>>(m_value))
        {
            JsonKey key = * static_cast<JsonKey*>(element);
            if(key.m_name == s)
            {
                return element;
            }
        }
        throw std::runtime_error("Key not found");
    }
    virtual std::string operator[] (int i) override
    {
        return std::get<std::vector<JsonElement*>>(m_value)[i]->m_name;
    }
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