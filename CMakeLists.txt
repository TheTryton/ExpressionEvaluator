cmake_minimum_required(VERSION 3.8)
project(ExpressionEvaluator)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(BUILD_EXAMPLES FALSE)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(ExpressionEvaluator_Sources
	Include/ExpressionEvaluator.h
	Source/ExpressionEvaluator.cpp
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ExpressionEvaluator_Sources})

add_library(ExpressionEvaluator STATIC ${ExpressionEvaluator_Sources})

add_subdirectory(Deprecated/ExpressionParser)
add_subdirectory(Examples/EvaluatorQt)

target_include_directories(ExpressionEvaluator PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/Include)