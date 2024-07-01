#ifndef JSON_ROOT_H
#define JSON_ROOT_H
#include "JsonElement.h"

class JsonRoot : public JsonElement
{
public:
    // Constructor
    JsonRoot();

    // Destructor
    ~JsonRoot();



private:
    JsonElement* m_element;
};

#endif // JSONROOT_H