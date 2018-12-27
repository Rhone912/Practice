cmake_minimum_required(VERSION 3.12)
project(Snake1 C)

link_directories("C:/MinGW/lib")
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -D FREEGLUT_STATIC")

add_executable(Snake1 main.c Data.h Initialization.c Game.c Opengl.c Food.c Weed.c SmartWeed.c Mine.c Map.c Snake.c Save_and_Load.c PowerWeed.c ConfusionWeed.c)
target_link_libraries(Snake1 -lfreeglut -lopengl32 -lglu32 -Wl,--subsystem,windows)