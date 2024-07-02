add_library(JSON_PARSER STATIC
    02_Source/src/JsonParser.cpp
)

target_include_directories(JSON_PARSER PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/02_Source/src/ 
    ${CMAKE_CURRENT_SOURCE_DIR}/02_Source/inc/ 

    PRIVATE


)


