project(Restaurant)

add_library(restaurant STATIC orderitem.cpp restaurant.cpp serverhandler.cpp waiter.cpp)
target_include_directories(restaurant PUBLIC ${Restaurant_SOURCE_DIR}/include csv.h)