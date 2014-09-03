# CMake settings
cmake_minimum_required(VERSION 2.8)

# Root project settings
set(PROJECT_NAME_ENGINE engine)
project(${PROJECT_NAME_ENGINE})

# Set the files used in the target
file(GLOB_RECURSE SOURCES Source/*.cpp)
file(GLOB_RECURSE HEADERS Include/*.h)

# Add the target
add_executable(${PROJECT_NAME_ENGINE} ${HEADERS} ${SOURCES})

# Set SUBSYSTEM:WINDOWS
set_target_properties(${PROJECT_NAME_ENGINE} PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")