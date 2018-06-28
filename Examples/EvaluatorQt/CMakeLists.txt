cmake_minimum_required(VERSION 3.8)
project(EvaluatorQt)

find_package( Qt5 COMPONENTS Widgets Gui Core REQUIRED )

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(EvaluatorQt_Sources
	Source/main.cpp

	Source/CCalculator.cpp
	Include/CCalculator.h
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${EvaluatorQt_Sources})

add_executable(EvaluatorQt ${EvaluatorQt_Sources})

target_link_libraries(EvaluatorQt PRIVATE Qt5::Widgets Qt5::Gui Qt5::Core ExpressionEvaluator)

target_include_directories(EvaluatorQt PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/Include)

set_target_properties (EvaluatorQt PROPERTIES FOLDER Examples)