cmake_minimum_required(VERSION 3.27)
project(SchemeImproved)

set(CMAKE_CXX_STANDARD 23)

# Find LLVM
find_package(LLVM)

# Set LLVM include directories
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# Add the executable
add_executable(SchemeImproved main.cpp lexer.cpp lexer.h)

# Link against LLVM
llvm_map_components_to_libnames(LLVM_LIBRARIES core support)
target_link_libraries(lisp__ ${LLVM_LIBRARIES})
