#ifndef JSON_ARRAY_H
#define JSON_ARRAY_H

class JsonArray : public JsonElement{
public:
    // Constructor
    JsonArray()
    {
        m_type = JsonElementType::ARRAY;
    }

    // Destructor
    ~JsonArray(){}

    virtual std::string serialize() override
    {
        if (m_children.empty())
        {
            return "[]";
        }
        std::string serialized = "[";
        for (auto child : m_children)
        {
            serialized += child->serialize() + ",";
        }
        serialized.pop_back(); // remove last comma
        serialized += "]";
        return serialized;
    }
};

#endif // JSONARRAY_H