cmake_minimum_required(VERSION 3.25)
# Set project name and version
project(main VERSION 0.1)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

# set clang-format flags
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set cmake debug target
set(CMAKE_BUILD_TYPE Debug)

# Set CPP Standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# gathers all source code files
file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS "src/*.cpp")
add_executable(${PROJECT_NAME} ${SRCS})
target_include_directories(${PROJECT_NAME} PUBLIC "include")

# https://cmake.org/cmake/help/latest/manual/cmake-modules.7.html
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_gfx REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_net REQUIRED)

# target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PUBLIC SDL2::SDL2 SDL2::TTF SDL2::Image
                                             SDL2::Mixer SDL2::Net SDL2::Gfx)
# ...............................................................

# compiles to executable

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
