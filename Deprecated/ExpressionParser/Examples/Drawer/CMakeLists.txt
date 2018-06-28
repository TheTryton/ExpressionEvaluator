cmake_minimum_required(VERSION 3.8)
project(Drawer)

find_package( Qt5 COMPONENTS Widgets Gui Core REQUIRED )

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(Drawer_Sources
	Include/CCanvas.h
	Source/CCanvas.cpp
	
	Include/CUserInput.h
	Source/CUserInput.cpp
	
	Source/main.cpp
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${Drawer_Sources})

add_executable(Drawer ${Drawer_Sources})

target_link_libraries(Drawer PRIVATE Qt5::Widgets Qt5::Gui Qt5::Core Evaluator)

target_include_directories(Drawer PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/Include)

set_target_properties (Drawer PROPERTIES FOLDER Deprecated/ExpressionParser/Drawer)