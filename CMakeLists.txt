cmake_minimum_required(VERSION 3.5)

project(1_lab LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

if(ANDROID)
  add_library(1_lab SHARED
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui

  )
else()
  add_executable(1_lab
          error_handling.cpp
          error_handling.h
          dots.cpp
          dots.h
          dot.cpp
          dot.h
          dot_math_operations/scaler.cpp
          dot_math_operations/scaler.h
          dot_math_operations/rotator.cpp
          dot_math_operations/rotator.h
          dot_math_operations/center.cpp
          dot_math_operations/center.h
          line.cpp
          line.h
          lines.cpp
          lines.h
          model.cpp
          model.h
          request.cpp
          request.h
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
  )
endif()

target_link_libraries(1_lab PRIVATE Qt5::Widgets)
