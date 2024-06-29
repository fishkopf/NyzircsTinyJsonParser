add_library(JSON_PARSER STATIC
    02_Source/src/JsonParser.cpp
    02_Source/src/JsonElement.cpp
    02_Source/src/JsonObject.cpp
    02_Source/src/JsonRoot.cpp
    02_Source/src/JsonKey.cpp
    02_Source/src/JsonValue.cpp
    02_Source/src/JsonArray.cpp

)

target_include_directories(JSON_PARSER PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/02_Source/src/ 
    ${CMAKE_CURRENT_SOURCE_DIR}/02_Source/inc/ 

    PRIVATE


)


