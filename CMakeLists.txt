cmake_minimum_required(VERSION 3.15)
project(repotify)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(json)
add_subdirectory(cpr)

add_executable(repotify src/main.cpp src/helpers.cpp src/helpers.h src/JsonReader.cpp src/JsonReader.h src/Domain.cpp src/Domain.h src/Project.cpp src/Project.h)

target_link_libraries(repotify PRIVATE nlohmann_json::nlohmann_json ${CPR_LIBRARIES} gtest_main gtest mongoose test_server notify)
include_directories(${CPR_INCLUDE_DIRS})
include_directories(${NLOHMANN_JSON_INCLUDE_DIRS})
include_directories(/usr/include/glib-2.0)
include_directories(/usr/include/gtk-2.0)
include_directories(/usr/lib/x86_64-linux-gnu/glib-2.0/include)
