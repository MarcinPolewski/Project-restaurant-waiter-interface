cmake_minimum_required(VERSION 3.13.0)
project(dllist VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-pedantic -Wall -Wextra -v")

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

set(PROJECT_SOURCES address.h destination.h menuItem.h menu.h serverHandler.h serverHandler.cpp)

add_executable(testGoogle testGoogle.cpp ${PROJECT_SOURCES})

target_link_libraries(testGoogle PUBLIC gtest_main)
add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)
# include_directories("${CMAKE_CURRENT_SOURCE_DIR}/build/_deps/csv-src/src/")
include_directories("${csvreader_SOURCE_DIR}")