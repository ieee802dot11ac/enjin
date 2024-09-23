# CMakeList.txt : CMake project for Encore, include source and define
# project specific logic here.
#

cmake_minimum_required (VERSION 3.11)
project ("game" LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add all subdirectories of src
file(GLOB_RECURSE SRC_FILES "src/*.cpp")
file(GLOB_RECURSE INC_FILES "src/*.h")

# Add source files to the executable
add_executable(game ${SRC_FILES} ${INC_FILES})

# Grab SDL & OpenGL
find_library(SDL_LIB SDL2)
find_library(GL_LIB GL)
find_library(ZMATH_LIB zmath)

# Set the include directory for the executable
target_include_directories(game PRIVATE "src")

# Get the current working branch
execute_process(
        COMMAND git rev-parse --abbrev-ref HEAD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_BRANCH
        OUTPUT_STRIP_TRAILING_WHITESPACE)

# Get the latest commit hash
execute_process(
        COMMAND git rev-parse HEAD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_COMMIT_HASH
        OUTPUT_STRIP_TRAILING_WHITESPACE)

target_compile_definitions(${PROJECT_NAME} PRIVATE
        "-DGIT_COMMIT_HASH=\"${GIT_COMMIT_HASH}\"")

target_link_libraries(game PRIVATE "${SDL_LIB}" "${GL_LIB}" "${ZMATH_LIB}")
