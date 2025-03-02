cmake_minimum_required(VERSION 2.8.12)

# Add this to the top of your CMakeLists.txt
include(FetchContent)
FetchContent_Declare(
  catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v2.13.7 # or the latest version
)
FetchContent_MakeAvailable(catch2)


project(pong)

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

target_link_libraries(${PROJECT_NAME} rt SDL2 SDL2_image SDL2_ttf)

file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION .)

#Add this to the bottom of your CMakeLists.txt
add_executable(tests tests/main.cpp)
target_link_libraries(tests Catch2::Catch2)
