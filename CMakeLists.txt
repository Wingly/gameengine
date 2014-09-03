# CMake settings
cmake_minimum_required(VERSION 2.8)

# Root project settings
set(SOLUTION_NAME Game_Engine)
project(${SOLUTION_NAME})

# SET OUTPUTFOLDER FOR ALL SUBPROJECTS
set(OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
##set(EXECUTABLE_OUTPUT_PATH ${OUTPUT_DIRECTORY} CACHE PATH "Build directory" FORCE)
##set(LIBRARY_OUTPUT_PATH ${OUTPUT_DIRECTORY} CACHE PATH "Build directory" FORCE)

# Set global compiler options
add_definitions(-DUNICODE -D_UNICODE)

include_directories(${CMAKE_SOURCE_DIR})

# Add subdirectories
add_subdirectory(engine)