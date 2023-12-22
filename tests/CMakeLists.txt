cmake_minimum_required(VERSION 3.10)
project(tests)

find_package(Threads)
# Add your executable
add_executable(tests tests.cpp)

# Link Boost libraries and pthread
target_link_libraries(tests pthread)
