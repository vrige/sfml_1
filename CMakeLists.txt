cmake_minimum_required(VERSION 3.15)
project(sfml_1)

set(CMAKE_CXX_STANDARD 14)

##include_directories("C:/users/cristina/CLionProjects/sfml_1")

## If you want to link SFML statically
set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
set(SFML_DIR "D:/Libraries/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
add_executable(sfml_1 main.cpp TileMap.cpp TileMap.h Player.cpp Player.h)
target_link_libraries(sfml_1 sfml-graphics sfml-window sfml-system)