#ifndef JSON_CONTAINER_H
#define JSON_CONTAINER_H

#include "JsonElement.h"

class JsonContainer : public JsonElement 
{
public:
    JsonContainer()
    {
        m_type = JsonElementType::CONTAINER;

    }

    ~JsonContainer()
    {}
};

#endif // JSON_CONTAINER_H