project(Restaurant)

add_library(restaurant STATIC orderitem.cpp restaurant.cpp waiter.cpp memoryhandler.cpp
    order.cpp table.cpp menu.cpp menuitem.cpp address.cpp employee.cpp menubutton.cpp popupmenu.cpp popuphandler.cpp topbar.cpp mainscreen.cpp consoleuiobject.cpp uitable.cpp address.cpp employee.cpp)
target_include_directories(restaurant PUBLIC ${Restaurant_SOURCE_DIR}/include csv.h)