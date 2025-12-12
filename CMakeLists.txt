cmake_minimum_required(VERSION 3.0.0)

project(pong VERSION 0.0.1)

set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_C_FLAGS_DEBUG "-O0 -ggdb")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb")

unset(QT_QMAKE_EXECUTABLE)

find_package(Threads REQUIRED)
find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIR} headers)

add_executable(${PROJECT_NAME} "sources/main.cpp" "sources/game.cpp" "sources/actor.cpp" 
    "sources/sprite.cpp" "sources/component.cpp" "sources/background.cpp" "sources/anim.cpp" 
    "sources/redpad.cpp" "sources/bluepad.cpp" "sources/math.cpp" "sources/ball.cpp" 
    "sources/circle.cpp" "sources/font.cpp" "sources/score.cpp") 

target_link_libraries(${PROJECT_NAME} rt SDL2 SDL2_image SDL2_ttf SDL2_mixer)

file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION .)
