cmake_minimum_required(VERSION 3.30)
project(DecFSM)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

file(GLOB LIB_SRC_FILES "src/*.*")

set(LIB_PATH ${CMAKE_SOURCE_DIR}/lib)
set(EXE_PATH ${CMAKE_SOURCE_DIR}/bin)


set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIB_PATH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIB_PATH})
set(EXECUTABLE_OUTPUT_PATH ${EXE_PATH})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${EXE_PATH})

add_library(${PROJECT_NAME} ${LIB_SRC_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ./include)

file(GLOB EXE_SRC_FILES "test/*.c*")

add_executable(test ${EXE_SRC_FILES})
target_include_directories(test PUBLIC ./include)
target_link_directories(test PRIVATE ${LIB_PATH}/${CMAKE_BUILD_TYPE})
target_link_libraries(test ${PROJECT_NAME})