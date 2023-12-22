cmake_minimum_required(VERSION 3.10)
project(tests)

set(CMAKE_CXX_STANDARD 17)

include_directories(
    ${CMAKE_SOURCE_DIR}/path/to/headers
    # Other include directories
)

find_package(Boost REQUIRED COMPONENTS system thread)
# Other find_package calls if necessary

add_executable(tests
    master.cpp
    slave.cpp
    tests.cpp
    # Other source files
)

target_link_libraries(tests
    Boost::system
    Boost::thread
    # Other libraries
)
