cmake_minimum_required(VERSION 3.0.0)
project(dz2)

set(CMAKE_CXX_STANDARD 20)



set(Srcs "setTree/RBtree.hpp" "iterator/Iterator.hpp" "main.cpp" "setTree/tree.h")
set(Hdrs  "setTree/Iset.h" "setTree/treeNode.h" "setTree/tree.h" "utils/concepts.h" "utils/exceptions.h")

include_directories(setTree)
include_directories(iterator)
include_directories(utils)

add_executable(dz2 ${Srcs} ${Hdrs})