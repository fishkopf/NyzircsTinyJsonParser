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
        m_value = std::vector<JsonElement*>();
    }

    // Destructor
    ~JsonKey()
    {
        
    }
    virtual void attach(JsonElement* child) override
    {
        std::get<std::vector<JsonElement*>>(m_value).push_back(child);
    }
    std::string serialize() override
    {
        std::string serialized = "\""+ m_name + "\""+ ":";
        serialized += std::get<std::vector<JsonElement*>>(m_value)[0]->serialize();
        return serialized;
    }
    std::string serialize(unsigned int indent) override
    {
        std::string indentStr(indent, ' ');

        std::string serialized = indentStr+"\""+ m_name + "\""+ ":";
        serialized += std::get<std::vector<JsonElement*>>(m_value)[0]->serialize();
        return serialized;
    }
private:

};

#endif // JSONKEY_H