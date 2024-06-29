
cmake_minimum_required(VERSION 3.27)
project(JsonParser)


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/JsonParser)


add_executable(JsonParser ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

target_include_directories(JsonParser PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/JsonParser/02_Source/inc/
    
    PRIVATE
)
target_link_libraries(  JsonParser
                        PRIVATE
                        JSON_PARSER                           
)

