#ifndef JSON_KEY_H
#define JSON_KEY_H
#include "JsonElement.h"
class JsonKey : public JsonElement
{
public:
    // Constructor
    JsonKey();

    // Destructor
    ~JsonKey();



private:
    JsonElement* m_template;

};

#endif // JSONKEY_H