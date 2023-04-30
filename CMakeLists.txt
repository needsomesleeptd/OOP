cmake_minimum_required(VERSION 3.0.0)
project(dz2)

set(CMAKE_CXX_STANDARD 20)



set(Srcs "setTree/RBtree.hpp" "iterator/Iterator.hpp" "setTree/main.cpp")
set(Hdrs  "setTree/Iset.h" "setTree/treeNode.h" "setTree/tree.h")


add_executable(dz2 ${Srcs} ${Hdrs})