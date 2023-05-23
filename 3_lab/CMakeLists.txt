cmake_minimum_required(VERSION 3.5)

project(3_lab LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
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

find_package(Qt5 COMPONENTS Widgets LinguistTools REQUIRED)

set(TS_FILES 3_lab_ru_RU.ts)

include_directories(Point)

if(ANDROID)
  add_library(3_lab SHARED
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui

    ${TS_FILES}
  )
else()
  add_executable(3_lab
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
          Point/Point.cpp
          Point/Point.h
          Figure/Figure.cpp
          Figure/Figure.h
    ${TS_FILES}
          Model/Model.cpp Model/Model.h Model/BaseModel.cpp Model/BaseModel.h Objects/VisiableObject.cpp Objects/VisiableObject.h Entity/Entity.cpp Entity/Entity.h Matrix/Matrix.cpp Matrix/Matrix.h)
endif()

target_link_libraries(3_lab PRIVATE Qt5::Widgets)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
