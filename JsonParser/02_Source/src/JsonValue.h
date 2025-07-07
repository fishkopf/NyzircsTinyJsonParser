#ifndef JSONSTRVALUE_H
#define JSONSTRVALUE_H
#include <iostream>
#include <variant>
#include <string>
#include <vector>
#include <stdexcept>
#include "JsonElement.h"

class JsonValue : public JsonElement
{
public:
    // Constructor
    JsonValue(std::string value)
    {
        m_value = value;
        m_type = JsonElementType::STRING;
    }
    JsonValue(int value)
    {
        m_value = value;
        m_type = JsonElementType::INTEGER;
    }
    JsonValue(unsigned int value)
    {
        m_value = (int)value;
        m_type = JsonElementType::INTEGER;
    }
    JsonValue(long double value)
    {
        m_value = value;
        m_type = JsonElementType::FLOAT;
    }


    // Destructor
    ~JsonValue()
    {
        
    }
    virtual void attach(JsonElement* child) override
    {
        // Do nothing
    }
    virtual std::string serialize() override
    {
        if(m_type == JsonElementType::STRING)
        {
            return std::get<std::string>(m_value);
        }
        else if(m_type == JsonElementType::INTEGER)
        {
            return std::to_string(std::get<int>(m_value));
        }
        else if(m_type == JsonElementType::FLOAT)
        {
            return std::to_string(std::get<long double>(m_value));
        }

        return "";        
    }
    std::string serialize(unsigned int indent) override
    {
        std::string ret = this->serialize();
        return  ret;
    }

    template <typename T>
    T getValue() const {
        if (std::holds_alternative<T>(m_value)) {
            return std::get<T>(m_value);
        } else {
            throw std::bad_variant_access();
        }
    }

private:
    using ValueType = std::variant<int, long double, std::string>;



};

#endif // JSON_VALUE_H