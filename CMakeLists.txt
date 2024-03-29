#============================================================================================================
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0.If a copy of the MPL was not distributed with this
# file, You can obtain one at http ://mozilla.org/MPL/2.0/.
#============================================================================================================

# use -DQt5_DIR={path to qt5's cmake dir}
cmake_minimum_required(VERSION 3.0.0)
project(PopupReferencer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

#find Qt5 and required components
find_package(Qt5 COMPONENTS REQUIRED Core Gui Widgets Svg LinguistTools Network)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# add project source files here
set(project_sources
	src/ConfigMng.cpp
	src/graphics_scene/AdvanceScene.cpp
	src/graphics_scene/SimpleScene.cpp
	src/Main.cpp
	src/window/About.cpp
	src/window/AdvPopup.cpp
	src/window/GridCreator.cpp
	src/window/MainWindow.cpp
	src/window/Popup.cpp
	src/window/Settings.cpp
	)

# add project header files here
set(project_headers
	src/ConfigMng.hpp
	src/graphics_scene/AdvanceScene.hpp
	src/graphics_scene/SimpleScene.hpp
	src/libs/nlohmann/json.hpp
	src/window/About.hpp
	src/window/AdvPopup.hpp
	src/window/GridCreator.hpp
	src/window/MainWindow.hpp
	src/window/Popup.hpp
	src/window/Settings.hpp
	)

# add project ui files here
set(project_ui
	src/window/About.ui
	src/window/GridCreator.ui
	src/window/MainWindow.ui
	src/window/Popup.ui
	src/window/Settings.ui
	)

# wrap the ui file to a c++ header
qt5_wrap_ui(ui_wrap ${project_ui})
qt5_wrap_cpp(moc_sources ${project_headers})
qt5_add_resources(qrc_sources resources.qrc)

add_executable(PopupReferencer WIN32 ${project_sources} ${project_headers} ${ui_wrap}
	${moc_sources} ${qrc_sources})
set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
target_link_libraries(PopupReferencer
	Qt5::Core
	Qt5::Gui
	Qt5::Widgets
	Qt5::Svg
	Qt5::Network
	)

if(WIN32)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:${PROJECT_NAME}>
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:${PROJECT_NAME}>
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:${PROJECT_NAME}>
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Svg> $<TARGET_FILE_DIR:${PROJECT_NAME}>
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Network> $<TARGET_FILE_DIR:${PROJECT_NAME}>
	)
endif(WIN32)
