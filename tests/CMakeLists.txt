cmake_minimum_required(VERSION 3.10)
project(tests)

set(CMAKE_CXX_STANDARD 17)

include_directories(
    ${CMAKE_SOURCE_DIR}/path/to/headers
    # Other include directories
)

find_package(Boost REQUIRED COMPONENTS system thread)
# Other find_package calls if necessary

# Add the path to your src directory
add_subdirectory(src/ build)

add_executable(tests
    tests.cpp
    # Other source files if necessary
)

target_link_libraries(tests
    worker_nodes # Link the worker_nodes library
    Boost::system
    Boost::thread
    # Other libraries
)
