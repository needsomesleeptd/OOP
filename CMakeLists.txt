cmake_minimum_required(VERSION 3.7.0)

project(lab-02 LANGUAGES CXX)

#add_library(matrix
        #src/except.cpp
        #)

#target_include_directories(matrix
        #PUBLIC include)

#add_executable(runner
#        test/runner.cpp
#        test/matrix.cpp
#        test/vector.cpp
#        )

add_executable(tree/tree.hpp tree/main.cpp tree/Iset.h tree/treeNode.h)

#target_link_libraries(runner
#        matrix)

#target_link_libraries(runner
#        CppUTest)