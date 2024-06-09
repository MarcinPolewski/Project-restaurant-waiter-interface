project(Restaurant)

add_library(gui_restaurant STATIC menubutton.cpp popupmenu.cpp popuphandler.cpp topbar.cpp mainscreen.cpp consoleuiobject.cpp uitable.cpp)
target_include_directories(gui_restaurant PUBLIC ${Restaurant_SOURCE_DIR}/gui_include)