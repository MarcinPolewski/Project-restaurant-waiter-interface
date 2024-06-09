cmake_minimum_required(VERSION 3.13.0)
project(Restaurant VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-pedantic -Wall -Wextra")

include(FetchContent)
FetchContent_Declare(
   googletest
   GIT_REPOSITORY https://github.com/google/googletest.git
   GIT_TAG main
)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
  csvReader
  GIT_REPOSITORY https://github.com/ben-strasser/fast-cpp-csv-parser.git
  GIT_TAG master
)
FetchContent_MakeAvailable(csvReader)

find_package(Curses REQUIRED)
include_directories(${Restaurant_SOURCE_DIR}/include ${Restaurant_SOURCE_DIR}/gui_include "${csvreader_SOURCE_DIR}" ${CURSES_INCLUDE_DIR})
add_subdirectory(src)
add_subdirectory(gui_src)

add_executable(testGoogle testGoogle.cpp)
add_executable(gui gui.cpp)

add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)
target_link_libraries(testGoogle PUBLIC gtest_main restaurant)
target_link_libraries(gui ${CURSES_LIBRARIES} restaurant gui_restaurant)