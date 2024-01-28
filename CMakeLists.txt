cmake_minimum_required(VERSION 3.15)
project(SchemeImproved)

# Set the C++ standard to 23
set(CMAKE_CXX_STANDARD 23)

# Find LLVM
find_package(LLVM REQUIRED CONFIG)

# Set LLVM include directories
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# Add the executable
add_executable(SchemeImproved main.cpp lexer.cpp lexer.h
        parser.cpp
        parser.h)

# Link against LLVM
llvm_map_components_to_libnames(LLVM_LIBRARIES core support)
target_link_libraries(SchemeImproved PRIVATE ${LLVM_LIBRARIES})
