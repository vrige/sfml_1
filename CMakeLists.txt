cmake_minimum_required(VERSION 3.15)
project(sfml_1)

set(CMAKE_CXX_STANDARD 14)

##include_directories("C:/users/cristina/CLionProjects/sfml_1")

## If you want to link SFML statically
set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
set(SFML_DIR "D:/Libraries/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
add_executable(unit_testing_sfml_prova main.cpp Tests/AStar.cpp Tests/AStar.h Tests/Player.cpp Tests/Player.h Tests/RenderingMap.cpp Tests/RenderingMap.h Tests/test.cpp)
target_link_libraries(unit_testing_sfml_prova gtest gtest_main sfml-graphics sfml-window sfml-system)