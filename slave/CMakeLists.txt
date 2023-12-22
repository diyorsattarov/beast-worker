cmake_minimum_required(VERSION 3.10)
project(slave)

# Find Boost libraries
find_package(Boost REQUIRED)

# Add your executable
add_executable(slave slave.cpp)

# Link Boost libraries and pthread
target_link_libraries(slave Boost::boost pthread)
