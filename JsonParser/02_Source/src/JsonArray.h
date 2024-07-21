#ifndef JSON_ARRAY_H
#define JSON_ARRAY_H

class JsonArray : public JsonElement{
public:
    // Constructor
    JsonArray()
    {
        m_type = JsonElementType::ARRAY;
        m_value = std::vector<JsonElement*>();
    }

    // Destructor
    ~JsonArray(){}
    virtual JsonElement* operator[] (std::string s) override
    {
        throw std::runtime_error("Array does not support key access");
    }
    virtual std::string operator[] (int i) override
    {
        return std::get<std::vector<JsonElement*>>(m_value)[i];
    }
    virtual std::string serialize() override
    {
        if (std::get<std::vector<JsonElement*>>(m_value).empty())
        {
            return "[]";
        }
        std::string serialized = "[";
        for (auto child : std::get<std::vector<JsonElement*>>(m_value))
        {
            serialized += child->serialize() + ",";
        }
        serialized.pop_back(); // remove last comma
        serialized += "]";
        return serialized;
    }
    virtual void attach(JsonElement* child) override
    {
        std::get<std::vector<JsonElement*>>(m_value).push_back(child);
    }
};

#endif // JSONARRAY_H