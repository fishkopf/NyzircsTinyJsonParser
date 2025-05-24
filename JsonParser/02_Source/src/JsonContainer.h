#ifndef JSON_CONTAINER_H
#define JSON_CONTAINER_H

#include "JsonElement.h"
#include "JsonKey.h"


class JsonContainer : public JsonElement 
{
public:
    JsonContainer()
    {
        m_type = JsonElementType::CONTAINER;
        m_value = std::vector<JsonElement*>();
    }

    ~JsonContainer()
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
    std::string serialize() override
    {
        if(std::get<std::vector<JsonElement*>>(m_value).empty())
        {
            return "{}";
        }
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

#endif // JSON_CONTAINER_H