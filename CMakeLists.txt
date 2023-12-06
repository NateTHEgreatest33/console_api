cmake_minimum_required(VERSION 3.5)
project(consoleAPI CXX ASM)

set(CMAKE_CXX_STANDARD 20)

pico_sdk_init()

add_library( consoleAPI
    console.hpp
    console.cpp
    )

target_link_libraries( consoleAPI
  pico_stdlib 
  # Using Pico W
  pico_cyw43_arch_none

)

target_include_directories(consoleAPI PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
