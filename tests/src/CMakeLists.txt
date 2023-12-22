cmake_minimum_required(VERSION 3.10)
project(WorkerNodes)

set(CMAKE_CXX_STANDARD 17)

include_directories(
    ${CMAKE_SOURCE_DIR}/../include
    # Other include directories if needed
)

# Specify the source files
set(SOURCE_FILES
    master.cpp
    slave.cpp
    # Add other source files if necessary
)

# Create a library from the source files
add_library(worker_nodes STATIC ${SOURCE_FILES})

# Link libraries (e.g., Boost) if required
target_link_libraries(worker_nodes
    Boost::system
    Boost::thread
    # Other libraries
)
