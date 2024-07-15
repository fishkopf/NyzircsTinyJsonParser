#ifndef JSON_ELEMENT_H
#define JSON_ELEMENT_H
#include <string>
#include <vector>

enum class JsonElementType
{
    KEY,
    VALUE,
    CONTAINER,
    ARRAY,
    UNKNOWN,
    INTEGER,
    FLOAT,
    STRING,
    ROOT

};

class JsonElement 
{
public:
    // Constructor
    JsonElement()
    {
        m_type = JsonElementType::UNKNOWN;
    }

    // Destructor
    ~JsonElement()
    {

    }

    virtual void attach(JsonElement* child) 
    {
        m_children.push_back(child);
    }
    virtual std::string serialize() = 0;


    std::string m_name;
    JsonElementType m_type;
    std::vector<JsonElement*> m_children;
private:


};

#endif // JSONELEMENT_H