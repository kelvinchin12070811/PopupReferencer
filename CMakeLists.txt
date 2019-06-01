# use -DQt5_DIR={path to qt5's cmake dir}
cmake_minimum_required(VERSION 3.0.0)
project(PopupReferencer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

#find Qt5 and required components
find_package(Qt5 COMPONENTS REQUIRED Core Gui Widgets)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# add project source files here
set(project_sources
	src/Main.cpp
	src/window/MainWindow.cpp
	)

# add project header files here
set(project_headers
	src/window/MainWindow.hpp
	)

# add project ui files here
set(project_ui
	src/window/MainWindow.ui
	)

# wrap the ui file to a c++ header
qt5_wrap_ui(ui_wrap ${project_ui})
qt5_wrap_cpp(moc_sources ${project_headers})

add_executable(PopupReferencer WIN32 ${project_sources} ${project_headers} ${ui_wrap} ${moc_sources})

target_link_libraries(PopupReferencer
	Qt5::Core
	Qt5::Gui
	Qt5::Widgets
	)

if(WIN32)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:${PROJECT_NAME}>
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:${PROJECT_NAME}>
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:${PROJECT_NAME}>
	)
endif(WIN32)
