#ifndef JSON_ELEMENT_H
#define JSON_ELEMENT_H
#include <string>
#include <vector>
#include <stdexcept>

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
    virtual JsonElement* operator[] (std::string s)
    {
        throw std::runtime_error("Not implemented");
    }
    virtual std::string operator[] (int i)
    {
        throw std::runtime_error("Not implemented");
    }
    // Destructor
    ~JsonElement()
    {

    }

    virtual void attach(JsonElement* child) = 0;

    virtual std::string serialize() = 0;

    JsonElementType m_type;


    template <typename T>
    T getValue() const {
        if (std::holds_alternative<T>(m_value)) {
            return std::get<T>(m_value);
        } else {
            throw std::bad_variant_access();
        }
    }
    std::string m_name;

protected:
    using ValueType = std::variant<int, long double, std::string, std::vector<JsonElement*>>;
    ValueType m_value;
    
private:
    
 



};

#endif // JSONELEMENT_H