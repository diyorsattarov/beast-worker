cmake_minimum_required(VERSION 3.10)
project(master)

# Find Boost libraries
find_package(Boost REQUIRED)

# Add your executable
add_executable(master master.cpp)

# Link Boost libraries and pthread
target_link_libraries(master Boost::boost pthread)
