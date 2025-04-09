cmake_minimum_required(VERSION 3.30)
project(Cobalt)

set(CMAKE_CXX_STANDARD 20)

add_executable(Cobalt main.cpp
        src/parser/lexer.cpp
        src/tests/lexer_test.cpp
        src/cobaltEnv/cobalt.cpp
        src/parser/ast.cpp
        src/parser/parser.cpp
        src/codegen/codegen.cpp
)

# connect llvm
find_package(LLVM REQUIRED CONFIG)
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

llvm_map_components_to_libnames(LLVM_LIBS core support)
target_link_libraries(Cobalt ${LLVM_LIBS})