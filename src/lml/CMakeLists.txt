cmake_minimum_required(VERSION 3.8.0)
project(LearnML CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(INCLUDE_DIR "../../include")
set(SOURCE_DIR "./")
set(OUTPUT_DIR "../../bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

include_directories(${INCLUDE_DIR})
file(GLOB_RECURSE SOURCE_LIST ${SOURCE_DIR}/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_LIST})
target_link_libraries(${PROJECT_NAME} LearnML_EDK)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)