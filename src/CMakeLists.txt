project(Restaurant)

add_library(restaurant STATIC orderitem.cpp restaurant.cpp waiter.cpp memoryhandler.cpp order.cpp table.cpp menubutton.cpp popupmenu.cpp popuphandler.cpp topbar.cpp)
target_include_directories(restaurant PUBLIC ${Restaurant_SOURCE_DIR}/include csv.h)