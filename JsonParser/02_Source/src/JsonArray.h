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


};

#endif // JSONARRAY_H