cmake_minimum_required(VERSION 3.28)
include(FetchContent)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Project definition
project(client LANGUAGES CXX)
add_executable(server
    include/server.h
	include/mqttserver.h source/mqttserver.cpp
    main.cpp
)
target_include_directories(server PRIVATE
	${CMAKE_SOURCE_DIR}/include
)
target_compile_options(server PRIVATE
	-Wall
	-Wextra
	-Wno-strict-aliasing
)

## OpenSSL
FetchContent_Declare(openssl-cmake URL https://github.com/jimmy-park/openssl-cmake/archive/refs/tags/3.5.0.tar.gz)
FetchContent_MakeAvailable(openssl-cmake)

## Paho MQTT
set(PAHO_WITH_MQTT_C ON CACHE BOOL "" FORCE)
set(PAHO_WITH_SSL ON CACHE BOOL "" FORCE)
set(PAHO_BUILD_SHARED OFF CACHE BOOL "" FORCE)
set(PAHO_BUILD_STATIC ON CACHE BOOL "" FORCE)
FetchContent_Declare(paho-mqtt-cpp GIT_REPOSITORY https://github.com/eclipse/paho.mqtt.cpp.git GIT_TAG v1.5.3)
FetchContent_MakeAvailable(paho-mqtt-cpp)
add_dependencies(common_ssl_obj_static OpenSSL::SSL)

# Link libraries
target_link_libraries(server PRIVATE
	paho-mqttpp3-static
)