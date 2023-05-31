cmake_minimum_required(VERSION 3.5)

project(3 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
find_package(glm REQUIRED)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)



MACRO(HEADER_DIRECTORIES return_list)
    FILE(GLOB_RECURSE new_list *.h)
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()




add_executable(${PROJECT_NAME}
        ../src/main.cpp
        ../inc/mainwindow.h
        ../src/mainwindow.cpp
        ../inc/model/dot.h
        ../src/model/dot.cpp
        ../src/model/link.cpp
        ../inc/model/link.h
        ../src/model/model_struct.cpp
        ../inc/model/model_struct.h
        ../src/model/model.cpp
        ../inc/model/model.h
        ../inc/object/object.h
        ../src/object/composite.cpp
        ../inc/object/composite.h
        ../src/camera/camera.cpp
        ../inc/camera/camera.h
        ../inc/visitor/visitor.h
        ../src/scene/scene.cpp
        ../inc/scene/scene.h
        ../inc/managers/base_manager.h
        ../src/managers/scene/scene_manager.cpp
        ../inc/managers/scene/scene_manager.h
        ../inc/managers/scene/scene_manager_creator.h
        ../src/managers/scene/scene_manager_creator.cpp
        ../inc/managers/transform/transform_manager_creator.h
        ../inc/managers/transform/transform_manager.h
        ../src/managers/transform/transform_manager.cpp
        ../src/managers/transform/transform_manager_creator.cpp
        ../src/managers/draw/draw_manager.cpp
        ../inc/managers/draw/draw_manager.h
        ../inc/managers/draw/draw_manager_creator.h
        ../src/managers/draw/draw_manager_creator.cpp
        ../inc/drawer/abstract_drawer.h
        ../inc/drawer/abstract_drawer_factory.h
        ../inc/drawer/drawer_qt.h
        ../src/drawer/drawer_qt.cpp
        ../inc/drawer/drawer_qt_factory.h
        ../src/drawer/drawer_qt_factory.cpp
        ../inc/managers/load/load_manager.h
        ../src/managers/load/load_manager.cpp
        ../inc/managers/load/abstract_load_controller.h
        ../src/managers/load/abstract_load_controller.cpp
        ../inc/managers/load/load_manager_creator.h
        ../src/managers/load/load_manager_creator.cpp
        ../inc/builder/base_builder.h
        ../inc/builder/builder_model.h
        ../src/builder/builder_model.cpp
        ../inc/builder/builder_camera.h
        ../src/builder/builder_viewer.cpp
        ../src/builder/builder_scene.cpp
        ../inc/builder/builder_scene.h
        ../inc/loader/base_loader.h
        ../inc/loader/base_loader_model.h
        ../inc/loader/loader_model_file.h
        ../src/loader/loader_model_file.cpp
        ../inc/loader/base_loader_camera.h
        ../inc/loader/loader_camera_file.h
        ../src/loader/loader_camera_file.cpp
        ../src/loader/loader_scene_file.cpp
        ../inc/loader/loader_scene_file.h
        ../inc/loader/base_loader_scene.h
        ../inc/managers/load/load_model_controller.h
        ../src/managers/load/load_model_controller.cpp
        ../src/managers/load/load_model_controller_creator.cpp
        ../inc/managers/load/load_model_controller_creator.h
        ../inc/managers/load/load_scene_controller.h
        ../inc/managers/load/load_scene_controller_creator.h
        ../src/managers/load/load_scene_controller.cpp
        ../src/managers/load/load_scene_controller_creator.cpp
        ../inc/commands/base_command.h
        ../inc/commands/camera_command.h
        ../src/commands/camera_command.cpp
        ../src/commands/model_command.cpp
        ../inc/commands/model_command.h
        ../src/commands/scene_command.cpp
        ../inc/commands/scene_command.h
        ../inc/facade/facade.h
        ../src/facade/facade.cpp
        ../inc/exceptions.h
        ../inc/configuration/abstract_cfg.h
        ../inc/configuration/creator_cfg.h
        ../src/configuration/creator_cfg.cpp
        ../src/configuration/configuration.cpp
        ../inc/configuration/configuration.h
        ../inc/math/glm_wrapper.h
        ../src/math/glm_wrapper.cpp
        ../inc/utils/BaseTransformer.h
        ../src/utils/BaseTransformer.cpp


        inc/commands/compound_command.h src/commands/compound_command.cpp inc/visitor/TransformVisitor.h src/visitor/TransformVisitor.cpp)

HEADER_DIRECTORIES(header_dir_list)

target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
        ${header_dir_list}
)
message(STATUS "[INFO] Found ${header_dir_list_count} header directories.")


find_library(LIBCONFIGPP_LOCATION libconfig++)
find_library(LIBCONFIG_LOCATION libconfig)
target_link_libraries(3 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets  ${GTEST_LIBRARIES} Threads::Threads glm::glm -L/usr/local/Cellar/libconfig/1.7.2/lib/ -lconfig++)






set_target_properties(3 PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
        )

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(3)
endif()